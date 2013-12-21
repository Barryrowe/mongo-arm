// atomic_int.h
// atomic wrapper for unsigned

/*    Copyright 2009 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

namespace mongo {

    struct AtomicUInt {
        AtomicUInt() : x(0) {}
        AtomicUInt(unsigned z) : x(z) { }

        operator unsigned() const { return x; }
        unsigned get() const { return x; }
        inline void set(unsigned newX);

        inline AtomicUInt operator++(); // ++prefix
        inline AtomicUInt operator++(int);// postfix++
        inline AtomicUInt operator--(); // --prefix
        inline AtomicUInt operator--(int); // postfix--
        inline void signedAdd(int by);
        inline void zero() { x = 0; } // TODO: this isn't thread safe
        volatile unsigned x;
    };

#if defined(__ARMEL__) || defined(__ARM_ARCH_5T__) || defined(__ARM_PCS) || defined(__ARM_EABI__)

#define arm_atomic_add_inline(ptr, val) \
    ({ register unsigned int *__ptr asm("r2") = (ptr); \
      register unsigned int __result asm("r1"); \
      asm volatile ( \
          "1: @ atomic_add\n\t" \
          "ldr     r0, [r2]\n\t" \
          "mov     r3, #0xffff0fff\n\t" \
          "add     lr, pc, #4\n\t" \
          "add     r1, r0, %2\n\t" \
          "add     pc, r3, #(0xffff0fc0 - 0xffff0fff)\n\t" \
          "bcc     1b" \
          : "=&r" (__result) \
          : "r" (__ptr), "rIL" (val) \
          : "r0","r3","ip","lr","cc","memory" ); \
      __result; })

#define atomic_int_helper(ptr, val) \
    (arm_atomic_add_inline(ptr, (val)) - (val))

    inline void AtomicUInt::set(unsigned newX) { asm volatile("" ::: "memory"); x = newX; }

    AtomicUInt AtomicUInt::operator++() {
        return atomic_int_helper((unsigned *)&x, 1)+1;
    }
    AtomicUInt AtomicUInt::operator++(int) {
        return atomic_int_helper((unsigned *)&x, 1);
    }
    AtomicUInt AtomicUInt::operator--() {
        return atomic_int_helper((unsigned *)&x, -1)-1;
    }
    AtomicUInt AtomicUInt::operator--(int) {
        return atomic_int_helper((unsigned *)&x, -1);
    }

#else
#error "unsupported compiler or platform"
#endif

} // namespace mongo
