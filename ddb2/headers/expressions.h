#include <stdint.h>
#define EXP_QUERIES                     0x0000
#define EXP_WHITESPACE                  0x0001
#define EXP_SELECT                      0x0002
#define EXP_SELECT_EXPR_LIST            0x0003
#define EXP_IDENTIFIER                  0x0004
#define EXP_EXPR                        0x0005
#define EXP_SELECT_EXPR                 0x0006
#define EXP_SUBQUERY                    0x0007
#define EXP_BOOLEAN_PRIMARY             0x0008
#define EXP_BOOLEAN                     0x0009
#define EXP_UNKNOWN                     0x000A
#define EXP_COMPARISON_OPERATOR         0x000B
#define EXP_PREDICATE                   0x000C
#define EXP_NULL                        0x000D
#define EXP_BIT_EXPR                    0x000E
#define EXP_SIMPLE_EXPR                 0x000F
#define EXP_OPERATIONS                  0x0010
#define EXP_INTERVAL_EXPR               0x0011
#define EXP_IDENTIFIER_EXPR             0x0012
#define EXP_LITERAL                     0x0013
#define EXP_HEX                         0x0014
#define EXP_BIT                         0x0015
#define EXP_STRING                      0x0016
#define EXP_REAL                        0x0017
#define EXP_YEARS                       0x0018
#define EXP_UNSIGNED_INT                0x0019
#define EXP_QUARTERS                    0x001A
#define EXP_MONTHS                      0x001B
#define EXP_WEEKS                       0x001C
#define EXP_DAYS                        0x001D
#define EXP_HOURS                       0x001E
#define EXP_MINUTES                     0x001F
#define EXP_SECONDS                     0x0020
#define EXP_MICROSECONDS                0x0021
#define EXP_MICROSECOND                 0x0022
#define EXP_SECOND                      0x0023
#define EXP_MINUTE                      0x0024
#define EXP_HOUR                        0x0025
#define EXP_DAY                         0x0026
#define EXP_WEEK                        0x0027
#define EXP_MONTH                       0x0028
#define EXP_QUARTER                     0x0029
#define EXP_YEAR                        0x002A
#define EXP_SECOND_MICROSECOND          0x002B
#define EXP_MINUTE_MICROSECOND          0x002C
#define EXP_MINUTE_SECOND               0x002D
#define EXP_HOUR_MICROSECOND            0x002E
#define EXP_HOUR_SECOND                 0x002F
#define EXP_HOUR_MINUTE                 0x0030
#define EXP_DAY_MICROSECOND             0x0031
#define EXP_DAY_SECOND                  0x0032
#define EXP_DAY_MINUTE                  0x0033
#define EXP_DAY_HOUR                    0x0034
#define EXP_YEAR_MONTH                  0x0035
#define EXP_TRUE                        0x0036
#define EXP_FALSE                       0x0037
#define EXP_INTEGER                     0x0038
#define EXP_SIGNED_INT                  0x0039
#define EXP_SIGN                        0x003A
#define EXP_EXPONENT                    0x003B
#define EXP_KEYWORDS                    0x003C
#define EXP_SINGLE_QUOTE_STRING         0x003D
#define EXP_DOUBLE_QUOTE_STRING         0x003E
#define EXP_QUERY_DELIMITER             0x003F
#define EXP_COMMENT                     0x0040
#define EXP_BLOCK_COMMENT               0x0041
#define EXP_SINGLE_COMMENT              0x0042
#define EXP_LEFT_COMMENT                0x0043
#define EXP_RIGHT_COMMENT               0x0044
#define EXP_INLINE_COMMENT              0x0045
#define EXP_END_OF_LINE                 0x0046
#define EXP_CATCH_ALL                   0x0047
#define STR_SELECT                      0x0048
#define STR_FROM                        0x0049
#define STR_PERIOD                      0x004A
#define STR_AS                          0x004B
#define STR_WHERE                       0x004C
#define STR_COMMA                       0x004D
#define STR_LEFT_PAREN                  0x004E
#define STR_RIGHT_PAREN                 0x004F
#define STR_OR                          0x0050
#define STR_LOGICAL_OR                  0x0051
#define STR_XOR                         0x0052
#define STR_AND                         0x0053
#define STR_SHORT_CIRCUIT_AND           0x0054
#define STR_NOT                         0x0055
#define STR_NEGATE                      0x0056
#define STR_IS                          0x0057
#define STR_NULL_EQUAL                  0x0058
#define STR_ALL                         0x0059
#define STR_ANY                         0x005A
#define STR_IN                          0x005B
#define STR_BETWEEN                     0x005C
#define STR_LIKE                        0x005D
#define STR_ESCAPE                      0x005E
#define STR_REGEXP                      0x005F
#define STR_PLUS                        0x0060
#define STR_MINUS                       0x0061
#define STR_LOGICAL_AND                 0x0062
#define STR_LT                          0x0063
#define STR_GT                          0x0064
#define STR_TIMES                       0x0065
#define STR_DIVIDE                      0x0066
#define STR_DIV                         0x0067
#define STR_MOD                         0x0068
#define STR_MODULUS                     0x0069
#define STR_TILDE                       0x006A
#define STR_MICROSECOND                 0x006B
#define STR_SECOND                      0x006C
#define STR_MINUTE                      0x006D
#define STR_HOUR                        0x006E
#define STR_DAY                         0x006F
#define STR_WEEK                        0x0070
#define STR_MONTH                       0x0071
#define STR_QUARTER                     0x0072
#define STR_YEAR                        0x0073
#define STR_SECOND_MICROSECOND          0x0074
#define STR_MINUTE_MICROSECOND          0x0075
#define STR_MINUTE_SECOND               0x0076
#define STR_HOUR_MICROSECOND            0x0077
#define STR_HOUR_SECOND                 0x0078
#define STR_HOUR_MINUTE                 0x0079
#define STR_DAY_MICROSECOND             0x007A
#define STR_DAY_SECOND                  0x007B
#define STR_DAY_MINUTE                  0x007C
#define STR_DAY_HOUR                    0x007D
#define STR_YEAR_MONTH                  0x007E
#define STR_SINGLE_QUOTE                0x007F
#define STR_COLON                       0x0080
#define STR_SPACE                       0x0081
#define STR_UNKNOWN                     0x0082
#define STR_0                           0x0083
#define STR_X                           0x0084
#define STR_9                           0x0085
#define STR_A                           0x0086
#define STR_F                           0x0087
#define STR_B                           0x0088
#define STR_1                           0x0089
#define STR_NULL                        0x008A
#define STR_TRUE                        0x008B
#define STR_FALSE                       0x008C
#define STR_E                           0x008D
#define STR_Z                           0x008E
#define STR_DOLLAR_SIGN                 0x008F
#define STR_UNDERSCORE                  0x0090
#define STR_ON                          0x0091
#define STR_LIMIT                       0x0092
#define STR_HAVING                      0x0093
#define STR_GROUP                       0x0094
#define STR_BY                          0x0095
#define STR_ORDER                       0x0096
#define STR_DOUBLE_QUOTE                0x0097
#define STR_SEMICOLON                   0x0098
#define STR_EQUALS                      0x0099
#define STR_NEW_LINE                    0x009A
#define STR_LINE_RETURN                 0x009B
#define STR_TAB                         0x009C

const char *debug_str[157];



uint16_t *pattern[157];