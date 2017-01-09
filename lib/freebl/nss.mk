HEADERS=$(shell find .. -name "*.h" )
PATH:=$(PATH):cbmc-5-1-win
CBMC=cbmc

U=\
prng_Hash_df.0:3


#Common vars
OPTS = -D NSS_USE_64
#SRC  =
INCLUDE_OPTS = -I ../../../dist/public/nss/ -I ../../../dist/Linux*_x86_64_cc_glibc_PTH_64_DBG.OBJ/include/ -I ../../../dist/private/nss/ -I mpi/

#Vars for compilation
RUN_OPTS = -L../../../dist/Linux*_x86_64_cc_glibc_PTH_64_DBG.OBJ/lib -lnssutil3 \
 -lplc4  -lnspr4  $(OPTS)
RUN_SRC  = verifyMain.c \
../../../dist/Linux*_x86_64_cc_glibc_PTH_64_DBG.OBJ/lib/libsectool.a  \
../../../dist/Linux*_x86_64_cc_glibc_PTH_64_DBG.OBJ/lib/libfreebl.a \

RUN_INCL = $(INCLUDE_OPTS)

#Vars for model checking
CBMC_OPTS = --gcc --unwindset "$(subst $(space),$(empty),$(U))" $(OPTS)
CBMC_SRC  = verifyMain.c drbg.c
CBMC_INCL = $(INCLUDE_OPTS)


compile:
	env USE_64=1 make -C ../.. nss_build_all

configure:
	true
