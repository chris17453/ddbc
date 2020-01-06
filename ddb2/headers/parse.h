#include    <stdint.h>
#define TYP_CHR  0xFF01   //CHAR
#define TYP_GRP  0xFF02   //GROUP
#define TYP_NEG  0xFF03   //NEGATE
#define TYP_NOT  0xFF04   //NOT
#define TYP_OOM  0xFF05   //ONE_OR_MORE
#define TYP_OPT  0xFF06   //OPTIONAL
#define TYP_OR   0xFF07   //OR
#define TYP_STR  0xFF08   //STR
#define TYP_RNG  0xFF09   //RANGE
#define TYP_ZOM  0xFF0A   //ZERO_OR_MORE
#define TYP_EXP  0xFF0B   //EXPRESSION



void parse(char * text);
int16_t core_parse(char *text,uint16_t pattern_id,uint16_t  pattern_pos,uint16_t  pos,uint16_t depth,uint16_t recursion_depth);
