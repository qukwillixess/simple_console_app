#ifndef CALCULATOR
#define CALCULATOR

void  calculator                       (char**,int);
float calculate_expression             (float*, int*, char*, int*);
float get_complete_integer             (char* src,int* j);
float perform_operation                (float, float, char);
void  process_high_priority_operations (float*, int*, char*, int*);
void  process_low_priority_operations  (float*, int*, char*, int*);

#endif