/*
 * Copyright 1994-2010 Clozure Associates
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define WORD_SIZE 64
#define PLATFORM_OS PLATFORM_OS_SOLARIS
#define PLATFORM_CPU PLATFORM_CPU_X86
#define PLATFORM_WORD_SIZE PLATFORM_WORD_SIZE_64

typedef struct ucontext ExceptionInformation;

#define MAXIMUM_MAPPABLE_MEMORY (512L<<30L)
#define IMAGE_BASE_ADDRESS 0x300000000000L

#include "lisptypes.h"
#include "x86-constants64.h"

#define xpGPRvector(x) ((x)->uc_mcontext.gregs)
#define xpGPR(x,gprno) (xpGPRvector(x)[gprno])
#define set_xpGPR(x,gpr,new) xpGPR((x),(gpr)) = (natural)(new)
#define xpPC(x) xpGPR(x,Iip)
#define eflags_register(xp) xpGPR(xp,Iflags)
#define xpXMMregs(x)(&((x)->uc_mcontext.fpregs.fp_reg_set.fpchip_state.xmm[0]))
#define xpMXCSR(x) ((x)->uc_mcontext.fpregs.fp_reg_set.fpchip_state.mxcsr)
#define SIGNUM_FOR_INTN_TRAP SIGSEGV
#define IS_MAYBE_INT_TRAP(info,xp) ((xpGPR(xp,REG_TRAPNO)==0xd)&&((xpGPR(xp,REG_ERR)&7)==2))
#define IS_PAGE_FAULT(info,xp) (xpGPR(xp,REG_TRAPNO)==0xe)
#define SIGRETURN(context) setcontext(context)

#include "os-solaris.h"
