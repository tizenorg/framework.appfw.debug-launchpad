/*
 *  debug-launchpad
 *
 * Copyright (c) 2000 - 2015 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: MooChang Kim <moochang.kim@samsung.com>
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

/*
 * simple AUL daemon - launchpad
 */

#include <stdio.h>
#include <aul.h>

void print_usage(const char *progname)
{
	printf("[usage] %s <appid>\n", progname);
}

int main(int argc, char **argv)
{
	int pid;
	char *appid = NULL;

	if (argc < 2) {
		print_usage(argv[0]);
		return -1;
	}

	appid = argv[1];

	pid = aul_app_get_pid(appid);

	/* get pid by appid */
	printf("%d\n", pid);

	return 0;
}
