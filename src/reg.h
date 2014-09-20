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
 * File: reg.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef REG_H_
#define REG_H_

#include "atype.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#define REGISTER_AH     0x00
#define REGISTER_AL     0x10
#define REGISTER_BH     0x20
#define REGISTER_BL     0x30
#define REGISTER_CH     0x40
#define REGISTER_CL     0x50
#define REGISTER_DH     0x60
#define REGISTER_DL     0x70
#define REGISTER_EH     0x80
#define REGISTER_EL     0x90
#define REGISTER_FH     0xA0
#define REGISTER_FL     0xB0
#define REGISTER_GH     0xC0
#define REGISTER_GL     0xD0
#define REGISTER_HH     0xE0
#define REGISTER_HL     0xF0

#define REGISTER_AX     0x01
#define REGISTER_BX     0x21
#define REGISTER_CX     0x41
#define REGISTER_DX     0x61
#define REGISTER_EX     0x81
#define REGISTER_FX     0xA1
#define REGISTER_GX     0xC1
#define REGISTER_HX     0xE1

#define REGISTER_EAB    0x03
#define REGISTER_ECD    0x43
#define REGISTER_EEF    0x83
#define REGISTER_EGH    0xC3

#define REGISTER_RAC    0x07
#define REGISTER_REG    0x87

class Register
{
public:
    Register();
    ~Register();

    inline void clear(u8 reg)               { clear_check(reg);         clear_unchecked(reg); }
    inline void load(u8 reg, void* p_val)   { load_check(reg, p_val);   load_unchecked(reg, p_val); }
    inline void mov(u8 reg1, u8 reg2)       { mov_check(reg1, reg2);    mov_unchecked(reg1, reg2); }
    inline void swap(u8 reg1, u8 reg2)      { swap_check(reg1, reg2);   swap_unchecked(reg1, reg2); }

    inline void util_load8(u8 reg, u8 val)   { load_check(reg, &val); load_register(reg, 1, &val); }
    inline void util_load16(u8 reg, u16 val) { load_check(reg, &val); load_register(reg, 2, &val); }
    inline void util_load32(u8 reg, u32 val) { load_check(reg, &val); load_register(reg, 4, &val); }
    inline void util_load64(u8 reg, u64 val) { load_check(reg, &val); load_register(reg, 8, &val); }

    inline void debug(u8 reg)
    {
        printf("%d\n", *((int*) (m_bytes + (reg >> 4))));
    }
private:
    u8 m_bytes[16];
    u8 m_buff[16];

    bool valid(u8 reg);
    bool overlap(u8 reg1, u8 reg2);

    void load_register(u8 reg, u8 srcsize, void* src);
    void to_buffer(u8 reg);

    void clear_check(u8 reg);
    void clear_unchecked(u8 reg);
    void load_check(u8 reg, void* p_val);
    void load_unchecked(u8 reg, void* p_val);
    void mov_check(u8 reg1, u8 reg2);
    void mov_unchecked(u8 reg1, u8 reg2);
    void swap_check(u8 reg1, u8 reg2);
    void swap_unchecked(u8 reg1, u8 reg2);
};

#endif /* REG_H_ */
