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

/******************************************************/

void Register::clear(u8 reg)
{
    if(!valid(reg)) exit(AVMEXIT_REGINVCLEAR);
    clear_unchecked(reg);
}

void Register::load(u8 reg, void* p_val)
{
    if(!valid(reg)) exit(AVMEXIT_REGINVLOAD);
    load_unchecked(reg, p_val);
}

void Register::mov(u8 reg1, u8 reg2)
{
    if(!valid(reg1)) exit(AVMEXIT_REGINVMOV);
    if(!valid(reg2)) exit(AVMEXIT_REGINVMOV);
    if(overlap(reg1, reg2)) exit(AVMEXIT_REGLAPMOV);
    mov_unchecked(reg1, reg2);
}

void Register::swap(u8 reg1, u8 reg2)
{
    if(!valid(reg1)) exit(AVMEXIT_REGINVMOV);
    if(!valid(reg2)) exit(AVMEXIT_REGINVMOV);
    if(overlap(reg1, reg2)) exit(AVMEXIT_REGLAPMOV);
    swap_unchecked(reg1, reg2);
}

/******************************************************/

bool Register::valid(u8 reg)
{
    return ((reg >> 4) + (reg & 0xF)) < 16;
}

bool Register::overlap(u8 reg1, u8 reg2)
{
    u8 pos1 = reg1 >> 4;
    u8 pos2 = reg2 >> 4;
    if(pos1 < pos2)
        return pos1 + (reg1 & 0xF) >= pos2;
    return pos2 + (reg2 & 0xF) >= pos1;
}

/******************************************************/

void Register::load_register(u8 reg, u8 srcsize, void* src)
{
    u8 pos = reg >> 4;
    u8 size = (reg & 0xF) + 1;
    if(srcsize >= size)
    {
        memcpy(m_bytes + pos, src, size);
    }
    else
    {
        memset(m_bytes + pos, 0, size);
        memcpy(m_bytes + pos, src, srcsize);
    }
}

void Register::to_buffer(u8 reg)
{
    memset(m_buff, 0, 16);
    memcpy(m_buff, m_bytes + (reg >> 4), (reg & 0xF) + 1);
}

/******************************************************/

void Register::clear_unchecked(u8 reg)
{
    memset(m_bytes + (reg >> 4), 0, (reg & 0xF) + 1);
}

void Register::load_unchecked(u8 reg, void* p_val)
{
    memcpy(m_bytes + (reg >> 4), p_val, (reg & 0xF) + 1);
}

void Register::mov_unchecked(u8 reg1, u8 reg2)
{
    load_register(reg2, (reg1 & 0xF) + 1, m_bytes + (reg1 >> 4));
}

void Register::swap_unchecked(u8 reg1, u8 reg2)
{
    to_buffer(reg1);
    load_register(reg1, (reg2 & 0xF) + 1, m_bytes + (reg2 >> 4));
    load_register(reg2, 16, m_buff);
}
