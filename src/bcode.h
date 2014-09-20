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
 * File: bcode.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef BCODE_H_
#define BCODE_H_

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "atype.h"

class Bytecode
{
public:
    Bytecode(u8* begin, u8* end)
    : m_begin(begin), m_current(begin), m_end(end)
    {
        if(begin > end) exit(AVMEXIT_INTERNLOGIC);
    }

    ~Bytecode() {}

    inline bool eof() { return m_current == m_end; }

    inline u8 next() { return *(m_current++); }
    inline void next(void* ptr, asize size)
    {
        if(m_current + size > m_end)
            exit(AVMEXIT_EOF);
        memcpy(ptr, m_current, size);
        m_current += size;
    }

    inline u8 next8() { return next(); }
    inline u16 next16() { u16 result; next(&result, 2); return result; }
    inline u32 next32() { u32 result; next(&result, 4); return result; }
    inline u64 next64() { u64 result; next(&result, 8); return result; }

    inline u8* nextString()
    {
        u8* strptr = m_current;
        while(*(m_current++));
        return strptr;
    }
private:
    u8* m_begin;
    u8* m_current;
    u8* m_end;
};

#endif /* BCODE_H_ */
