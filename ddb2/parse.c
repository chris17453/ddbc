#include    <stdio.h>
#include    <stdint.h>
#include    <stdlib.h>
#include    <string.h>

#include    "headers/stack.h"
#include    "headers/parse.h"
#include    "headers/expressions.h"

const int16_t MATCH_FAIL =-1;

void parse(char *text){
    uint16_t  res=core_parse(text,EXP_QUERIES,0,0,0,0);
}

const char * get_type(uint16_t t){
    switch(t){
        case TYP_CHR: return "CHAR";
        case TYP_GRP: return "GROUP";
        case TYP_NEG: return "NEGATE";
        case TYP_NOT: return "NOT";
        case TYP_OOM: return "ONE_OR_MORE";
        case TYP_OPT: return "OPTIONAL";
        case TYP_OR:  return "OR";
        case TYP_RNG: return "RANGE";
        case TYP_STR: return "STR";
        case TYP_ZOM: return "ZERO_OR_MORE";
        case TYP_EXP: return "EXPRESSION";
        default: return debug_str[t];
    }
}

uint16_t *get_next_level(uint16_t pattern_id,uint16_t index,uint16_t count){
    uint16_t *expressions=malloc(count * sizeof(uint16_t));
    uint16_t *fragment=pattern[pattern_id];
    uint16_t next_expr_len=0;

    //this is the curent index in the fragment to a top level element
    uint16_t expr_index=0;
    uint16_t level=0;
    while (expr_index<count){
        if(level==0){
            expressions[expr_index]=index;
            ++expr_index;
        } 

        if(fragment[index]>=0xFF00) {
            ++index;
            level+=fragment[index];
        }
        ++index;
        if (level>0) --level;
    }

    if (fragment[1]==TYP_CHR || fragment[1]==TYP_STR) {
        printf("\nTop Level Expressions index: for  %d, Count: %d\n",pattern_id,count);
        for(uint16_t i=0;i<count;i++){
            printf("%04x #%c\n",fragment[expressions[i]],fragment[expressions[i]]);
        }
    } else {
        printf("\nTop Level Expressions index: for  %d, Count: %d\n",pattern_id,count);
        for(uint16_t i=0;i<count;i++){
            if (fragment[expressions[i]]>=0xFF00) {
                printf("%04x %04x # %s/CHIDREN\n",fragment[expressions[i]],fragment[expressions[i]+1],get_type(fragment[expressions[i]]));
            } else {        
            printf("%04x #%s # %04x \n",fragment[expressions[i]],debug_str[fragment[expressions[i]]],expressions[i]);
            }
        }
    }
    printf("\n");
    return expressions;
}

void debug_pattern(uint16_t pattern_id){
    uint16_t *fragment=pattern[pattern_id];
    uint16_t length=fragment[0];
    stack_t *s=createStack(length);
    printf("\nPattern %04x, Length: %04x\n",pattern_id,length);
    
    int padd=0;
    int row_count=0;
    int last_fragment=0;
    for(int i=1;i<=length;i++){
        if (fragment[i]>=0xFF00) {
            last_fragment=fragment[i];
            for(int p=0;p<padd;p++) printf(" ");
            ++padd;
            printf("%04x %04x # %s/CHIDREN\n",fragment[i],fragment[i+1],get_type(fragment[i]));
            ++i;
            push(s,row_count-1);
            row_count=fragment[i];
            continue;
        }
        
        for(int p=0;p<padd;p++) printf(" "); 
        if (last_fragment==TYP_CHR ||  last_fragment==TYP_STR ) {
            printf("%04x #%c - %04x \n",fragment[i],fragment[i],fragment[i]);

        } else {
            printf("%04x #%s - %04x \n",fragment[i],debug_str[fragment[i]],fragment[i]);
        }

        if(row_count>0) {
            --row_count;
            while(row_count==0) {
                row_count=pop(s);
                if(padd>0)--padd;
            }
        }

    }
    free_stack(s);
    printf("\n");
}

char * padd(uint16_t length){
    char *pad_str=malloc(length+1);
    memset(pad_str,32,length);
    
    pad_str[length]=0;
    return pad_str;
}

