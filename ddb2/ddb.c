#include <stdio.h>

//# include "headers/bytecode.h"
#include "headers/func.h"

int main(){
    char  *query_str=" \n\
    select COUNT(*) AS number,*,(SELECT first_name FROM test.mock LIMIT 1) as first_name\n\
    FROM test.mock as f1 \n\
    INNER JOIN test as j1 ON f1.firstname=j1 \n\
    LEFT OUTER JOIN test as j2 ON f1.firstname=j2 \n\
    RIGHT OUTER JOIN test as j3 ON f1.firstname=j3 \n\
    WHERE first_name='bob' \n\
    and id=-11 \n\
    and id=+11 \n\
    and id=+11.44E-11 \n\
    and id=+11.44E11 \n\
    and id=11.44E11 \n\
    and id=11E11 \n\
    and id=+11E1 \n\
    and id=11 \n\
    and id=111.1111111 \n\
    and id=111.111111111111111 \n\
    and last_name not 'sam' \n\
    and gender=F \n\
    and last_name in (SELECT last_name FROM test.mock LIMIT 10 WHERE last_name like '%sam%') as first_name\n\
    \n\
    \n\
    heQ-- this is a comment\n\
Zllo    -- this is another comment /* */ fe\n\
    -- this is also a comment 'quote'\n\
    -- this is also a comment \"double quote\"\n";
    /*
        ;\n\
    b=:('rewrew')\n\
    *\n\
        Block Comment #1\n\
    \n\
    `identifier`.`identifier`.IDENTIFIER\n\
    sqltable_name_$ \n\
    sqltable_name12348_$ \n\
    135sqltable_name12348_$ \n\
    1\n\
    12\n\
    123\n\
    1234\n\
    pickup_last_ending
    */

    printf("Starting\n");
    printf("Query: %s\n \n",query_str);
    match_function(query_str);
    //print_tokens(tokens);






}




/*
expr:
    expr OR expr
  | expr || expr
  | expr XOR expr
  | expr AND expr
  | expr && expr
  | NOT expr
  | ! expr
  | boolean_primary IS [NOT] {TRUE | FALSE | UNKNOWN}
  | boolean_primary

boolean_primary:
    boolean_primary IS [NOT] NULL
  | boolean_primary <=> predicate
  | boolean_primary comparison_operator predicate
  | boolean_primary comparison_operator {ALL | ANY} (subquery)
  | predicate

comparison_operator: = | >= | > | <= | < | <> | !=

predicate:
    bit_expr [NOT] IN (subquery)
  | bit_expr [NOT] IN (expr [, expr] ...)
  | bit_expr [NOT] BETWEEN bit_expr AND predicate
  | bit_expr SOUNDS LIKE bit_expr
  | bit_expr [NOT] LIKE simple_expr [ESCAPE simple_expr]
  | bit_expr [NOT] REGEXP bit_expr
  | bit_expr

bit_expr:
    bit_expr | bit_expr
  | bit_expr & bit_expr
  | bit_expr << bit_expr
  | bit_expr >> bit_expr
  | bit_expr + bit_expr
  | bit_expr - bit_expr
  | bit_expr * bit_expr
  | bit_expr / bit_expr
  | bit_expr DIV bit_expr
  | bit_expr MOD bit_expr
  | bit_expr % bit_expr
  | bit_expr ^ bit_expr
  | bit_expr + interval_expr
  | bit_expr - interval_expr
  | simple_expr


simple_expr:
    literal
  | identifier
  | function_call
  | simple_expr COLLATE collation_name
  | param_marker
  | variable
  | simple_expr || simple_expr
  | + simple_expr
  | - simple_expr
  | ~ simple_expr
  | ! simple_expr
  | BINARY simple_expr
  | (expr [, expr] ...)
  | ROW (expr, expr [, expr] ...)
  | (subquery)
  | EXISTS (subquery)
  | {identifier expr}
  | match_expr
  | case_expr
  | interval_expr
  */





/****
 * F5                for debug
 * CTRL + SHIFT + B  to build 
 * vscode requires launch.json andtask.json to be setup for this to work.
 * sofar the project is manually created as a command to gcc to build...
 ****/