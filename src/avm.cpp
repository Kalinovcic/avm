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
 * File: avm.cpp
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include <iostream>

#include <cstdlib>
#include <cstdio>

#include "bcode.h"

int main(int argc, char** argv)
{
    FILE* file = fopen("../aspelc/test.aby", "r");
    fseek(file, 0, SEEK_END);
    u32 filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    u8* bcraw = new u8[filesize];
    fread(bcraw, 1, filesize, file);
    fclose(file);

    Bytecode* bytecode = new Bytecode(bcraw, bcraw + filesize);

    char* str = (char*) bytecode->nextString();
    u32 num = bytecode->next16();
    bytecode->next();
    char* str2 = (char*) bytecode->nextString();

    fprintf(stdout, "%s\n%d\n%s\n", str, num, str2);

    delete bytecode;
    delete[] bcraw;

    return EXIT_SUCCESS;
}
