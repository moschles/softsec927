

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Stringh.h"
#include "SB_unitTest.h"
#include "expressionParser.h"

//#define	EXPRESSPARSEDEBUG		__express_parse_debug
#define true			1
#define false			0

typedef int boolean;

#include "chatters.h"


int performUnitTests( int eval );
void cleanPrintFloat( double d );
void testcPF( void ) ;
void smallTestCompare( char expression[] , double ansC99 );
const char * firstFxn( int ff );
const char * secondFxn( int sf );
int descrim( int q, int p ) ;
//.

const char * firstFxn( int ff )
{
	if( ff == 1 ) {
		return( "first f" );
	} else {
		return( "gg" );
	}
}

const char * secondFxn( int sf )
{
	if( sf == 1 ) {
		return( "second f" );
	} else {
		return( "xx" );
	}
}

int descrim( int q, int p )
{
	return(  (q==p) );
}

// * // * //

int performUnitTests( int eval )
{
	int fails;
	int sbf , sutf, sutbf, sutcf , sutdf , sutef , sutff;
	fails = 0;

	if( eval==0) {

        sbf = sutf= sutbf= sutcf = sutdf = sutef = sutff= 0;

		printf("===== RUNNING StringBuilder Unit Tests ==========\n");
		sbf = 	SB_unitTest( 0 ) ;

		printf("===== RUNNING String Unit Test suite   ==========\n");
		sutf = String_unitTest( 0 );

		printf("===== RUNNING String Unit Test suite b ==========\n");
		sutbf = String_unitTest_b( 0 );

		printf("===== RUNNING String Unit Test suite c ==========\n");
		sutcf = String_unitTest_c( 0 );

		printf("===== RUNNING String Unit Test suite d ==========\n");
		sutdf = String_unitTest_d( 0 );

		printf("===== RUNNING String Unit Test suite e ==========\n");
		sutef = String_unitTest_e( 0 );

		printf("===== RUNNING String Unit Test suite f ==========\n");
		sutff = String_unitTest_f( 0 );

		fails = sbf+sutf+sutbf+sutcf + sutdf + sutef + sutff;

		if( fails == 0 ) {
			printf("\n============\n{}   All tests passed.\n");
		} else {
			if( fails == 1 ) {
				printf("\n============\n1 test failed@!\n"   );
			} else {
				printf("\n============\n%d tests failed@!\n" , fails );
			}
		}

	}

	return ( fails );
}



void cleanPrintFloat( double d )
{
	String post = postProcessRealNumber( d );
	S_printf( post );
	printf( "\n" );
	S_xfreex( post );
}


void testcPF( void )
{
		double tryrn;
	tryrn = 90.1234567e1;
	printf("xe1	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e2;
	printf("xe2	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e3;
	printf("xe3	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e4;
	printf("xe4	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e5;
	printf("xe5	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e6;
	printf("xe6	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e7;
	printf("xe7	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e8;
	printf("xe8	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e9;
	printf("xe9	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e12;
	printf("xe12	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e15;
	printf("xe15	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e18;
	printf("xe18	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e22;
	printf("xe22	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e25;
	printf("xe25	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e28;
	printf("xe28	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e32;
	printf("xe32	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );


	// * // * //

	tryrn = 0.000000;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 707303.000000;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 1.000000;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 3.000000;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 13.000000;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 29.000000;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	double pr,qr;
	pr = 293.700;
	qr = 101.700;

	tryrn = pr-qr;
	printf(" s  , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e1;
	printf("xe1	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-1;
	printf("xe-1	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-2;
	printf("xe-2	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-3;
	printf("xe-3	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-4;
	printf("xe-4	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-5;
	printf("xe-5	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-6;
	printf("xe-6	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-7;
	printf("xe-7	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-8;
	printf("xe-8	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-12;
	printf("xe-12	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-17;
	printf("xe-17	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-20;
	printf("xe-20	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );

	tryrn = 90.1234567e-24;
	printf("xe-24	 , %lf\n",  tryrn );
	cleanPrintFloat( tryrn );
}


void smallTestCompare( char expression[] , double ansC99 )
{
	int errorcode =-9902;
	double answer;
	printf( "%s\n" , expression );
	answer = evaluateExpressionArr( expression ,  &errorcode );
	printf("\t= ");
	cleanPrintFloat(answer);
	printf("\t= %e  (C99)\n" , ansC99 );
	chatter("errorcode was ");
	chatteri(errorcode);
	chendl();
}

// /////////////////////////////
//  MAIN ENTRY
// ////////////////////////////
int main(int argc, char *argv[])
{
	char userin[80];
	char expression[256];
	int eval, utfails;
	double answerC99;
	//.

	printf("user? >");
	scanf( "%s" , userin );
	eval = strcmp( userin , "g" );
	if( eval != 0 ) {
		return( 1 );
	}

	// Unit tests.
	utfails = performUnitTests( eval );
	if( utfails > 0 ) {
		return( 1 );
	}


	// ===
	strcpy( expression , "(124-122)*(3+1)" );
	answerC99           = (124.0-122.0)*(3.0+1.0);
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(2+3*4+5-6/7*3+8*9/2)-(21/3+4)*(1+8-(7+1)+0)-94" );
	answerC99           = (2.0+3.0*4.0+5.0-6.0/7.0*3.0+8.0*9.0/2.0)-(21.0/3.0+4.0)*(1.0+8.0-(7.0+1.0)+0.0)-94.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(.2+.3*.4+.5-.6/.7*.3+.8*.9/.2)-(.21/.3+.4)*(.1+.8-(.7+.1)+.0)-.94" );
	answerC99           = (.2+.3*.4+.5-.6/.7*.3+.8*.9/.2)-(.21/.3+.4)*(.1+.8-(.7+.1)+.0)-.94;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(  197.31e7 -  177.93e+8 )   *  (  -3.800e-14   + 1.019e-13  )" );
	answerC99           = (  197.31e7 -  177.93e+8 )   *  (  -3.800e-14   + 1.019e-13  );
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(     ( (-104+122) * (((-8)+   2))  ))" );
	answerC99           = (     ( (-104.0+122.0) * (((-8.0)+   2.0))  ));
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "1.93002e7" );
	answerC99           = 1.93002e7;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "(( () * ((())) ))" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(2+3) * " );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "  * (8+7)" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "(13*12.06) +" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "+ (13*12.06)" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "3.6*/9.1" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "3.6--9.1" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "3.6-+9.1" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "3.6.2 - 9.1" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "3.6 * 9..1" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "." );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "e-12" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(  3+2  (" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	// ===
	strcpy( expression , "(2+3)-(21/3)*(  1+8-(7+1(+(0+(2*8))+6  )-94" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );

	// ===
	strcpy( expression , "(( (1.2) * ((())) ))" );
	answerC99           = -1.0;
	smallTestCompare( expression , answerC99 );


	int n = 4;

	const char * construct =  ( ( descrim(n,41) ) ?
		firstFxn(1) :
		secondFxn(56) );

	printf("construct =  %s\n" , construct );


	return( 0 );
}




