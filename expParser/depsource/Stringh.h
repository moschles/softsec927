typedef struct {
	long int length;
	unsigned char allocated;
	char * cd;
} __String_structure;


typedef __String_structure * String;


typedef struct {
	long int idx;
	long int capacity;
	unsigned char allocated;
	char * data;
} __StringBuilder_structure;


typedef __StringBuilder_structure * StringBuilder;

// This is not S_free(). Why? see Stringc.c for details. 
void S_xfreex( String S );   

String S_new( void ); 
String S_empty( void ); 
String S_newInitL( const char * );
String S_newInit( char cs[] ); 
String S_newInitch( char k ); 
String S_copy( String oS ); 
int S_length( String S );
int S_size( String S ); 

// Return the character located at position index i
char S_apply( String sA , int i );

// Set the ith character to k
// Return 1 if i was inside the length of sA.
// Return -1 otherwise.
int S_set( String sA , int i, char k );

// Print the string sA to the console.
void S_printf( String sA );

// Print the string sA to the standard error stream. 
void S_stderr( String sA );

// Print the string sA to a given stream.
void S_fprintf(  String sA ,  FILE * stream ); 

/*
 Return a null-terminated char array.
  This function will malloc() a new array.   */ 
char * S_Cstyle( String S );

// Fill a null-terminated char array with the String S.
void S_CstylePlace( String S , char carr[] ); 

// Return 1 if S is empty.   Otherwise 0. 
int S_isEmpty( String S ); 

// Return concatenation  sA + sB
String S_plus( String sA , String sB );
String S_plusL( String sA , const char * sB ); 
String S_plusch( String sA , char sB ); 

// Return sA with all instances of sB removed from it.
String S_minus( String sA , String sB );
String S_minusL( String sA , const char * sB ); 
String S_minusch( String sA , char sB );

// Remove all whitespace from sA
String S_printable( String sA ); 

/* Replace all whitespace in sA with character 'code'
Most useful for stripping whitespace but keeping the space characters. */
String S_printableFilter( String sA , int code ); 

/* Remove run-length duplicates of character 'c', 
replacing the runs with character 'r'. 
Most useful in replacing tabs with spaces.  */ 
String S_telescope( String sA , char c , char r );


// Return sA with the first instance of query removed from it.
String S_extract( String sA , String query );
String S_extractL( String sA , const char * query );
String S_extractch( String sA , char query );

// Return sA with instances of query replaced with sR
String S_replace( String sA , String query,  String sR );
String S_replacecfc( String sA , char query,  char sR );
String S_replacelfl( String sA , const char * query , const char * sR );

// Return the total number of appearances of query in S.  
int S_appears( String S , String query );
int S_appearsL( String S , const char * query );
int S_appearsch( String S , char query ); 


/*
 Split sA along the delimeters in delims. 
 Expect tokens to be an array of String of appropriate size. 
 Return the number of tokens produced by the splitting.
 
 No capacity check is performed on `tokens`     */
int S_split( String sA , String delims , String * tokens );
int S_splitL( String sA , const char * delims , String * tokens );



/*
 Split sA along the delimeters.
 delimeters are determined by whether they do not appear in 'idelims'
 Expect tokens to be an array of String of appropriate size. 
 Return the number of tokens produced by the splitting.
 
 No capacity check is performed on `tokens`     */
int S_splitInverse( String sA , String idelims , String * tokens );
int S_splitInverseL( String sA , const char * idelims , String * tokens );


/*
Return a version of sA, which only contains the characters included
in the set of characters given by 'filter'. 
Example
	sA = "12 - 3  +  8/2 + 61"
	sB = S_filterSetL( sA , "*+-/" );
	sB == "-+/+"     
*/ 
String S_filterSet( String sA , String filter );
String S_filterSetL( String sA , const char * filter) ;

/*
Return a version of sA, which only contains the characters 
which do not appear in 'ifilter'. 
Example
	sA = "12 - 3  +  8/2 + 61  "
	sB = S_filterComplementL( sA , "*+-/" );
	sB == 12  3    82  61  "
	*/ 
String S_filterComplement( String sA , String ifilter );
String S_filterComplementL( String sA , const char * ifilter) ;


/*
Apply the function pointed to by evalFxn to each charcter in sA.
Keep only those characters for which that function evaluates
to 1.  Any characters for which that function evaluates to 
something other than 1 are removed.  
Most useful for purposes of custom whitespace.  */
String S_withFilter( String sA , int (*evalFxn)( char ) ); 

