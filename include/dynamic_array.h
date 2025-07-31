#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include<stdlib.h>
typedef struct Dynamic_Array_Base{
    void * arr;
    int allocated;
    int elements;
    size_t type;
}Arr;

void  arr_init     (Arr*, size_t);
void  arr_resize   (Arr*);
void  arr_push     (Arr*, void*);

#endif