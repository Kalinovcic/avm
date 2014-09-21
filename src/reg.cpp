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

bool Register::valid(u8 reg)
{
    u8 pos = reg >> 4;
    u8 size = (reg & 0xF) + 1;
    return (pos + size - 1 < 16)
        && !(pos % size)
        && !((size & (size - 1)))
        && (size != 16);
}

bool Register::valid_float(u8 reg)
{
    u8 pos = reg >> 4;
    u8 size = (reg & 0xF) + 1;
    return (pos + size - 1 < 16)
        && !(pos % size)
        && !((size & (size - 1)))
        && (size != 16)
        && (size >= 4);
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

void Register::loadreg(u8 reg, u8 srcsize, void* src)
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

void Register::tobuff(u8 reg)
{
    memset(m_buff, 0, 16);
    memcpy(m_buff, m_bytes + (reg >> 4), (reg & 0xF) + 1);
}

/******************************************************/

void Register::clear_noc(u8 reg)
{
    memset(m_bytes + (reg >> 4), 0, (reg & 0xF) + 1);
}

void Register::load_noc(u8 reg, void* p_val)
{
    memcpy(m_bytes + (reg >> 4), p_val, (reg & 0xF) + 1);
}

void Register::mov_noc(u8 reg1, u8 reg2)
{
    loadreg(reg2, (reg1 & 0xF) + 1, m_bytes + (reg1 >> 4));
}

void Register::swap_noc(u8 reg1, u8 reg2)
{
    tobuff(reg1);
    loadreg(reg1, (reg2 & 0xF) + 1, m_bytes + (reg2 >> 4));
    loadreg(reg2, 16, m_buff);
}

void Register::rot_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: rotateu8 ((u8 *) (m_bytes + (reg1 >> 4)), (u8) val); break;
    case 2: rotateu16((u16*) (m_bytes + (reg1 >> 4)), (u8) val); break;
    case 4: rotateu32((u32*) (m_bytes + (reg1 >> 4)), (u8) val); break;
    case 8: rotateu64((u64*) (m_bytes + (reg1 >> 4)), (u8) val); break;
    }
}

void Register::shtl_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) <<= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) <<= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) <<= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) <<= val; break;
    }
}

void Register::shtr_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) >>= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) >>= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) >>= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) >>= val; break;
    }
}

void Register::band_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) &= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) &= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) &= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) &= val; break;
    }
}

void Register::bor_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) |= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) |= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) |= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) |= val; break;
    }
}

void Register::bxor_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) ^= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) ^= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) ^= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) ^= val; break;
    }
}

void Register::bnot_noc(u8 reg)
{
    switch((reg & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg >> 4)))) ^= -1; break;
    case 2: (*((u16*) (m_bytes + (reg >> 4)))) ^= -1; break;
    case 4: (*((u32*) (m_bytes + (reg >> 4)))) ^= -1; break;
    case 8: (*((u64*) (m_bytes + (reg >> 4)))) ^= -1; break;
    }
}

void Register::inc_noc(u8 reg)
{
    switch((reg & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg >> 4))))++; break;
    case 2: (*((u16*) (m_bytes + (reg >> 4))))++; break;
    case 4: (*((u32*) (m_bytes + (reg >> 4))))++; break;
    case 8: (*((u64*) (m_bytes + (reg >> 4))))++; break;
    }
}

void Register::dec_noc(u8 reg)
{
    switch((reg & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg >> 4))))--; break;
    case 2: (*((u16*) (m_bytes + (reg >> 4))))--; break;
    case 4: (*((u32*) (m_bytes + (reg >> 4))))--; break;
    case 8: (*((u64*) (m_bytes + (reg >> 4))))--; break;
    }
}

void Register::neg_noc(u8 reg)
{
    switch((reg & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg >> 4)))) *= -1; break;
    case 2: (*((u16*) (m_bytes + (reg >> 4)))) *= -1; break;
    case 4: (*((u32*) (m_bytes + (reg >> 4)))) *= -1; break;
    case 8: (*((u64*) (m_bytes + (reg >> 4)))) *= -1; break;
    }
}

void Register::add_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) += val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) += val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) += val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) += val; break;
    }
}

void Register::sub_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) -= val; break;
    }
}

void Register::mul_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) *= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) *= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) *= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) *= val; break;
    }
}

void Register::div_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::idiv_noc(u8 reg1, u8 reg2)
{
    i64 val = getival(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((i8 *) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 2: (*((i16*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 4: (*((i32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((i64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::fadd_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) += val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) += val; break;
    }
}

void Register::fiadd_noc(u8 reg1, u8 reg2)
{
    i64 val = getival(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) += val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) += val; break;
    }
}

void Register::fuadd_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) += val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) += val; break;
    }
}

void Register::fsub_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) -= val; break;
    }
}

void Register::fisub_noc(u8 reg1, u8 reg2)
{
    i64 val = getival(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) -= val; break;
    }
}

void Register::fisubr_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((i8 *) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 2: (*((i16*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 4: (*((i32*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 8: (*((i64*) (m_bytes + (reg1 >> 4)))) -= val; break;
    }
}

void Register::fusub_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) -= val; break;
    }
}

void Register::fusubr_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) -= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) -= val; break;
    }
}

void Register::fmul_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) *= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) *= val; break;
    }
}

void Register::fimul_noc(u8 reg1, u8 reg2)
{
    i64 val = getival(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) *= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) *= val; break;
    }
}

void Register::fumul_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) *= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) *= val; break;
    }
}

void Register::fdiv_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::fidiv_noc(u8 reg1, u8 reg2)
{
    i64 val = getival(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::fidivr_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((i8 *) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 2: (*((i16*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 4: (*((i32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((i64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::fudiv_noc(u8 reg1, u8 reg2)
{
    u64 val = getval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 4: (*((f32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((f64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::fudivr_noc(u8 reg1, u8 reg2)
{
    f64 val = getfval(reg2);
    switch((reg1 & 0xF) + 1)
    {
    case 1: (*((u8 *) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 2: (*((u16*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 4: (*((u32*) (m_bytes + (reg1 >> 4)))) /= val; break;
    case 8: (*((u64*) (m_bytes + (reg1 >> 4)))) /= val; break;
    }
}

void Register::fneg_noc(u8 reg)
{
    switch((reg & 0xF) + 1)
    {
    case 4: (*((u32*) (m_bytes + (reg >> 4)))) ^= 1 << 31; break;
    case 8: (*((u64*) (m_bytes + (reg >> 4)))) ^= 1L << 63; break;
    }
}

