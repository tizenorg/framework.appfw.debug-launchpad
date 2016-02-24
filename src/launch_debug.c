/*
 *  debug-launchpad
 *
 * Copyright (c) 2000 - 2015 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Sangmin Jeong <s-mim.jeong@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aul.h>
#include <bundle.h>
#include <bundle_internal.h>
#include "app_sock.h"
#include "simple_util.h"

#define APP_PATH_MAX_LENGTH 1024

static char app_path[APP_PATH_MAX_LENGTH];

static void print_usage(const char *progname)
{
	printf("[usage] %s [appid] __AUL_SDK__ ATTACH __DLP_ATTACH_ARG__ --attach,:[port],[pid]\n", progname);
	printf("ex) $ launch_debug [appid] __AUL_SDK__ ATTACH __DLP_ATTACH_ARG__ --attach,:10003,1234\n");
}

static int iterfunc(const aul_app_info *info, void *data)
{
	if (info && data && !strcmp(info->appid, (char *)data)) {
		strncpy(app_path, info->app_path, APP_PATH_MAX_LENGTH - 1);
		app_path[APP_PATH_MAX_LENGTH - 1] = '\0';
		return -1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	int i, j, cnt;
	int ret;
	bundle *b;
	int b_datalen;
	bundle_raw *b_data;
	char *bundle_args[10];

	if (argc < 2) {
		print_usage(argv[0]);
		exit(-1);
	}

	b = bundle_create();
	if (b == NULL) {
		printf("out of memory");
		exit(-1);
	}

	if(aul_app_get_running_app_info(iterfunc, argv[1]) != AUL_R_OK)
		_E("get running app info failed");

	for (i = 2; i < argc; i++) {
		if (argv[i] && !strcmp(argv[i], "__AUL_SDK__"))
			bundle_add(b, "__AUL_SDK__", argv[i + 1]);

		if (argv[i] && !strcmp(argv[i], "__DLP_ATTACH_ARG__")) {
			bundle_args[0] = strtok(argv[i + 1], ",");

			cnt = 1;
			while ((bundle_args[cnt] = strtok(NULL, ",")) != NULL)
				cnt++;

			bundle_add(b, "ATTACH", "__DLP_ATTACH_ARG__");
			bundle_add_str_array(b, "__DLP_ATTACH_ARG__", NULL, cnt);

			for (j = 0; j < cnt; j++)
				bundle_set_str_array_element(b, "__DLP_ATTACH_ARG__", j, bundle_args[j]);
		}
	}

	bundle_add(b, "__AUL_PKG_NAME__", argv[1]);
	bundle_add(b, "__AUL_STARTTIME__", "1441865531/743961");
	bundle_add(b, "__AUL_CALLER_PID__", "0");
	bundle_add(b, "__AUL_HWACC__", "SYS");
	bundle_add(b, "__AUL_TASKMANAGE__", "true");
	bundle_add(b, "__AUL_EXEC__", app_path);
	bundle_add(b, "__AUL_PACKAGETYPE__", "rpm");
	bundle_add(b, "__AUL_INTERNAL_POOL__", "false");
	bundle_add(b, "__AUL_PKGID_", argv[1]);
	bundle_add(b, "__AUL_HIGHPRIORITY__", "true");

	bundle_encode(b, &b_data, &b_datalen);

	ret = __app_send_raw(DEBUG_LAUNCHPAD_PID, APP_START, b_data, b_datalen);
	if (ret < 0)
		_E("Bundle send fail");

	free(b_data);

	return ret;
}
