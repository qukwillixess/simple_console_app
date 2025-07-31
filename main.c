#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include "include/memory_register.h"
#include "include/input_parser.h"
#include "include/calculator.h"
#include "include/dynamic_array.h"


int main(void){
    memory_registration();

    while(1){
        Arr arr;
        arr_init(&arr,sizeof(char));

        int c;
        printf(">");
        while((c=getchar())!= EOF && c!='\n'){
            arr_push(&arr,(void*)&c);
        }

        if (arr.elements == arr.allocated) {
            arr_resize(&arr);
        }

        ((char*)arr.arr)[arr.elements] = '\0';
        input_parser(&arr);
    }
    
    return EXIT_SUCCESS;
}
