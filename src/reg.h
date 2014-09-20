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

#include <stdlib.h>
#include <string.h>

#define REGISTER 0x

class Register
{
public:
    Register();
    ~Register();

    inline void load(u8 reg, void* p_val);
    inline void mov(u8 reg1, u8 reg2);
private:
    u8 m_bytes[16];

    inline bool valid(u8 reg) { return (reg & 0xF) + (reg >> 4) < 16; }
    inline bool overlap(u8 reg1, u8 reg2);
};

#endif /* REG_H_ */