/*
Apply the function pointed to by evalFxn to each charcter in sA.
Keep only those characters for which that function evaluates
to 1.  Any characters for which that function evaluates to 
something other than 1 are removed. 

int (*evalFxn)( char  left  , char  mid  , char  right  )

'left' is the characters to the left of the currently-tested 'mid'.
'right' is the character to the right of the currently-tested 'mid'.
'mid' will be kept in the return String whenever the function pointed to 
by evalFxn evaluates to 1. 

S_midFilter() proceeds by mark-and-sweep.  The first character and last
character of sA is always included.  If the desired evaluation function 
ignores right or left characters, the function should be written in such 
a way that ignores them. 

S_midFilter() is most useful in finding erronious spaces in numbers.
For example, if an expression parser is given as input "12   46 +   8"  
and the spaces are stripped , we have "1246+8" which appears to be
a valid expression, but should invoke an error.
*/
String S_midFilter( String sA , int (*evalFxn)( char    , char   , char   ) ); 


/*
Return a transformation of characters in sA to an array of
integers.  

int (*transformFxn)( char ec  , int  pos )
transformFxn is a pointer to a function that
evaluates each character of sA and returns a corresponding int.
'pos' is the zero index of each character.

S_map()  mallocates the returned integer array.
S_map() is best used for mark-and-sweep
*/
int * S_map( String sA , int (*transformFxn)( char   , int   ) ); 


/*
Create and return a String whose characters are built out of a transformation
 of integers. Expect an array of int 'range' of size 'rangesz'.  transformFxn 
 is a pointer to a function that takes each integer and its index position 
 and returns a corresponding char.  */
String S_mapInverse( int range[] , int rangesz , char (*transformFxn)( int ri , int pos ) ); 


/*
sideFxn is a pointer to a function that is called for each character in sA. 
Presumably that function will have some side effects.

int (*sideFxn)( char sc , int pos , void * extra )

 For each character, 
'sc' is the character at index 'pos'.  'extra'  can be used to supply 
additional data to the function according to need.  
It could also be used for storing results.  */
void S_forEach( String sA , int (*sideFxn)(   char,int,void * extra  ) , void * user_extra ); 

 


/*
Return the parenthesese depth of the ith character of sA. 
Any characters in 'leftParen' are considered left parenthesese.
ANy character in 'rightParen' are considered right parenthesese. 
Return 0 if  the ith character is at the "top" level of depth.
Return (-1) if the i is outside the bounds of sA.
Return (-2) if the parenthesese are not balanced up to the ith character.
Return (-4) if any character appears in both leftParen and rightParen.
*/
int S_parenthesesDepth( String sA, int i , String leftParen, String rightParen ); 
int S_parenthesesDepthL( String sA, int i , const char * lefParen , const char * rightParen ); 

/*
 Split sA at the location index. 
 Expect `segments` to be an array of String of at least size 2.
 The String at segments[0] starts at index 0.
 The String at segments[1] starts at index 'index'. 
 
No capacity check is performed on `segments`  
S_partition() will accept any possible value of 'index' including
negative values, and always return two Strings in 'segments'. 
index falling outside the range on either side will produce
empty Strings in 'segments' appropriately.    */
void S_partition( String sA, int index , String * segments );




/*
Strip all duplicate characters from String sA. 
  
The resulting returned String will have one of each character that
appears within sA.
Example
	sA = "q,w,e,r,t,y,t,e,r,y,w,q,x"
	sB = S_unique( sA )
	sB == "q,wertyx"
	
The duplicates need not be contiguous.
( To strip contiguous runs of characters, use S_telescope() instead)*/
String S_unique( String sA ); 


/*
Pad sA  with character 'pad' until it reaches the specified length.
Padding characters will appear on the left.  */
String S_padLeft( String sA, char pad , int length );

/*
Pad sA  with character 'pad' until it reaches the specified length.
Paddiong characters will appear on the right.  */
String S_padRight( String sA, char pad , int length );


/*
Return 0 if sA == sB.
Return -1 if sA < sB
Retrurn 1 if sA > sB */
int S_compare( String sA,  String sB ); 
int S_compareL( String sA,  const char * sB ); 

/*
Return 1 if sA is greater than sB.
Return 0 otherwise */
int  S_greaterThan( String sA, String sB ); 
int  S_greaterThanL( String sA, const char * sB );


/*
Return 1 if sA is lesser than sB.
Return 0 otherwise */
int  S_lessThan( String sA, String sB ); 
int  S_lessThanL( String sA, const char * sB );

/*
Return 1 if sA is equal to sB.
Return 0 otherwise */
int  S_equal( String sA, String sB ); 
int  S_equalL( String sA, const char * sB );

/*
Return 1 if sA is greater than or equal to sB 
return 0 otherwise */
int  S_greaterThanEqual( String sA, String sB ); 
int  S_greaterThanEqualL( String sA, const char * sB );

/*
Return 1 if sA is lesser than or equal to sB 
return 0 otherwise */
int  S_lessThanEqual( String sA, String sB ); 
int  S_lessThanEqualL( String sA, const char * sB );


// Return a new string that is the lowercase version of S
String S_toLower( String S );

// Return a new string that is the uppercase version of S
String S_toUpper( String S );

// Return a string that is the concatenation  (sp + sA)
String S_prepend( String sp , String sA );
String S_prependL( const char * sp , String sA );
String S_prependch( char sp , String sA ); 

