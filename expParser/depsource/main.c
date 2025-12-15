#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#pragma STDC FENV_ACCESS ON 
#include <fenv.h> 
#include "Stringh.h"
#include "expressionParser.h" 

//#define	EXPRESSPARSEDEBUG		__express_parse_debug
#define true			1
#define false			0

typedef int boolean;  

#include "chatters.h"


void cleanPrintFloat( double d );
static inline void enable_fp_traps(void);

void cleanPrintFloat( double d )
{
	String post = postProcessRealNumber( d );
	S_printf( post );
	printf( "\n" );
	S_xfreex( post );
}


static inline void enable_fp_traps(void) {
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
}

// /////////////////////////////
//  MAIN ENTRY
// ////////////////////////////
/*
 * rewrite the main()  to make it appropriate for fuzzing with AFL.
 * */
int main(int argc, char *argv[]) 
{
	if(argc < 2) return(1);
	FILE * fhandle  = fopen(argv[1], "r");
	if( fhandle==NULL ) return(1);
	fseek(fhandle,0,SEEK_END);
	size_t insize = ftell(fhandle);
	fseek(fhandle,0,SEEK_SET);
	if( insize > 250 ) {
		fclose(fhandle);
		return(1);
	}

	char expression[260];
	expression[250] = '\0';
	expression[251] = '\0';
	expression[259] = '\0';
	if(  (fread( (void *)expression, 1, insize, fhandle ))  != insize ) {
		fclose(fhandle);
		return(1);
	}
	expression[insize] = '\0';
	fclose( fhandle );
	fhandle=NULL;

    enable_fp_traps( ); 
    
	int errorcode =-9902;
	double answer = -1;
	answer = evaluateExpressionArr( expression ,  &errorcode );
	if( errorcode == VALIDEXPRESSION ) {
		cleanPrintFloat(answer);
		return(0);
	}
	return(-1);
}




