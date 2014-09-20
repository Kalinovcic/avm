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

    inline void clear(u8 reg)               { clear_check(reg);       clear_noc(reg);       }
    inline void load(u8 reg, void* p_val)   { load_check(reg, p_val); load_noc(reg, p_val); }
    inline void mov(u8 reg1, u8 reg2)       { mov_check(reg1, reg2);  mov_noc(reg1, reg2);  }
    inline void swap(u8 reg1, u8 reg2)      { swap_check(reg1, reg2); swap_noc(reg1, reg2); }

    inline void util_load8(u8 reg, u8 val)   { load_check(reg, &val); loadreg(reg, 1, &val); }
    inline void util_load16(u8 reg, u16 val) { load_check(reg, &val); loadreg(reg, 2, &val); }
    inline void util_load32(u8 reg, u32 val) { load_check(reg, &val); loadreg(reg, 4, &val); }
    inline void util_load64(u8 reg, u64 val) { load_check(reg, &val); loadreg(reg, 8, &val); }

    inline void inc(u8 reg)                 { inc_check(reg);           inc_noc(reg);         }
    inline void dec(u8 reg)                 { dec_check(reg);           dec_noc(reg);         }
    inline void neg(u8 reg)                 { neg_check(reg);           neg_noc(reg);         }
    inline void add(u8 reg1, u8 reg2)       { add_check(reg1, reg2);    add_noc(reg1, reg2);  }
    inline void sub(u8 reg1, u8 reg2)       { sub_check(reg1, reg2);    sub_noc(reg1, reg2);  }
    inline void mul(u8 reg1, u8 reg2)       { mul_check(reg1, reg2);    mul_noc(reg1, reg2);  }
    inline void div(u8 reg1, u8 reg2)       { div_check(reg1, reg2);    div_noc(reg1, reg2);  }
    inline void idiv(u8 reg1, u8 reg2)      { idiv_check(reg1, reg2);   idiv_noc(reg1, reg2); }

    inline void debug(u8 reg)
    {
        printf("%d\n", *((int*) (m_bytes + (reg >> 4))));
    }
