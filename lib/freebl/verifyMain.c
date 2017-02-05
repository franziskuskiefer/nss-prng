#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "blapi.h"
#include "secutil.h"


#define INPUT_AMOUNT 32
#define OUTPUT_AMOUNT 32

//#define INF_TEST_A
//#define INF_TEST_B


	unsigned char* in = 0;
	unsigned char* out = 0;


int main(){
	unsigned char input;
	unsigned char output;
	int i;

	in = (unsigned char*) malloc(INPUT_AMOUNT);
	out = (unsigned char*) malloc(OUTPUT_AMOUNT);
	for(i = 0; i < INPUT_AMOUNT; i++){
	  input = in[i];
	}
#if defined(INF_TEST_A) && defined(INF_TEST_B)
	#error
#endif
#ifdef INF_TEST_A
	#include "ex_a.c"
#endif
#ifdef INF_TEST_B
	#include "ex_b.c"
#endif

#ifndef __CPROVER__
	printf("\nINPUT:\n");
	for(i = 0; i < INPUT_AMOUNT; i++){
	  printf("%02x", in[i]);
	}
	printf("\n");
#endif


        SECStatus rv = SECFailure;
        assert(INPUT_AMOUNT==OUTPUT_AMOUNT);
        rv = my_rng_init(in, INPUT_AMOUNT, out);
        if (rv != PR_SUCCESS) {
            SECU_PrintPRandOSError("");
            return -1;
        }

        rv = RNG_GenerateGlobalRandomBytes(out, OUTPUT_AMOUNT);
        if (rv != SECSuccess) {
            SECU_PrintPRandOSError("");
            return -1;
        }


	printf("\nOUTPUT:\n");
	for(i = 0; i < OUTPUT_AMOUNT; i++){
	  output = out[i];
	  printf("%02x", out[i]);
	}/*
	for(i = 0; i < 22; i++){
	  output = state[i];
	  printf("%02x", state[i]);
	}*/
	printf("\n");

#if !defined(INF_TEST_A) && !defined(INF_TEST_B)
#ifndef INF_NO_ASSERT
	assert(0);
#endif
#endif
	return 0;
}
