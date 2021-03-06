#
# Copyright 1994-2001 Clozure Associates
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

OPENMCL_MAJOR_VERSION=0
OPENMCL_MINOR_VERSION=14

VPATH = ../
RM = /bin/rm
# Versions of GNU as >= 2.9.1 all seem to work
# AS = gas-2.9.1
AS = as
M4 = m4
ASFLAGS = -mregnames -mppc32
M4FLAGS = -DLINUX -DPPC
CDEFINES = -DLINUX -DPPC -D_REENTRANT -DSTATIC -D_GNU_SOURCE
CDEBUG = -g
COPT = -O2

# The only version of GCC I have that supports both ppc32 and ppc64
# compilation uses the -m32 option to target ppc32.  This may not be
# definitive; there seem to be a bewildering array of similar options
# in other GCC versions.  It's assumed here that if "-m32" is recognized,
# it's required as well.

PPC32 = $(shell ($(CC) --help -v 2>&1 | grep -q -e "-m32 ") && /bin/echo "-m32")

# Likewise, some versions of GAS may need a "-a32" flag, to force the
# output file to be 32-bit compatible.

A32 = $(shell ($(AS) --help -v 2>&1 | grep -q -e "-a32") && /bin/echo "-a32")

.s.o:
	$(M4) $(M4FLAGS) -I../ $< | $(AS) $(A32) $(ASFLAGS) -o $@
.c.o:
	$(CC) -I./ -c $< $(CDEFINES) $(CDEBUG) $(COPT) $(PPC32) -o $@

SPOBJ = pad.o ppc-spjump.o ppc-spentry.o ppc-subprims.o
ASMOBJ = ppc-asmutils.o imports.o

COBJ  = pmcl-kernel.o ppc-gc.o bits.o  ppc-exceptions.o \
	image.o thread_manager.o lisp-debug.o memory.o

DEBUGOBJ = lispdcmd.o plprint.o plsym.o plbt.o ppc_print.o
KERNELOBJ= $(COBJ) ppc-asmutils.o  imports.o
STATICOBJ= staticlib.o

SPINC =	lisp.s m4macros.m4 ppc-constants.s ppc-macros.s errors.s ppc-uuo.s ppc-constants32.s

CHEADERS = area.h bits.h ppc-constants.h lisp-errors.h gc.h lisp.h \
	lisp-exceptions.h lisp_globals.h macros.h memprotect.h image.h \
	threads.h ppc-constants32.h ppc-exceptions.h

# Subprims linked into the kernel ?
# Yes:

KSPOBJ = $(SPOBJ)
all:	../../static-ppccl


# No:

# KSPOBJ=
# all:	../../static-ppccl ../../subprims.so

OSLIBS =  -lm -lpthread


../../static-ppccl:	$(KSPOBJ) $(KERNELOBJ) $(DEBUGOBJ) $(STATICOBJ)
	$(CC) $(PPC32) $(CDEBUG) -static  -o $@ -T ../linux//elf32ppclinux.x $(KSPOBJ) $(KERNELOBJ) $(STATICOBJ) $(DEBUGOBJ) $(OSLIBS)


$(SPOBJ): $(SPINC)
$(ASMOBJ): $(SPINC)
$(COBJ): $(CHEADERS)
$(DEBUGOBJ): $(CHEADERS) lispdcmd.h
staticlib.o: external-functions.h staticlib.c
	$(CC) -c staticlib.c -fno-builtin $(CDEFINES) $(CDEBUG) $(COPT) $(PPC32) -o $@


external-functions.h:
	echo "Must generate external-functions.h from running lisp"


cclean:
	$(RM) -f $(KERNELOBJ) $(DEBUGOBJ) ../../ppccl

clean:	cclean
	$(RM) -f $(SPOBJ)

strip:	../../ppccl
	strip -g ../../ppccl
