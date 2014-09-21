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
    Register reg;
    reg.util_load32f(REGISTER_EAB, 51.23f);

    reg.debug2(REGISTER_EAB);
    reg.cfi(REGISTER_EAB);
    reg.debug(REGISTER_EAB);
    reg.cif(REGISTER_EAB);
    reg.debug2(REGISTER_EAB);

    return EXIT_SUCCESS;
}
