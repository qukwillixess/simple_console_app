#ifndef MEMORY_REGISTER
#define MEMORY_REGISTER

typedef struct Memory_Register_Base{
    int length;
    void** data;
}Mem_reg;




Mem_reg* memory_registration (void);
void  memory_pointer_push    (void*);
void  memory_pointer_remove  (void*);
void  memory_clear           (void);
#endif