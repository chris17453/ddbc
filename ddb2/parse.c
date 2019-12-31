#include    <stdio.h>
#include    <stdint.h>
#include    <stdlib.h>

#include    "headers/stack.h"
#include    "headers/parse.h"
#include    "headers/expressions.h"



void parse(char *text){
    uint16_t  res=core_parse(text,EXP_QUERIES,0,0);
}

char * get_type(uint16_t t){
    switch(t){
        case TYP_CHR: return "CHAR";
        case TYP_GRP: return "GROUP";
        case TYP_NEG: return "NEGATE";
        case TYP_NOT: return "NOT";
        case TYP_OOM: return "ONE_OR_MORE";
        case TYP_OPT: return "OPTIONAL";
        case TYP_OR: return "OR";
        case TYP_RNG: return "RANGE";
        case TYP_STR: return "STR";
        case TYP_ZOM: return "ZERO_OR_MORE";
        case TYP_EXP: return "EXPRESSION";
        default: return "UNK";
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

    printf("\nTop Level Expressions index: for  %d, Count: %d\n",pattern_id,count);
    for(uint16_t i=0;i<count;i++){
        if (fragment[expressions[i]]>=0xFF00) {
            printf("%04x %04x # %s/CHIDREN\n",fragment[expressions[i]],fragment[expressions[i]+1],get_type(fragment[expressions[i]]));
        } else {        
        printf("%04x #%s \n",fragment[expressions[i]],debug_str[fragment[expressions[i]]]);
        }

        //printf("\n %d",expressions[i]);
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
    
    for(int i=1;i<=length;i++){
        if (fragment[i]>=0xFF00) {
            for(int p=0;p<padd;p++) printf(" ");
            ++padd;
            printf("%04x %04x # %s/CHIDREN\n",fragment[i],fragment[i+1],get_type(fragment[i]));
            ++i;
            push(s,row_count-1);
            row_count=fragment[i];
            continue;
        }
        
        for(int p=0;p<padd;p++) printf(" "); 
        printf("%04x #%s \n",fragment[i],debug_str[fragment[i]]);

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

uint16_t core_parse(char *text,uint16_t pattern_id,uint16_t  pattern_pos,uint16_t  pos){
    // this holds the action\type
    uint16_t *fragment=pattern[pattern_id];
    uint16_t expr_type=0;
    uint16_t expr_len =0;
    uint16_t data_char;
    uint16_t expr_char;
    //for(uint16_t id=0;id<3;id++) debug_pattern(id);
    debug_pattern(pattern_id);
    // the first index [0] of a pattern is its overall length
    // core functions and expressions are 16 bit int's
    //   Core functions are >= FF00
    //   everything below that is an expression
    // the limit for custom expressions + unique strings/characters is FF00-1

    uint16_t length=fragment[0];
    uint16_t res=0;
    uint16_t range1;
    uint16_t range2;
    //if this is the start of the pattern match
    ++pattern_pos;
    uint16_t pin,matched;
    printf("Length: %d",length);

    while (pattern_pos<=length){
        printf("\nPattern: %04x  Index: %04x",pattern_id,pattern_pos);
        expr_type=fragment[pattern_pos];
        ++pattern_pos;
        if(expr_type<0xFF00) {
            expr_len=1;
        } else {
            expr_len =fragment[pattern_pos];
            ++pattern_pos;
        }
        
        //at this point, the pattern_pos index will be at the next  component

        uint16_t *sub_expr=get_next_level(pattern_id,pattern_pos,expr_len);


        printf("\n%s,%d\n",get_type(expr_type),pattern_pos);
        char c = getchar( );
        printf("\n%c\n",c);
        switch(expr_type){
            case TYP_CHR:        
            case TYP_STR:   matched=0;
                            while (matched<expr_len){
                                expr_char=fragment[pattern_pos];
                                data_char=(char)text[pos+matched];
                                if (expr_char != data_char ) break;
                                ++matched;
                            }
                            if (matched==expr_len) pos+=expr_len;
                            else return 0;
                            break;

            case TYP_RNG:   range1=fragment[pattern_pos+1]; 
                            range2=fragment[pattern_pos+2];
                            data_char=(char)text[pos+1];
                            if (data_char<range1 || data_char>range2) return 0;
                            pos++;
                            break;


            case TYP_GRP:   res=core_parse(text,pattern_id,pattern_pos,pos);
                            if (res!=0) pos=res;
                            else return 0;
                            break;

            case TYP_OPT:   res=core_parse(text,pattern_id,pattern_pos,pos);
                            if (res!=0) pos=res;
                            break;

            case TYP_OR :   matched=0;
                            for(int i=0;i<expr_len;i++){
                                res=core_parse(text,pattern_id,sub_expr[i],pos);
                                if (res!=0) {
                                    pos=res;
                                    ++matched;
                                    break;
                                }
                            } //end for
                            if (matched==0) {
                                return 0;
                            }
                            break;

      
            case TYP_NOT:   res=core_parse(text,pattern_id,pattern_pos,pos);
                            if (res==0) pos+=1;
                            else return 0;
                            break;
                            
            case TYP_OOM:   matched=0;
                            pin=0;
                            res=1;
                            while(res!=0){
                                pin=pos;
                                for(int i=0;i<expr_len;i++){
                                    res=core_parse(text,pattern_id,sub_expr[i],pos);
                                    if (res!=0) {
                                        pos=res;
                                    }  else {
                                        break;
                                    }
                                } //end for
                                if (res==0) {
                                    pos=pin;
                                    break;
                                } else { 
                                    ++matched; 
                                }
                            } //end while
                            if (matched==0) return 0;
                            break;
            
                            
            case TYP_ZOM:   pin=0;
                            res=1;
                            while(res!=0){
                                pin=pos;
                                for(int i=0;i<expr_len;i++){
                                    res=core_parse(text,pattern_id,sub_expr[i],pos);
                                    if (res!=0) {
                                        pos=res;
                                    }  else {
                                        break;
                                    }
                                } //end for
                                if (res==0) {
                                    pos=pin;
                                    break;
                                } 
                            } //end while
                            break;
            
            

                            
                            
            //if its not a core funciton or grouping, it's an expression / user function
            default:    res=core_parse(text,fragment[pattern_pos],0,pos);
                        if (res!=0) pos=res;
                        else return 0;

        }//end switch
        pattern_pos+=expr_len;
    }//end loop
    return pos;
}
