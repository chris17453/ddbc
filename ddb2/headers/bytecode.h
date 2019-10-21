#include <stdio.h> 
#include <stdlib.h> 
#include "tokens.h"


// bytecode types
typedef enum  {
    KNOWN,              // tab, space, new line, linefeed
    UNKNOWN,            // tab, space, new line, linefeed
    WHITESPACE,         // tab, space, new line, linefeed
    STRING,             // a string, including block strings level 2
    
    //Spanning type for generic /group matching
    LITERAL,            // any NUMERIC BOLEAN, or STRING
    NUMERIC,            // any of INTEGER OR DECIMAL, DOUBLE, FLOAT
    INTEGER,            // any of TINYINT, SMALLINT, MEDIUMINT, INT, BIGINT, UNSIGNED_TINYINT, UNSIGNED_SMALLINT, UNSIGNED_MEDIUMINT, UNSIGNED_INT, UNSIGNED_BIGINT, 




    //DATA TYPES
    BOOLEAN,     // a bool    literal level 2
    DECIMAL,     // a stores the EXACT data
    DOUBLE,      //64 bit
    FLOAT,       //32bit
    TINYINT,     //1	-128	    0         127            255
    SMALLINT,    //2	-32768	    0         32767          65535
    MEDIUMINT,   //3	-8388608	0         8388607        16777215
    INT,         //4	-2147483648	0         2147483647     4294967295
    BIGINT,      //8	
    UNSIGNED_TINYINT,     //1	-128	    0         127            255
    UNSIGNED_SMALLINT,    //2	-32768	    0         32767          65535
    UNSIGNED_MEDIUMINT,   //3	-8388608	0         8388607        16777215
    UNSIGNED_INT,         //4	-2147483648	0         2147483647     4294967295
    UNSIGNED_BIGINT,      //8	


    VARIABLE,
    SUB_QUERY,
    MATCH_EXPRESSION,
    CASE_EXPRESSION,
    INTERVAL_EXPRESSION,
    EXPRESSION,          
    BOOLEAN_PRIMARY,     
    PREDICATE,           
    COMPARISON_OPERATOR, 
    BIT_EXPRESSION,      
    SIMPLE_EXPRESSION,   
    IDENTIFIER,          // a back ticked string
    DELIMITER,           // ,./&$
    OPERATOR,            // + - < > * / 
    FUNCTION,            // ex. count,sum,avg
    RESERVED,            // ex. from
    KEYWORD              // ex. select

    }BYTECODE_TYPE;


void print_tokens(token_t *token);
token_t * bytecode(char *query_str);
//expression stuff
token_t * dot(token_t *tokens);
token_t * alpha_E(token_t *tokens);
token_t * sign(token_t *tokens);
token_t * unsigned_integer(token_t *tokens);
token_t * signed_integer(token_t *tokens);
token_t * integer(token_t *tokens);
token_t * number(token_t *tokens);





/*******
COMPARITOR
=
<=
>=
<=>
<>
!=
********/