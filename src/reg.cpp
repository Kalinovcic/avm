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
 * File: reg.cpp
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "reg.h"

Register::Register()
{

}

Register::~Register()
{

}

void Register::load(u8 reg, void* p_val)
{
    if(!valid(reg)) exit(AVMEXIT_REGLOAD);
    memcpy(m_bytes + (reg >> 4), p_val, (reg & 0xF) + 1);
}

void Register::mov(u8 reg1, u8 reg2)
{

}
