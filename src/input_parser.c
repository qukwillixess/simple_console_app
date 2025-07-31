#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "../include/dynamic_array.h"
#include "../include/input_parser.h"
#include "../include/calculator.h"
#include "../include/config.h"

void input_parser(Arr* arr){
    char* command = (char*)arr->arr;

    Arr command_Parts;
    arr_init(&command_Parts,sizeof (char*) );
 
    int i = 0;

    while(command[i] != '\0'){
        while(isspace(command[i])){
            i++;
        }
        if (command[i] == '\0') break; 
        
        int j = 0;
        char Word[ARRAY_MAX_SIZE];

        while(command[i] != ' ' && command[i] != '\t' && command[i] != '\0'){
            if(j>=ARRAY_MAX_SIZE){
                printf("Too long word\n"); // buffer overflow checker
                exit(EXIT_FAILURE);
            }
            Word[j++] = command[i++];
        }

        Word[j] = '\0';

        char * str = strdup(Word);
        if(str == NULL){
            printf("Strdup = NULL\n");
            exit(EXIT_FAILURE);
        }
        arr_push(&command_Parts,&str);
        memory_pointer_push(str); 
    }
    input_reader((char**)command_Parts.arr,command_Parts.elements);
    return;
}

void input_reader(char** str,int size){

    if(strcmp(str[0], "exit") == 0){
        exit(EXIT_SUCCESS);
    }

    else if(strcmp(str[0], "help") == 0){
        printf("Available functions: calc  print  exit  \n"
            "\ncalc {arguments} \tdescription: calculate simple expressions         \texample: calc 12.3+12--12/5.23\n"
            "\nprint {arguments}\tdescription: print any string you write           \texample: print hello world\n"
            "\nexit             \tdescription: exit the programm                    \texample: exit\n"
            "\nclear            \tdescription: the same as \"clear\"function in terminal\texample: clear\n");
        return;
    }

    else if(strcmp(str[0],"clear") == 0){
        system("clear");
        return;
    }

    else if(strcmp(str[0], "calc" ) == 0){
        for(int i = 1; i<size - 1;i++){
            str[i][strlen(str[i])] = ' ';
        }
        calculator(str,size);
    }

    else if(strcmp(str[0], "print" ) == 0){
        for(int i = 1;i < size;i++){
            printf("%s ",str[i]);
        }
        printf("\n");
    }

    else{
        printf("Unknown command\n");
        return;
    }
        
}