/*
 *  debug-launchpad
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jungmin Cho <chivalry.cho@samsung.com>, Gwangho Hwang <gwang.hwang@samsung.com>
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


#ifdef DAC_ACTIVATE

#include <privilege-control.h>

#define INHOUSE_UID     5000
static inline int __set_access(const char* pkg_name, const char* pkg_type, const char* app_path)
{
	return perm_app_set_privilege_debug(pkg_name, pkg_type, app_path);
}

#else

static inline int __set_access(const char* pkg_name, const char* pkg_type, const char* app_path)
{
	return 0;
}

#endif


