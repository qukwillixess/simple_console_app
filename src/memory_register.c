#include<stdio.h>
#include<stdlib.h>
#include <string.h> 

#include "../include/memory_register.h"
#include "../include/config.h"

Mem_reg * memory_registration(void){   //difine pointer in first call,and returns same pointer every time
    static Mem_reg * result = NULL;
    if(result == NULL){
        result =  calloc(1,sizeof(Mem_reg));
        if(result == NULL){
            printf("Memory register allocation failed\n");
            exit(EXIT_FAILURE);
        }
        result->length = 0;
        result->data = (void**)malloc(sizeof(void*));
        if(result->data == NULL){
            printf("Memory register array allocation failed\n");
            exit(EXIT_FAILURE);
        }
        atexit(memory_clear);
    }
    
    return result;

}

void memory_pointer_push(void * val){
    Mem_reg * mem = memory_registration();
    void ** tmp = realloc(mem->data,sizeof(void*) * ( mem->length + 1));
    if(tmp==NULL){
        printf("Memory registration push pointer failed\n");
        exit(EXIT_FAILURE);
    }
    mem->data = tmp;
    mem->data[mem->length++] = val;

}

void memory_pointer_remove(void * pointer){
    Mem_reg * mem = memory_registration();

    for(int i =0; i<mem->length; i++){
        if(((void**)mem->data)[i] == pointer){
            memmove(&((void**)mem->data)[i],&((void**)mem->data)[i+1],(mem->length - (i+1)) * sizeof(void*));
            mem->length--;
            return;
        }
    }
    printf("Memory pointer remove failed: No pointer found\n");
    exit(EXIT_FAILURE);    
}

void memory_clear(void){  
    Mem_reg * mem = memory_registration();
    if(mem->data != NULL){
        if(mem->length != 0){
            for(int i = mem->length - 1; i >= 0; i--){
                free(((void**)mem->data)[i]);
                ((void**)mem->data)[i] = NULL;
            }
        }
        free(mem->data);
        mem->data = NULL;
    }
    free(mem);
}