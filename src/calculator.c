#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>


#include "../include/calculator.h"
#include "../include/config.h"


float perform_operation(float a, float b, char act){
    switch (act){
        case '+': return a+b;
        case '-': return a-b;           
        case '*': return a*b;           
        case '/':
            if (b == 0) {
            printf("Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
            return a/b;
        default:
            printf("Wrong operation '%c'", act);
            exit(EXIT_FAILURE);
    }
    return 0;
}

void process_high_priority_operations(float* Nums,int* Num_Size,char* Act, int* Act_Size){
    for(int i = 0; i < *Act_Size; i++){
        if(Act[i] == '/' || Act[i] == '*'){
            float New_Val = perform_operation(Nums[i],Nums[i+1],Act[i]);
            Nums[i] = New_Val;
            memmove(&Nums[i+1],&Nums[i+2],(*Num_Size - (i + 2)) * sizeof(Nums[i]));
            (*Num_Size)--;
            memmove(&Act[i],&Act[i+1],(*Act_Size - (i + 1)) * sizeof(Act[i]));
            (*Act_Size)--;
            process_high_priority_operations(Nums,Num_Size,Act,Act_Size);
            return;
        }       
    }
}

void process_low_priority_operations(float* Nums,int* Num_Size,char* Act, int* Act_Size){
    for(int i = 0; i < *Act_Size; i++){
        if(Act[i] == '+' || Act[i] == '-'){
            float New_val = perform_operation(Nums[i],Nums[i+1],Act[i]);
            Nums[i] = New_val;
            memmove(&Nums[i+1],&Nums[i+2],(*Num_Size - (i + 2)) * sizeof(Nums[i]));   
            (*Num_Size)--;
            memmove(&Act[i],&Act[i+1],(*Act_Size - (i + 1)) * sizeof(Act[i]));
            (*Act_Size)--;
            process_low_priority_operations(Nums,Num_Size,Act,Act_Size);
            return;
        }  
    }
}

float calculate_expression(float* Nums,int* NumSize,char* Act, int* ActSize){
    
    process_high_priority_operations(Nums,NumSize,Act,ActSize); // counting * and / operations
    process_low_priority_operations(Nums,NumSize,Act,ActSize); // + and - aperations
    
    return Nums[0];
}

float get_complete_integer(char* src,int* j){
    
    double res = 0;
    while(isdigit(src[(*j)])){
        res *= 10;
        res += src[(*j)] - '0';
        (*j)++;
    }
    if(src[(*j)] == '.' && isdigit(src[(*j)+1])){
        (*j)++;
        double point = 0;
        int point_part = 1;
        while(isdigit(src[(*j)])){
            point*=10;
            point +=src[(*j)]-'0';
            point_part *= 10;
            (*j)++;
        }
        res += (float)(point/point_part);
    }

    return res;

}



void calculator(char** src,int size){
    int source_overflow_detector = 0;
    for(int i = 1;i < size; i++){
        source_overflow_detector += (int)strlen(src[i]); // buffer overflow detection,if count of symbols in argument is more than ARRAY_MAX_SIZE - exit function
    }
    if(source_overflow_detector >= ARRAY_MAX_SIZE){
        printf("Too many arguments in function \"calculator\"\n");
        return;
    }
    char source[ARRAY_MAX_SIZE];
    int sourse_length = 0;
    for(int i = 1; i < size;i++){
        for(int j = 0; j<(int)strlen(src[i]);j++){
            
                source[sourse_length++] = src[i][j]; // make a char* from char** 

            
        }
    }
    source[sourse_length] = '\0';
    
    float Numbers[ARRAY_MAX_SIZE];
    int Nums_Size = 0;
    char Act[ARRAY_MAX_SIZE];
    int Act_Size = 0;
    int i = 0, was_operator = 1, is_negative = 0;
    while(source[i] != '\0' ){
        while(isspace(source[i])){
            i++;
        }
        if(was_operator == 1 && source[i] == '-' && isdigit(source[i+1])){ //checking if next number is negative 
            is_negative = 1;
            i++;
        }

        else if(isdigit(source[i])){
            Numbers[Nums_Size] = get_complete_integer(source,&i); // gets integer from string untill space symbol or anything else but '.' 
            
            if(is_negative == 1){
                Numbers[Nums_Size] *= -1;
                is_negative = 0;
            }
            was_operator = 0;
            Nums_Size++; 
        
        }
        else if(source[i] == '-' || source[i] == '+' || source[i] == '*' || source[i] == '/'){ // gets operator
            if(was_operator == 0){
                Act[Act_Size++] = source[i++];
                was_operator = 1;
            }else{
                printf("Worng input\n"); // if twice operator and its not negative symbol - exit function
                return;
            }
        }
        else{
            if(!isspace(source[i]) && source[i] != '\0'){
                printf("Wrong input\n");
                return;
            }else i++;
            
        }
        
    }
    printf("%g\n",calculate_expression(Numbers,&Nums_Size,Act,&Act_Size));

}
