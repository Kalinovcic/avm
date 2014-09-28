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
 * File: aby.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "aby.h"

#define AVM_ABY_FREAD(ptr, pF)     if(!fread(&(ptr), sizeof(ptr), 1, pF)) AVM_abort("failed to load ABY", AVM_ERRNO_ABYFLOAD);

inline char* AVM_readstring(FILE* pF)
{
    AVM_size size = 0;
    AVM_size pos = ftell(pF);
    char c;
    do { AVM_ABY_FREAD(c, pF); size++; } while(c);
    char* str = malloc(size);
    fseek(pF, pos, SEEK_SET);
    fread(str, size, 1, pF);
    return str;
}

struct AVM_ABY* AVM_ABY_new(FILE* pF)
{
    AVM_u32 i;

    struct AVM_ABY* aby = malloc(sizeof(struct AVM_ABY));

    AVM_u8 header;
    AVM_ABY_FREAD(header, pF);
    if(header != 'A')
        AVM_abort("invalid ABY header", AVM_ERRNO_ABYINVHD);
    AVM_ABY_FREAD(header, pF);
    if(header != 'B')
        AVM_abort("invalid ABY header", AVM_ERRNO_ABYINVHD);
    AVM_ABY_FREAD(header, pF);
    if(header != 'Y')
        AVM_abort("invalid ABY header", AVM_ERRNO_ABYINVHD);
    AVM_ABY_FREAD(header, pF);
    if(header != 0x1B)
        AVM_abort("invalid ABY header", AVM_ERRNO_ABYINVHD);

    AVM_ABY_FREAD(aby->version, pF);

    AVM_ABY_FREAD(aby->nativec, pF);
    aby->nativev = malloc(sizeof(void*) * aby->nativec);
    for(i = 0; i < aby->nativec; i++)
    {
        char* native_name = AVM_readstring(pF);
        struct AVM_native* native = AVM_native_new(native_name);
        aby->nativev[i] = native;
    }

    AVM_ABY_FREAD(aby->bcodec, pF);
    aby->bcodev = malloc(sizeof(void*) * aby->bcodec);
    for(i = 0; i < aby->bcodec; i++)
    {
        AVM_u32 bcode_size;
        AVM_ABY_FREAD(bcode_size, pF);
        struct AVM_bytecode* bcode = AVM_bytecode_new(bcode_size);
        AVM_bytecode_load(bcode, pF);
        aby->bcodev[i] = bcode;
    }

    aby->threadc = 1;
    aby->threadv = AVM_thread_new();
    AVM_thread_setnext(aby->threadv, aby->threadv);

    AVM_u32 globalmem_size;
    AVM_ABY_FREAD(globalmem_size, pF);
    aby->globalmem = AVM_memory_new(globalmem_size);

    return aby;
}

#undef AVM_ABY_FREAD

void AVM_ABY_free(struct AVM_ABY* aby)
{
    AVM_u32 i;

    for(i = 0; i < aby->nativec; i++)
        AVM_native_free(aby->nativev[i]);
    free(aby->nativev);

    for(i = 0; i < aby->bcodec; i++)
        AVM_bytecode_free(aby->bcodev[i]);
    free(aby->bcodev);

    for(i = 0; i < aby->threadc; i++)
    {
        struct AVM_thread* cur = aby->threadv;
        aby->threadv = aby->threadv->next;
        AVM_thread_free(cur);
    }

    AVM_memory_free(aby->globalmem);

    free(aby);
}
