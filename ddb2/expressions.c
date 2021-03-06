/********************************************
* Generated: 2020-03-03                    *
********************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "headers/expressions.h"
#include "headers/parse.h"
//#define DEBUG_START   1
//#define DEBUG_SUCCESS 1
//#define DEBUG_FAIL    1

uint16_t PATTERN_0x000[0x006] = { 0x005, TYP_GRP, 0x003, EXP_IDENTIFIER, STR_AS, EXP_IDENTIFIER };      //{IDENTIFIER_EXPR}
uint16_t PATTERN_0x001[0x005] = { 0x004, TYP_GRP, 0x002, EXP_SIGN, EXP_UNSIGNED_INT };  //{SIGNED_INT}
uint16_t PATTERN_0x002[0x029] = { 0x028, TYP_OR, 0x002, EXP_PREDICATE, TYP_GRP, 0x003, EXP_BOOLEAN_PRIMARY, EXP_WHITESPACE, TYP_OR, 0x004, TYP_GRP, 0x003, EXP_COMPARISON_OPERATOR, EXP_WHITESPACE, EXP_PREDICATE, TYP_GRP, 0x004, STR_IS, TYP_OPT, 0x001, TYP_GRP, 0x002, EXP_WHITESPACE, STR_NOT, EXP_WHITESPACE, EXP_NULL, TYP_GRP, 0x003, STR_NULL_EQUAL, EXP_WHITESPACE, EXP_PREDICATE, TYP_GRP, 0x005, EXP_COMPARISON_OPERATOR, EXP_WHITESPACE, TYP_OR, 0x002, STR_ALL, STR_ANY, EXP_WHITESPACE, EXP_SUBQUERY };  //{BOOLEAN_PRIMARY}
uint16_t PATTERN_0x003[0x003] = { 0x002, STR_DIVIDE, STR_TIMES };       //{LEFT_COMMENT}
uint16_t PATTERN_0x004[0x005] = { 0x004, TYP_GRP, 0x002, EXP_WHITESPACE, EXP_SELECT };  //{QUERIES}
uint16_t PATTERN_0x005[0x009] = { 0x008, TYP_GRP, 0x003, STR_SINGLE_QUOTE, TYP_OOM, 0x001, STR_NOT, STR_SINGLE_QUOTE, STR_SINGLE_QUOTE };       //{SINGLE_QUOTE_STRING}
uint16_t PATTERN_0x006[0x016] = { 0x015, TYP_OR, 0x007, STR_EQUALS, TYP_GRP, 0x002, STR_LT, STR_GT, TYP_GRP, 0x002, STR_GT, STR_EQUALS, TYP_GRP, 0x002, STR_LT, STR_EQUALS, TYP_GRP, 0x002, STR_NEGATE, STR_EQUALS, STR_GT, STR_LT };   //{COMPARISON_OPERATOR}
uint16_t PATTERN_0x007[0x013] = { 0x012, TYP_OR, 0x010, STR_SELECT, STR_FROM, STR_ON, STR_WHERE, STR_AND, STR_OR, STR_XOR, STR_LIMIT, STR_HAVING, STR_GROUP, STR_BY, STR_ORDER, STR_NOT, STR_IN, STR_BETWEEN, STR_LIKE };       //{KEYWORDS}
uint16_t PATTERN_0x008[0x003] = { 0x002, STR_MINUS, STR_PLUS }; //{SIGN}
uint16_t PATTERN_0x009[0x012] = { 0x011, STR_0, STR_X, STR_X, TYP_OOM, 0x003, TYP_RNG, 0x002, STR_0, STR_9, TYP_RNG, 0x002, STR_A, STR_F, TYP_RNG, 0x002, STR_A, STR_F };       //{HEX}
uint16_t PATTERN_0x00A[0x004] = { 0x003, TYP_ZOM, 0x001, STR_SPACE };   //{WHITESPACE}
uint16_t PATTERN_0x00B[0x00A] = { 0x009, EXP_SELECT_EXPR, TYP_ZOM, 0x001, TYP_GRP, 0x004, EXP_WHITESPACE, STR_COMMA, EXP_WHITESPACE, EXP_SELECT_EXPR }; //{SELECT_EXPR_LIST}
uint16_t PATTERN_0x00C[0x005] = { 0x004, TYP_OR, 0x002, EXP_BLOCK_COMMENT, EXP_SINGLE_COMMENT };        //{COMMENT}
uint16_t PATTERN_0x00D[0x046] = { 0x045, EXP_BIT_EXPR, TYP_OPT, 0x001, TYP_OR, 0x004, TYP_GRP, 0x006, EXP_WHITESPACE, TYP_OPT, 0x001, STR_NOT, EXP_WHITESPACE, STR_IN, EXP_WHITESPACE, EXP_SUBQUERY, TYP_GRP, 0x009, EXP_WHITESPACE, TYP_OPT, 0x001, STR_NOT, EXP_WHITESPACE, STR_IN, EXP_WHITESPACE, STR_LEFT_PAREN, EXP_EXPR, TYP_OPT, 0x001, TYP_ZOM, 0x001, TYP_GRP, 0x004, EXP_WHITESPACE, STR_COMMA, EXP_WHITESPACE, EXP_EXPR, STR_RIGHT_PAREN, TYP_GRP, 0x00A, EXP_WHITESPACE, TYP_OPT, 0x001, STR_NOT, EXP_WHITESPACE, STR_BETWEEN, EXP_WHITESPACE, EXP_BIT_EXPR, EXP_WHITESPACE, STR_AND, EXP_WHITESPACE, EXP_PREDICATE, TYP_GRP, 0x007, EXP_WHITESPACE, TYP_OPT, 0x001, STR_NOT, EXP_WHITESPACE, STR_LIKE, EXP_WHITESPACE, EXP_SIMPLE_EXPR, TYP_OPT, 0x001, TYP_GRP, 0x004, EXP_WHITESPACE, STR_ESCAPE, EXP_WHITESPACE, EXP_SIMPLE_EXPR };    //{PREDICATE}
uint16_t PATTERN_0x00E[0x002] = { 0x001, STR_UNKNOWN }; //{UNKNOWN}
uint16_t PATTERN_0x00F[0x026] = { 0x025, STR_SELECT, EXP_WHITESPACE, EXP_SELECT_EXPR_LIST, EXP_WHITESPACE, TYP_OPT, 0x001, TYP_GRP, 0x005, STR_FROM, EXP_WHITESPACE, EXP_IDENTIFIER, TYP_OPT, 0x001, TYP_GRP, 0x002, STR_PERIOD, EXP_IDENTIFIER, TYP_OPT, 0x001, TYP_GRP, 0x004, EXP_WHITESPACE, STR_AS, EXP_WHITESPACE, EXP_IDENTIFIER, EXP_WHITESPACE, TYP_OPT, 0x001, TYP_GRP, 0x002, STR_WHERE, TYP_OOM, 0x001, TYP_GRP, 0x002, EXP_WHITESPACE, EXP_EXPR }; //{SELECT}
uint16_t PATTERN_0x010[0x002] = { 0x001, EXP_BOOLEAN_PRIMARY }; //{EXPR}
uint16_t PATTERN_0x011[0x006] = { 0x005, TYP_GRP, 0x002, STR_E, STR_E, EXP_INTEGER };   //{EXPONENT}
uint16_t PATTERN_0x012[0x005] = { 0x004, TYP_OR, 0x002, STR_FALSE, STR_FALSE }; //{FALSE}
uint16_t PATTERN_0x013[0x007] = { 0x006, TYP_OOM, 0x001, TYP_RNG, 0x002, STR_0, STR_9 };        //{UNSIGNED_INT}
uint16_t PATTERN_0x014[0x007] = { 0x006, TYP_NOT, 0x001, STR_TAB, STR_SPACE, STR_NEW_LINE, STR_R };     //{CATCH_ALL}
uint16_t PATTERN_0x015[0x007] = { 0x006, STR_0, STR_B, TYP_OOM, 0x001, STR_0, STR_1 };  //{BIT}
uint16_t PATTERN_0x016[0x00C] = { 0x00B, TYP_GRP, 0x003, EXP_EXPR, EXP_WHITESPACE, TYP_OPT, 0x001, TYP_GRP, 0x003, STR_AS, EXP_WHITESPACE, EXP_IDENTIFIER };    //{SELECT_EXPR}
uint16_t PATTERN_0x017[0x005] = { 0x004, TYP_OR, 0x002, EXP_SINGLE_QUOTE_STRING, EXP_DOUBLE_QUOTE_STRING };     //{STRING}
uint16_t PATTERN_0x018[0x003] = { 0x002, STR_TIMES, STR_DIVIDE };       //{RIGHT_COMMENT}
uint16_t PATTERN_0x019[0x005] = { 0x004, TYP_OR, 0x002, EXP_SIGNED_INT, EXP_UNSIGNED_INT };     //{INTEGER}
uint16_t PATTERN_0x01A[0x005] = { 0x004, TYP_OR, 0x002, EXP_TRUE, EXP_FALSE };  //{BOOLEAN}
uint16_t PATTERN_0x01B[0x009] = { 0x008, TYP_GRP, 0x003, STR_DOUBLE_QUOTE, TYP_OOM, 0x001, STR_NOT, STR_DOUBLE_QUOTE, STR_DOUBLE_QUOTE };       //{DOUBLE_QUOTE_STRING}
uint16_t PATTERN_0x01C[0x015] = { 0x014, TYP_OR, 0x00C, STR_LOGICAL_OR, STR_LOGICAL_AND, TYP_GRP, 0x002, STR_LT, STR_LT, TYP_GRP, 0x002, STR_GT, STR_GT, STR_PLUS, STR_MINUS, STR_TIMES, STR_DIVIDE, STR_DIV, STR_MOD, STR_MODULUS, STR_NOT };  //{OPERATIONS}
uint16_t PATTERN_0x01D[0x006] = { 0x005, TYP_OR, 0x003, EXP_LITERAL, EXP_IDENTIFIER, EXP_IDENTIFIER_EXPR };     //{SIMPLE_EXPR}
uint16_t PATTERN_0x01E[0x003] = { 0x002, STR_MINUS, STR_MINUS };        //{INLINE_COMMENT}
uint16_t PATTERN_0x01F[0x008] = { 0x007, TYP_GRP, 0x005, STR_LEFT_PAREN, EXP_WHITESPACE, EXP_SELECT, EXP_WHITESPACE, STR_RIGHT_PAREN }; //{SUBQUERY}
uint16_t PATTERN_0x020[0x012] = { 0x011, TYP_OR, 0x003, TYP_GRP, 0x003, EXP_INTEGER, STR_PERIOD, EXP_UNSIGNED_INT, TYP_GRP, 0x002, STR_PERIOD, EXP_UNSIGNED_INT, TYP_GRP, 0x002, EXP_INTEGER, TYP_OPT, 0x001, EXP_EXPONENT };   //{REAL}
uint16_t PATTERN_0x021[0x00D] = { 0x00C, TYP_GRP, 0x003, EXP_INLINE_COMMENT, TYP_ZOM, 0x001, TYP_GRP, 0x002, TYP_NOT, 0x001, EXP_END_OF_LINE, STR_PERIOD, EXP_END_OF_LINE };    //{SINGLE_COMMENT}
uint16_t PATTERN_0x022[0x014] = { 0x013, TYP_NOT, 0x001, EXP_KEYWORDS, TYP_OOM, 0x004, TYP_RNG, 0x002, STR_A, STR_Z, TYP_RNG, 0x002, STR_A, STR_Z, TYP_RNG, 0x002, STR_0, STR_9, STR_DOLLAR_SIGN, STR_UNDERSCORE };     //{IDENTIFIER}
uint16_t PATTERN_0x023[0x002] = { 0x001, STR_SEMICOLON };       //{QUERY_DELIMITER}
uint16_t PATTERN_0x024[0x005] = { 0x004, STR_NEW_LINE, TYP_OPT, 0x001, STR_R }; //{END_OF_LINE}
uint16_t PATTERN_0x025[0x005] = { 0x004, TYP_OR, 0x002, STR_NULL, STR_NULL };   //{NULL}
uint16_t PATTERN_0x026[0x005] = { 0x004, TYP_OR, 0x002, STR_TRUE, STR_TRUE };   //{TRUE}
uint16_t PATTERN_0x027[0x009] = { 0x008, TYP_OR, 0x006, EXP_HEX, EXP_BIT, EXP_BOOLEAN, EXP_NULL, EXP_STRING, EXP_REAL };        //{LITERAL}
uint16_t PATTERN_0x028[0x002] = { 0x001, EXP_SIMPLE_EXPR };     //{BIT_EXPR}
uint16_t PATTERN_0x029[0x00D] = { 0x00C, TYP_GRP, 0x003, EXP_LEFT_COMMENT, TYP_ZOM, 0x001, TYP_GRP, 0x002, TYP_NOT, 0x001, EXP_RIGHT_COMMENT, STR_PERIOD, EXP_RIGHT_COMMENT };  //{BLOCK_COMMENT}
uint16_t PATTERN_0x02A[0x004] = { 0x003, TYP_CHR, 0x001, 0x24 };        //DOLLAR_SIGN
uint16_t PATTERN_0x02B[0x008] = { 0x007, TYP_STR, 0x005, 0x4C, 0x49, 0x4D, 0x49, 0x54 };        //LIMIT
uint16_t PATTERN_0x02C[0x004] = { 0x003, TYP_CHR, 0x001, 0x29 };        //RIGHT_PAREN
uint16_t PATTERN_0x02D[0x007] = { 0x006, TYP_STR, 0x004, 0x54, 0x52, 0x55, 0x45 };      //TRUE
uint16_t PATTERN_0x02E[0x005] = { 0x004, TYP_STR, 0x002, 0x42, 0x59 };  //BY
uint16_t PATTERN_0x02F[0x004] = { 0x003, TYP_CHR, 0x001, 0x30 };        //0
uint16_t PATTERN_0x030[0x004] = { 0x003, TYP_CHR, 0x001, 0x2B };        //PLUS
uint16_t PATTERN_0x031[0x004] = { 0x003, TYP_CHR, 0x001, 0x3E };        //GT
uint16_t PATTERN_0x032[0x004] = { 0x003, TYP_CHR, 0x001, 0x2E };        //PERIOD
uint16_t PATTERN_0x033[0x009] = { 0x008, TYP_STR, 0x006, 0x45, 0x53, 0x43, 0x41, 0x50, 0x45 };  //ESCAPE
uint16_t PATTERN_0x034[0x004] = { 0x003, TYP_CHR, 0x001, 0x58 };        //X
uint16_t PATTERN_0x035[0x008] = { 0x007, TYP_STR, 0x005, 0x57, 0x48, 0x45, 0x52, 0x45 };        //WHERE
uint16_t PATTERN_0x036[0x005] = { 0x004, TYP_STR, 0x002, 0x4F, 0x4E };  //ON
uint16_t PATTERN_0x037[0x005] = { 0x004, TYP_STR, 0x002, 0x4F, 0x52 };  //OR
uint16_t PATTERN_0x038[0x008] = { 0x007, TYP_STR, 0x005, 0x47, 0x52, 0x4F, 0x55, 0x50 };        //GROUP
uint16_t PATTERN_0x039[0x004] = { 0x003, TYP_CHR, 0x001, 0x26 };        //LOGICAL_AND
uint16_t PATTERN_0x03A[0x009] = { 0x008, TYP_STR, 0x006, 0x53, 0x45, 0x4C, 0x45, 0x43, 0x54 };  //SELECT
uint16_t PATTERN_0x03B[0x004] = { 0x003, TYP_CHR, 0x001, 0x2D };        //MINUS
uint16_t PATTERN_0x03C[0x004] = { 0x003, TYP_CHR, 0x001, 0x2F };        //DIVIDE
uint16_t PATTERN_0x03D[0x004] = { 0x003, TYP_CHR, 0x001, 0x3D };        //EQUALS
uint16_t PATTERN_0x03E[0x004] = { 0x003, TYP_CHR, 0x001, 0x09 };        //TAB
uint16_t PATTERN_0x03F[0x006] = { 0x005, TYP_STR, 0x003, 0x41, 0x4E, 0x44 };    //AND
uint16_t PATTERN_0x040[0x005] = { 0x004, TYP_STR, 0x002, 0x41, 0x53 };  //AS
uint16_t PATTERN_0x041[0x004] = { 0x003, TYP_CHR, 0x001, 0x5E };        //NOT
uint16_t PATTERN_0x042[0x006] = { 0x005, TYP_STR, 0x003, 0x41, 0x4E, 0x59 };    //ANY
uint16_t PATTERN_0x043[0x006] = { 0x005, TYP_STR, 0x003, 0x4D, 0x4F, 0x44 };    //MOD
uint16_t PATTERN_0x044[0x004] = { 0x003, TYP_CHR, 0x001, 0x22 };        //DOUBLE_QUOTE
uint16_t PATTERN_0x045[0x00A] = { 0x009, TYP_STR, 0x007, 0x55, 0x4E, 0x4B, 0x4E, 0x4F, 0x57, 0x4E };    //UNKNOWN
uint16_t PATTERN_0x046[0x004] = { 0x003, TYP_CHR, 0x001, 0x21 };        //NEGATE
uint16_t PATTERN_0x047[0x008] = { 0x007, TYP_STR, 0x005, 0x4F, 0x52, 0x44, 0x45, 0x52 };        //ORDER
uint16_t PATTERN_0x048[0x004] = { 0x003, TYP_CHR, 0x001, 0x3B };        //SEMICOLON
uint16_t PATTERN_0x049[0x004] = { 0x003, TYP_CHR, 0x001, 0x28 };        //LEFT_PAREN
uint16_t PATTERN_0x04A[0x004] = { 0x003, TYP_CHR, 0x001, 0x0A };        //NEW_LINE
uint16_t PATTERN_0x04B[0x004] = { 0x003, TYP_CHR, 0x001, 0x42 };        //B
uint16_t PATTERN_0x04C[0x006] = { 0x005, TYP_STR, 0x003, 0x3C, 0x3D, 0x3E };    //NULL_EQUAL
uint16_t PATTERN_0x04D[0x004] = { 0x003, TYP_CHR, 0x001, 0x46 };        //F
uint16_t PATTERN_0x04E[0x006] = { 0x005, TYP_STR, 0x003, 0x41, 0x4C, 0x4C };    //ALL
uint16_t PATTERN_0x04F[0x004] = { 0x003, TYP_CHR, 0x001, 0x52 };        //R
uint16_t PATTERN_0x050[0x00A] = { 0x009, TYP_STR, 0x007, 0x42, 0x45, 0x54, 0x57, 0x45, 0x45, 0x4E };    //BETWEEN
uint16_t PATTERN_0x051[0x004] = { 0x003, TYP_CHR, 0x001, 0x5A };        //Z
uint16_t PATTERN_0x052[0x004] = { 0x003, TYP_CHR, 0x001, 0x25 };        //MODULUS
uint16_t PATTERN_0x053[0x008] = { 0x007, TYP_STR, 0x005, 0x46, 0x41, 0x4C, 0x53, 0x45 };        //FALSE
uint16_t PATTERN_0x054[0x007] = { 0x006, TYP_STR, 0x004, 0x4C, 0x49, 0x4B, 0x45 };      //LIKE
uint16_t PATTERN_0x055[0x004] = { 0x003, TYP_CHR, 0x001, 0x7C };        //LOGICAL_OR
uint16_t PATTERN_0x056[0x004] = { 0x003, TYP_CHR, 0x001, 0x5F };        //UNDERSCORE
uint16_t PATTERN_0x057[0x006] = { 0x005, TYP_STR, 0x003, 0x44, 0x49, 0x56 };    //DIV
uint16_t PATTERN_0x058[0x007] = { 0x006, TYP_STR, 0x004, 0x4E, 0x55, 0x4C, 0x4C };      //NULL
uint16_t PATTERN_0x059[0x004] = { 0x003, TYP_CHR, 0x001, 0x31 };        //1
uint16_t PATTERN_0x05A[0x004] = { 0x003, TYP_CHR, 0x001, 0x3C };        //LT
uint16_t PATTERN_0x05B[0x004] = { 0x003, TYP_CHR, 0x001, 0x2C };        //COMMA
uint16_t PATTERN_0x05C[0x004] = { 0x003, TYP_CHR, 0x001, 0x39 };        //9
uint16_t PATTERN_0x05D[0x004] = { 0x003, TYP_CHR, 0x001, 0x41 };        //A
uint16_t PATTERN_0x05E[0x004] = { 0x003, TYP_CHR, 0x001, 0x45 };        //E
uint16_t PATTERN_0x05F[0x004] = { 0x003, TYP_CHR, 0x001, 0x20 };        //SPACE
uint16_t PATTERN_0x060[0x005] = { 0x004, TYP_STR, 0x002, 0x49, 0x53 };  //IS
uint16_t PATTERN_0x061[0x006] = { 0x005, TYP_STR, 0x003, 0x58, 0x4F, 0x52 };    //XOR
uint16_t PATTERN_0x062[0x004] = { 0x003, TYP_CHR, 0x001, 0x2A };        //TIMES
uint16_t PATTERN_0x063[0x005] = { 0x004, TYP_STR, 0x002, 0x49, 0x4E };  //IN
uint16_t PATTERN_0x064[0x007] = { 0x006, TYP_STR, 0x004, 0x46, 0x52, 0x4F, 0x4D };      //FROM
uint16_t PATTERN_0x065[0x004] = { 0x003, TYP_CHR, 0x001, 0x27 };        //SINGLE_QUOTE
uint16_t PATTERN_0x066[0x009] = { 0x008, TYP_STR, 0x006, 0x48, 0x41, 0x56, 0x49, 0x4E, 0x47 };  //HAVING

// ********************

uint16_t *pattern[103] =
  { PATTERN_0x000, PATTERN_0x001, PATTERN_0x002, PATTERN_0x003, PATTERN_0x004, PATTERN_0x005, PATTERN_0x006, PATTERN_0x007, PATTERN_0x008,
PATTERN_0x009, PATTERN_0x00A, PATTERN_0x00B, PATTERN_0x00C, PATTERN_0x00D, PATTERN_0x00E, PATTERN_0x00F, PATTERN_0x010, PATTERN_0x011, PATTERN_0x012, PATTERN_0x013,
PATTERN_0x014, PATTERN_0x015, PATTERN_0x016, PATTERN_0x017, PATTERN_0x018, PATTERN_0x019, PATTERN_0x01A, PATTERN_0x01B, PATTERN_0x01C, PATTERN_0x01D, PATTERN_0x01E,
PATTERN_0x01F, PATTERN_0x020, PATTERN_0x021, PATTERN_0x022, PATTERN_0x023, PATTERN_0x024, PATTERN_0x025, PATTERN_0x026, PATTERN_0x027, PATTERN_0x028, PATTERN_0x029,
PATTERN_0x02A, PATTERN_0x02B, PATTERN_0x02C, PATTERN_0x02D, PATTERN_0x02E, PATTERN_0x02F, PATTERN_0x030, PATTERN_0x031, PATTERN_0x032, PATTERN_0x033, PATTERN_0x034,
PATTERN_0x035, PATTERN_0x036, PATTERN_0x037, PATTERN_0x038, PATTERN_0x039, PATTERN_0x03A, PATTERN_0x03B, PATTERN_0x03C, PATTERN_0x03D, PATTERN_0x03E, PATTERN_0x03F,
PATTERN_0x040, PATTERN_0x041, PATTERN_0x042, PATTERN_0x043, PATTERN_0x044, PATTERN_0x045, PATTERN_0x046, PATTERN_0x047, PATTERN_0x048, PATTERN_0x049, PATTERN_0x04A,
PATTERN_0x04B, PATTERN_0x04C, PATTERN_0x04D, PATTERN_0x04E, PATTERN_0x04F, PATTERN_0x050, PATTERN_0x051, PATTERN_0x052, PATTERN_0x053, PATTERN_0x054, PATTERN_0x055,
PATTERN_0x056, PATTERN_0x057, PATTERN_0x058, PATTERN_0x059, PATTERN_0x05A, PATTERN_0x05B, PATTERN_0x05C, PATTERN_0x05D, PATTERN_0x05E, PATTERN_0x05F, PATTERN_0x060,
PATTERN_0x061, PATTERN_0x062, PATTERN_0x063, PATTERN_0x064, PATTERN_0x065, PATTERN_0x066 };
const char *debug_str[103] =
  { "IDENTIFIER_EXPR", "SIGNED_INT", "BOOLEAN_PRIMARY", "LEFT_COMMENT", "QUERIES", "SINGLE_QUOTE_STRING", "COMPARISON_OPERATOR", "KEYWORDS", "SIGN",
"HEX", "WHITESPACE", "SELECT_EXPR_LIST", "COMMENT", "PREDICATE", "UNKNOWN", "SELECT", "EXPR", "EXPONENT", "FALSE", "UNSIGNED_INT", "CATCH_ALL", "BIT", "SELECT_EXPR",
"STRING", "RIGHT_COMMENT", "INTEGER", "BOOLEAN", "DOUBLE_QUOTE_STRING", "OPERATIONS", "SIMPLE_EXPR", "INLINE_COMMENT", "SUBQUERY", "REAL", "SINGLE_COMMENT", "IDENTIFIER",
"QUERY_DELIMITER", "END_OF_LINE", "NULL", "TRUE", "LITERAL", "BIT_EXPR", "BLOCK_COMMENT", "DOLLAR_SIGN", "LIMIT", "RIGHT_PAREN", "TRUE", "BY", "0", "PLUS", "GT", "PERIOD",
"ESCAPE", "X", "WHERE", "ON", "OR", "GROUP", "LOGICAL_AND", "SELECT", "MINUS", "DIVIDE", "EQUALS", "TAB", "AND", "AS", "NOT", "ANY", "MOD", "DOUBLE_QUOTE", "UNKNOWN",
"NEGATE", "ORDER", "SEMICOLON", "LEFT_PAREN", "NEW_LINE", "B", "NULL_EQUAL", "F", "ALL", "R", "BETWEEN", "Z", "MODULUS", "FALSE", "LIKE", "LOGICAL_OR", "UNDERSCORE", "DIV",
"NULL", "1", "LT", "COMMA", "9", "A", "E", "SPACE", "IS", "XOR", "TIMES", "IN", "FROM", "SINGLE_QUOTE", "HAVING" };
