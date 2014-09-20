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

#include "atype.h"
#include "reg.h"

int main(int argc, char** argv)
{
    int i5 = 5;
    int i16 = 16;
    float f14p6 = 14.6f;

    Register reg;
    reg.load(REGISTER_EAB, &i5);
    reg.load(REGISTER_ECD, &i16);
    reg.clear(REGISTER_EAB);

    reg.debug(REGISTER_EAB);
    reg.debug(REGISTER_ECD);

    return EXIT_SUCCESS;
}
