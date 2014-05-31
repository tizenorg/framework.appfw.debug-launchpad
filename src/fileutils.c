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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

static int recurse(const char *path, mode_t mode, int (*fn)(const char *,mode_t, int)) {
    struct stat st;
    char dir[PATH_MAX];

    if (path == NULL) {
        return -1;
    }
    if (lstat (path, &st) == -1) {
        return -1;
    }
    if (strrchr(path, '/') != NULL) {
        int n = strlen(path)-strlen(strrchr(path, '/'));
        if (n >= PATH_MAX) {
            return -1;
        }
        strncpy(dir, path, n);
        dir[n] = '\0';
        fn(dir, mode,1);
        return 0;
    }
    return -1;
}

int dlp_chmod(const char *path, mode_t mode, int recursive) {
#ifdef HAVE_WIN32_PROC
    fprintf(stderr, "error: dlp_chmod not implemented on Win32 (%s)\n", path);
    return -1;
#else
    struct stat st;

    if (stat (path, &st) == -1)
        return -1;

    if (chmod (path, mode) == -1) {
        return -1;
    }
    if (recursive) {
        return recurse(path, mode, dlp_chmod);
    }
    return 0;
#endif
}
