/* 
 * Copyright (C) 2014 Lovro Kalinovcic
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * File: native.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "native.h"

#if defined AVM_WINDOWS
#include <windows.h>
#elif defined AVM_LINUX || defined AVM_MAC
#include <dlfcn.h>
#endif

struct AVM_native* AVM_native_new(char* name)
{
    struct AVM_native* native = malloc(sizeof(struct AVM_native));
    native->name = name;
    return native;
}

void AVM_native_free(struct AVM_native* native)
{
    free(native->name);
    free(native);
}

static char* AVM_nativelib_getpath(char* name)
{
#if defined AVM_WINDOWS
    char* extension = "dll";
#elif defined AVM_MAC
    char* extension = "dylib";
#elif defined AVM_LINUX
    char* extension = "so";
#endif
    char* path = malloc(strlen(name) + 1 + strlen(extension));
    sprintf(path, "%s.%s", name, extension);
    return path;
}

struct AVM_nativelib* AVM_nativelib_new(char* name)
{
    struct AVM_nativelib* lib = malloc(sizeof(struct AVM_nativelib));
    char* path = AVM_nativelib_getpath(name);
    AVM_nativelib_open(lib, path);
    free(path);
    return lib;
}

void AVM_nativelib_free(struct AVM_nativelib* lib)
{
    AVM_nativelib_close(lib);
    free(lib);
}

void AVM_nativelib_open(struct AVM_nativelib* lib, char* path)
{
#if defined AVM_WINDOWS
#error "missing support"
#elif defined AVM_LINUX || defined AVM_MAC
    lib->handle = dlopen(path, RTLD_LAZY);
    char* error = dlerror();
    if(error) AVM_abort(error, AVM_ERRNO_NLIBOPEN);
#endif
}

void AVM_nativelib_close(struct AVM_nativelib* lib)
{
#if defined AVM_WINDOWS
#error "missing support"
#elif defined AVM_LINUX || defined AVM_MAC
    dlclose(lib->handle);
    char* error = dlerror();
    if(error) AVM_abort(error, AVM_ERRNO_NLIBCLSE);
#endif
}

AVM_native_proto AVM_nativelib_load(struct AVM_nativelib* lib, char* symbol)
{
#if defined AVM_WINDOWS
#error "missing support"
#elif defined AVM_LINUX || defined AVM_MAC
    AVM_native_proto proto = (AVM_native_proto) dlsym(lib->handle, symbol);
    // missing error handling
    return proto;
#endif
}