private:
    u8 m_bytes[16];
    u8 m_buff[16];

    bool valid(u8 reg);
    bool valid_float(u8 reg);
    bool overlap(u8 reg1, u8 reg2);

    void loadreg(u8 reg, u8 srcsize, void* src);
    void tobuff(u8 reg);

    inline u8 tou8(u8 reg)   { return *((u8 *) (m_bytes + (reg >> 4))); }
    inline u16 tou16(u8 reg) { return *((u16*) (m_bytes + (reg >> 4))); }
    inline u32 tou32(u8 reg) { return *((u32*) (m_bytes + (reg >> 4))); }
    inline u64 tou64(u8 reg) { return *((u64*) (m_bytes + (reg >> 4))); }

    inline f32 tof32(u8 reg) { return *((f32*) (m_bytes + (reg >> 4))); }
    inline f64 tof64(u8 reg) { return *((f64*) (m_bytes + (reg >> 4))); }

    inline u64 getval(u8 reg)
    {
        switch((reg & 0xF) + 1)
        {
        case 1: return tou8(reg);
        case 2: return tou16(reg);
        case 4: return tou32(reg);
        case 8: return tou64(reg);
        }
        return 0;
    }

    inline f64 getfval(u8 reg)
    {
        switch((reg & 0xF) + 1)
        {
        case 4: return tof32(reg);
        case 8: return tof64(reg);
        }
    }

    inline void scheck1(u8 r, bool f, int ec)
    {
        if(f) { if(!valid_float(r)) exit(ec); }
        else    if(!valid(r)) exit(ec);
    }

    inline void scheck2nl(u8 r1, bool f1, u8 r2, bool f2, int ec)
    {
        scheck1(r1, f1, ec);
        scheck1(r2, f2, ec);
    }

    inline void scheck2(u8 r1, bool f1, u8 r2, bool f2, int ecinv, int eclap)
    {
        scheck2nl(r1, f1, r2, f2, ecinv);
        if(overlap(r1, r2)) exit(eclap);
    }

    inline void intc1(u8 r, int ec)                     { scheck1(r, 0, ec); }
    inline void floatc1(u8 r, int ec)                   { scheck1(r, 1, ec); }
    inline void intc2(u8 r1, u8 r2, int ec1, int ec2)   { scheck2(r1, 0, r2, 0, ec1, ec2); }
    inline void intc2nl(u8 r1, u8 r2, int ec1)          { scheck2nl(r1, 0, r2, 0, ec1); }
    inline void floatc2(u8 r1, u8 r2, int ec1, int ec2) { scheck2(r1, 1, r2, 1, ec1, ec2); }
    inline void floatc2nl(u8 r1, u8 r2, int ec1)        { scheck2nl(r1, 1, r2, 1, ec1); }

    inline void clear_check(u8 reg)             { intc1(reg, ECINVCLEAR); }
    inline void load_check(u8 reg, void* p_val) { intc1(reg, ECINVLOAD); }
    inline void mov_check(u8 reg1, u8 reg2)     { intc2(reg1, reg2, ECINVMOV, ECLAPMOV); }
    inline void swap_check(u8 reg1, u8 reg2)    { intc2(reg1, reg2, ECINVSWAP, ECLAPSWAP);}

    inline void inc_check(u8 reg)               { intc1(reg, ECINVINC); }
    inline void dec_check(u8 reg)               { intc1(reg, ECINVDEC); }
    inline void neg_check(u8 reg)               { intc1(reg, ECINVNEG); }
    inline void add_check(u8 reg1, u8 reg2)     { intc2nl(reg1, reg1, ECINVADD); }
    inline void sub_check(u8 reg1, u8 reg2)     { intc2nl(reg1, reg1, ECINVSUB); }
    inline void mul_check(u8 reg1, u8 reg2)     { intc2nl(reg1, reg1, ECINVMUL); }
    inline void div_check(u8 reg1, u8 reg2)     { intc2nl(reg1, reg1, ECINVDIV); }
    inline void idiv_check(u8 reg1, u8 reg2)    { intc2nl(reg1, reg1, ECINVIDIV); }
    inline void fadd_check(u8 reg1, u8 reg2)    { scheck2nl(reg1, 1, reg2, 1, ECINVFADD); }
    inline void fiadd_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFIADD); }
    inline void fuadd_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFUADD); }
    inline void fsub_check(u8 reg1, u8 reg2)    { scheck2nl(reg1, 1, reg2, 1, ECINVFSUB); }
    inline void fisub_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFISUB); }
    inline void fisubr_check(u8 reg1, u8 reg2)  { scheck2nl(reg1, 0, reg2, 1, ECINVFISUBR); }
    inline void fusub_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFUSUB); }
    inline void fusubr_check(u8 reg1, u8 reg2)  { scheck2nl(reg1, 0, reg2, 1, ECINVFUSUBR); }
    inline void fmul_check(u8 reg1, u8 reg2)    { scheck2nl(reg1, 1, reg2, 1, ECINVFMUL); }
    inline void fimul_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFIMUL); }
    inline void fumul_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFUMUL); }
    inline void fdiv_check(u8 reg1, u8 reg2)    { scheck2nl(reg1, 1, reg2, 1, ECINVFDIV); }
    inline void fidiv_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFIDIV); }
    inline void fidivr_check(u8 reg1, u8 reg2)  { scheck2nl(reg1, 0, reg2, 1, ECINVFIDIVR); }
    inline void fudiv_check(u8 reg1, u8 reg2)   { scheck2nl(reg1, 1, reg2, 0, ECINVFUDIV); }
    inline void fudivr_check(u8 reg1, u8 reg2)  { scheck2nl(reg1, 0, reg2, 1, ECINVFUDIVR); }
    inline void fneg_check(u8 reg1, u8 reg2)    { floatc1(reg1, ECINVFNEG); }

    void clear_noc(u8 reg);
    void load_noc(u8 reg, void* p_val);
    void mov_noc(u8 reg1, u8 reg2);
    void swap_noc(u8 reg1, u8 reg2);

    void inc_noc(u8 reg);
    void dec_noc(u8 reg);
    void neg_noc(u8 reg);
    void add_noc(u8 reg1, u8 reg2);
    void sub_noc(u8 reg1, u8 reg2);
    void mul_noc(u8 reg1, u8 reg2);
    void div_noc(u8 reg1, u8 reg2);
    void idiv_noc(u8 reg1, u8 reg2);
};

#endif /* REG_H_ */