/*
 Return a String that is S with its first character removed.
  Return the removed character into `top`      */
String S_pop( String S , char * top );


/*
Return a String that is S without its last character.
Return the removed character into `b`    */
String S_init( String S , char * b ); 

// Combine all the String in arr.  
//  `total` is the  number of String in arr[] 
String S_combine( String * arr , int total );


// Return sA with its first n characters missing.
String S_drop( String sA , int n ); 

// Return sA with its last n characters missing.
String S_dropRight( String sA , int n ); 


/* Remove a run of character t off the left of sA, 
going rightwards until a character other than t is found. */
String S_trim(  String sA , char t ); 

/* Remove a run of character t off the end of sA,
going leftwards until a character other than t is found. */ 
String S_trimRight( String sA, char t ); 


/* 
Return the index of the first instance of `query` in S.
Return -1 if  `query` does not appear in S    */
int S_find( String S ,  String query );
int S_findL( String S , const char * query );
int S_findch( String S,  char query );

/* 
Return the index of the last instance of `query` in S.
Return -1 if  `query` does not appear in S    */
int S_findBack( String S ,  String query );
int S_findBackL( String S , const char * query );
int S_findBackch( String S,  char query );

/*  
Find all the occurances of `query` in sA .
Return 0 if `query` does not occur in sA.
Otherwise return the number of times it occurs.
Populate `indeces` with all the zero-based locations
where the query string was found. */
int S_findAll( String S ,  String query ,  int indeces[] );
int S_findAll_L( String S , const char * query ,  int indeces[]  );
int S_findAll_ch( String S,  char query ,   int indeces[]  );

/* Return 1 if  S ends with query. 
Return 0 if S does not end with query.   */
int S_endsWith( String S, String query );
int S_endsWithL( String S, const char * query );
int S_endsWithch( String S, char query );

// Return the supplied String in reverse order.
String S_reverse( String S );

// Return the sum of the characters in the supplied String.
int S_sum( String S );

// Return the largest character in S, by ASCII code.
char S_max( String S );

// Return the smallest character in S, by ASCII code.
char S_min( String S ); 

// Return a version of S where its characters are sorted. 
String S_sorted( String S );


// * // * //

// * // * //

void SB_free( StringBuilder B ); 
StringBuilder SB_new( void ); 
StringBuilder SB_empty( void ); 
StringBuilder SB_newInitL( const char * literal );
StringBuilder SB_newInit( char cs[] ); 
StringBuilder SB_newInitch( char k ); 
StringBuilder SB_newInitSt( String osa ); 
StringBuilder SB_copy( StringBuilder oB ); 
int SB_length( StringBuilder B );
int SB_size( StringBuilder B ); 
long int SB_capacity( StringBuilder B );

/*
 Return a null-terminated char array.
  This function will malloc() a new array.   */ 
char * SB_Cstyle( StringBuilder B );

// Fill a null-terminated char array with the StringBuilder B.
void SB_CstylePlace( StringBuilder B , char carr[] ); 

// Return a  String version of the builder B 
String SB_toString( StringBuilder B );

// Return 1 if B is empty.   Otherwise 0. 
int SB_isEmpty( StringBuilder B ); 

// Print the StringBuilder to the console.
void SB_printf( StringBuilder B );

// Print the StringBuilder to the standard error stream. 
void SB_stderr( StringBuilder B );

// Print the StringBuilder to a given stream.
void SB_fprintf(  StringBuilder B ,  FILE * stream ); 

// Append a new string onto the supplied StringBuilder B
void SB_append( StringBuilder B ,  String sA );
void SB_appendL( StringBuilder B ,  const char * sA );
void SB_appendch( StringBuilder B ,  char sA );
void SB_appendCS( StringBuilder B , char sA[] ); 

//  Walk the symbolic length backwards by n characters.
void SB_cut( StringBuilder B , int n );  

// Walk the symbolic length backwards until the first
//  instance of sK is found.  Leave sK in B.
void SB_cutUntil( StringBuilder B, char sK ); 

//  Re-allocate the StringBuilder B to a larger capacity.
//  Do not alter its current symbolic contents.
void SB_growCapacity( StringBuilder B );  

/*
 Re-allocate the StringBuilder B so that if n characters were
 to be append()'d to its existing contents, the capacity
 could accomodate them.   B's symbolic content is not modified.   */
void SB_growToFit( StringBuilder B , long int n ); 

// Return the first character in the StringBuilder's contents
char SB_first ( StringBuilder B );

// Return the last character in the StringBuilder's contents.
char SB_last( StringBuilder B );

/* Return 1 if  S ends with query. 
Return 0 if S does not end with query. 
Return 0 if query is an empty String.   */
int SB_endsWith( StringBuilder B ,  String query );
int SB_endsWithL( StringBuilder B ,  const char * query );
int SB_endsWithch( StringBuilder B ,  char query );

// Return the last n characters in B as a String
//   B is not altered. 
String SB_dequeue( StringBuilder B , long int n );