int16_t core_parse(char *text,uint16_t pattern_id,uint16_t  pattern_pos,uint16_t  pos,uint16_t depth, uint16_t recursion_depth){
    // this holds the action\type
    uint16_t *fragment=pattern[pattern_id];
    uint16_t expr_type=0;
    uint16_t expr_len =0;
    uint16_t data_char;
    uint16_t expr_char;
    //for(uint16_t id=0;id<3;id++) debug_pattern(id);
    //debug_pattern(pattern_id);
    // the first index [0] of a pattern is its overall length
    // core functions and expressions are 16 bit int's
    //   Core functions are >= FF00
    //   everything below that is an expression
    // the limit for custom expressions + unique strings/characters is FF00-1

    uint16_t length=fragment[0];
    int16_t  res=0;
    uint16_t range1;
    uint16_t range2;
    //if this is the start of the pattern match
    if (pattern_pos==0)    ++pattern_pos;
    uint16_t pin,matched;
    uint16_t next_recursion_depth=recursion_depth;
//    printf("Length: %d",length);

    

    while (pattern_pos<=length){
        
        printf("%s Pattern: %04x  Index: %04x\n",padd(depth),pattern_id,pattern_pos);
        expr_type=fragment[pattern_pos];
        if(expr_type<0xFF00) {
            expr_len=1;
        } else {
            ++pattern_pos;
            expr_len =fragment[pattern_pos];
            ++pattern_pos;
        }
        
        //at this point, the pattern_pos index will be at the next  component

        uint16_t *sub_expr=get_next_level(pattern_id,pattern_pos,expr_len);

        //skip anything recursive from the left
        if (recursion_depth==0 && expr_type==pattern_id) {
            printf("skipping\n");
            pattern_pos+=expr_len;
            continue;
        }
        //for(int i=0;i<expr_len;i++) if(sub_expr[i]==pattern_id) 

        //printf("\n%s,%d\n",get_type(expr_type),pattern_pos);
        char c = getchar( );
        //printf("%c",c);


        switch(expr_type){
            case TYP_CHR:        
            case TYP_STR:   matched=0;
                            //printf("%s",text);
                            while (matched<expr_len){
                                expr_char=(char)fragment[pattern_pos+matched];
                                data_char=(char)text[pos+matched];
                                printf("%s EXP: %c - TEXT: %c %d\n",padd(depth), expr_char,data_char,pos+matched,depth+1);
                                if (expr_char != data_char ) break;
                                ++matched;
                            }
                            if (matched==expr_len) pos+=expr_len;
                            else {
                                printf("%s str/chr failed\n",padd(depth));
                                return MATCH_FAIL;
                            }
                            break;

            case TYP_RNG:   range1=fragment[pattern_pos+1]; 
                            range2=fragment[pattern_pos+2];
                            data_char=(char)text[pos+1];
                            if (data_char<range1 || data_char>range2) return MATCH_FAIL;
                            pos++;
                            break;


            case TYP_GRP:   for(int i=0;i<expr_len;i++){
                                printf("%s TRYING %d\n",padd(depth), sub_expr[i]);
                                if(fragment[sub_expr[i]]==pattern_id) {
                                    next_recursion_depth=recursion_depth+1;
                                } else { 
                                    next_recursion_depth=recursion_depth; 
                                }
                                res=core_parse(text,pattern_id,sub_expr[i],pos,depth+1,next_recursion_depth);
                           
                                if (res==MATCH_FAIL) return MATCH_FAIL;
                                pos=res;
                            }
                            break;


            case TYP_OPT:
                            res=core_parse(text,pattern_id,pattern_pos,pos,depth+1,next_recursion_depth);
                            if (res!=MATCH_FAIL) pos=res;
                            break;

            case TYP_OR :   matched=0;
                            for(int i=0;i<expr_len;i++){
                                if(fragment[sub_expr[i]]==pattern_id) {
                                    next_recursion_depth=recursion_depth+1;
                                } else { 
                                    next_recursion_depth=recursion_depth; 
                                }
                                res=core_parse(text,pattern_id,sub_expr[i],pos,depth+1,next_recursion_depth);
                                if (res!=MATCH_FAIL) {
                                    pos=res;
                                    ++matched;
                                    break;
                                }
                            } //end for
                            if (matched==0) {
                                return MATCH_FAIL;
                            }
                            break;

      
            case TYP_NOT:   res=core_parse(text,pattern_id,pattern_pos,pos,depth+1,recursion_depth);
                            if (res==MATCH_FAIL) pos+=1;
                            else return MATCH_FAIL;
                            break;
                            
            case TYP_OOM:   matched=0;
                            pin=0;
                            res=1;
                            while(res!=MATCH_FAIL){
                                pin=pos;
                                for(int i=0;i<expr_len;i++){
                                    if(fragment[sub_expr[i]]==pattern_id) {
                                        next_recursion_depth=recursion_depth+1;
                                    } else { 
                                        next_recursion_depth=recursion_depth; 
                                    }
                                    res=core_parse(text,pattern_id,sub_expr[i],pos,depth+1,next_recursion_depth);
                                    if (res!=MATCH_FAIL) {
                                        pos=res;
                                    }  else {
                                        break;
                                    }
                                } //end for
                                if (res==MATCH_FAIL) {
                                    pos=pin;
                                    break;
                                } else { 
                                    ++matched; 
                                }
                            } //end while
                            if (matched==0) return MATCH_FAIL;
                            break;
            
                            
            case TYP_ZOM:   pin=0;
                            res=1;
                            while(res!=MATCH_FAIL){
                                pin=pos;
                                for(int i=0;i<expr_len;i++){
                                    if(fragment[sub_expr[i]]==pattern_id) {
                                        next_recursion_depth=recursion_depth+1;
                                    } else { 
                                        next_recursion_depth=recursion_depth; 
                                    }
                                                
                                    res=core_parse(text,pattern_id,sub_expr[i],pos,depth+1,next_recursion_depth);
                                    if (res!=MATCH_FAIL) {
                                        pos=res;
                                    }  else {
                                        printf("%s Match internal failed\n",padd(depth));
                                        break;
                                    }
                                } //end for
                                printf("%s End of ZOM\n",padd(depth));
                                if (res==MATCH_FAIL) {
                                    pos=pin;
                                    printf("%s Match failed\n",padd(depth));
                                    break;
                                } 
                            } //end while
                            printf("%s Exit ZOM\n",padd(depth));
                            break;
            
            

                            
                            
            //if its not a core funciton or grouping, it's an expression / user function
            default:    printf ("%s Default\n",padd(depth) );

                        if(fragment[pattern_pos]==pattern_id) {
                            next_recursion_depth=recursion_depth+1;
                        } else { 
                            next_recursion_depth=recursion_depth; 
                        }
                        res=core_parse(text,pattern_id,fragment[pattern_pos],pos,depth+1,next_recursion_depth);
                        if (res!=MATCH_FAIL) {
                            pos=res;
                            printf("%s Default good\n",padd(depth));
                        } else {
                            printf("%s Default fail\n",padd(depth));
                            return MATCH_FAIL;
                        }

        }//end switch
        printf("%s Success -> %04X\n",padd(depth), pattern_id);
        pattern_pos+=expr_len;
    }//end loop
    //pos=0;
    return pos;
}
/*
uint16_t PATTERN_0x005[0x02E] = { 0x02D, 
TYP_OR, 0x005, 
    TYP_GRP, 0x005, 
        EXP_EXPR, 
        EXP_WHITESPACE, 
        TYP_OR, 0x005, 
            STR_OR, 
            TYP_GRP, 0x002, 
                STR_LOGICAL_OR, 
                STR_LOGICAL_OR, 
            STR_XOR, 
            STR_AND, 
            STR_SHORT_CIRCUIT_AND, 
        EXP_WHITESPACE, 
        EXP_EXPR, 
    TYP_GRP, 0x003, 
        STR_NOT, 
        EXP_WHITESPACE, 
        EXP_EXPR, 
    TYP_GRP, 0x003, 
        STR_NEGATE, 
        EXP_WHITESPACE, 
        EXP_EXPR, 
    TYP_GRP, 0x006, 
        EXP_BOOLEAN_PRIMARY, 
        EXP_WHITESPACE, 
        STR_IS, 
        TYP_OPT, 0x001, 
            TYP_GRP, 0x002, 
                EXP_WHITESPACE, 
                STR_NOT, 
        EXP_WHITESPACE, 
        TYP_OR, 0x002, 
            EXP_BOOLEAN, 
            EXP_UNKNOWN, 
    EXP_BOOLEAN_PRIMARY

};      //{EXPR}


expr: 
      ( {expr} {whitespace}  ( or | ([\|] [\|]) | xor | and | && )  {whitespace}  {expr})
  |   not {whitespace} {expr}
  |   !   {whitespace} {expr}
  |  {boolean_primary} {whitespace} IS ({whitespace} not)? {whitespace} ( {boolean} | {unknown})
  |  {boolean_primary} 

*/