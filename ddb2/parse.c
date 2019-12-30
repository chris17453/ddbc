#include "headers/parse.h"
#include "headers/expressions.h"






void parse(char *text){
    core_parse(text,EXP_QUERIES,0);
}

void core_parse(void *text,uint16_t pattern_id,int pos){//,char character,char * data,char range1,char range2){
    int ok=0;

    /*if (ok==0) {
        return NULL;
    }
    */


    // this holds the action\type
    uint16_t type=0;
    char c;

    
    for(int index=1;index<pattern[pattern_id][0];index+=1){
        type=pattern[pattern_id][index];
        c=(char)&text[pos];
        
        switch(type){
            case TYP_CHR:        if(c == p) ok=1; break;
            case TYP_STR:        if(stricmp(text[pos],compare_string) ==0 ) ok=1; break;
            case TYP_RNG:             if (text[pos]>=range1 && text[pos]<=range2) ok=1; break;
            case TYP_GRP:             ok=core_parse(text,positition,character,data,range1,range2);   break;
            case TYP_OPT:          ok=core_parse(text,positition,character,data,range1,range2);
                                    if (ok==0) ok=1;
                                    break;
            case TYP_NOT:               ok=core_parse(text,positition,character,data,range1,range2);
                                    if (ok==0) ok=1; else ok=0;  //NEGATE
                                    break;
            case TYP_OOM:           while( ok==1 ) {
                                        ok=core_parse(text,positition,character,data,range1,range2);
                                    }
                                    break;
            case TYP_ZOM:           while( ok==1 ) {
                                        ok=core_parse(text,positition,character,data,range1,range2);
                                    }
                                    ok=1; 
                                    break;
            case TYP_EXP:           ok=core_parse(text,positition,character,data,range1,range2);
                                    ok=1; 
                                    break;
        }//end switch
    }//end loop

}
