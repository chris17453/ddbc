#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "headers/func.h"

#define BUF_SIZE 512
#define BUF_MIN 128


char *get_stdin(){
  char *input, *p;
  int len, remain, n, size;

  size = BUF_SIZE;
  input = malloc(size);
  len = 0;
  remain = size;
  while (!feof(stdin)) {
      if (remain <= BUF_MIN) {
          remain += size;
          size *= 2;
          p = realloc(input, size);
          if (p == NULL) {
            free(input);
            return NULL;
          }
          input = p;
      }
      fgets(input + len, remain, stdin);
      n = strlen(input + len);
      len += n;
      remain -= n;
  }
  return input;
}//end get_stdin


char* read_file(char *file){
  FILE *fptr;
  char *buffer=0;
  long length=0;

   if ((fptr = fopen(file,"r")) == NULL){
       printf("Error! opening file: %s",file);
       exit(1);
   }
    
  if (fptr) {
    fseek (fptr, 0, SEEK_END);
    length = ftell (fptr);
    fseek (fptr, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)    {
      fread (buffer, 1, length, fptr);
    } else {
      printf("Cannot allocate memory for file read.");
      exit(1);
    }
    fclose (fptr);
  }
  return buffer;

}

int main(int argc, char* argv[]) {
    char *query_str;
    // if not a terminal grab from pipe
    if (!isatty(0)) {   
      query_str=get_stdin();
    } else {  //args at this point
      if (argc==1){
        printf("\n");
        printf("usage:\n");
        printf("   ddbc query.sql\n");
        printf("   cat query.sql| ddbc\n");
        printf("   ddbc<query.sql\n");
        return 0;
      }
      char *file=argv[1];
      query_str=read_file(file);
    }


    //printf("Query: %s\n \n",query_str);
    match_function(query_str);
    free(query_str);
    return 0;
}


/****
 * F5                for debug
 * CTRL + SHIFT + B  to build 
 * vscode requires launch.json andtask.json to be setup for this to work.
 * sofar the project is manually created as a command to gcc to build...
 ****/