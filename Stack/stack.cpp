#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define CANARY_VALUE1 0xDEADBEAF
#define CANARY_VALUE2 0xBADF00D
#define ERR_CODE_HASH 0xBADCAD
#define ERR_CODE_CANARY1_STRUCT 0xBADBE
#define ERR_CODE_CANARY2_STRUCT 0xBADED
#define ERR_CODE_CANARY1_STACK 0xBEDAA
#define ERR_CODE_CANARY2_STACK 0xBEDAB
#define ERR_CODE_STRUCT_HASH 0xBABABEDA
#define UNDERFLOWING_STACK -2
#define BAD_POINTER -3

#define MEOW

#ifdef MEOW 
    #define TRACE stack_dump(stk)
#else
    #define TRACE printf("ERROR!!!!!\n")
#endif


typedef int Elem_t;


struct Stack_t
{
    int canary1;

	Elem_t* data;
	int size;
	int buffer_size;
    unsigned long long hash;
    unsigned long long struct_hash;
    FILE* file_dump;

    int canary2;
};

void stack_construct(Stack_t* stk, int size);
unsigned long long get_struct_hash(const Stack_t* stk);
void stack_push(Stack_t* stk, Elem_t elem);
Elem_t stack_pop(Stack_t* stk);
unsigned long long get_hash(const Stack_t* stk);
int stack_OK(const Stack_t* stk);
void stack_assert(Stack_t* stk);
int stack_dump(Stack_t* stk);

//TODO struct hash
//TODO buffer canaries
//TODO if in dumps
//TODO dump is a part of stack struct 
//TODO #ifdef safe and fast stack

/*int main()
{
    int size = 4;
    Stack_t stk;
    
    stack_construct(&stk, size);

    stack_push(&stk, 5);
    stack_push(&stk, 6);
    stack_push(&stk, 7);
    stack_push(&stk, 8);
    stack_push(&stk, 9);
    stack_push(&stk, 10);
    stack_push(&stk, 11);
    stack_push(&stk, 12);
    stack_push(&stk, 13);

    Elem_t x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    x = stack_pop(&stk);
    printf("%d\n", x);
    
    stk.data[3] = 99;
    
    x = stack_pop(&stk);
    printf("%d\n", x);
    
    stack_push(&stk, 36);
    printf("%d\n", stack_pop(&stk));
    
    return 0;
}*/



void stack_assert(Stack_t* stk)
{
    if (stack_OK(stk) != 1)
    {
        TRACE;
        assert(!"error");
    }
}


unsigned long long get_struct_hash(const Stack_t* stk)
{
    unsigned long long struct_hash = stk -> canary1 ^ 
                                    (long long int)(stk -> data) ^
                                    (stk -> size) ^ (stk -> buffer_size) ^
                                    (stk -> hash) ^ (stk -> canary2);
    return struct_hash;
}


void stack_construct(Stack_t* stk, int size)
{
	assert(stk);
    
    (stk -> canary1) = CANARY_VALUE1;

	stk -> data = (Elem_t*) calloc(sizeof(Elem_t), size + 2);
	
	(stk -> data) [0] = CANARY_VALUE1;// const ftok
	(stk -> data)[size + 1] = CANARY_VALUE2;
	
	stk -> size = 1;
	stk -> buffer_size = size + 2;
	
	stk -> hash = get_hash(stk);
	
    stk -> file_dump = fopen("Dump.txt", "wb");
    
    (stk -> canary2) = CANARY_VALUE2;
    
    stk -> struct_hash = get_struct_hash(stk);

    stack_assert(stk);

}



void stack_push(Stack_t* stk, Elem_t elem)
{
    stack_assert(stk);

	if ((stk -> size) >= (stk -> buffer_size - 1))
	{
	    //printf("reallocing from %d to %d\n", stk -> buffer_size, stk -> buffer_size*2);
		stk -> buffer_size *= 2;
		stk -> data = (Elem_t*) realloc(stk -> data, 
		                               (stk -> buffer_size) * sizeof(Elem_t));
		(stk -> data)[stk -> buffer_size - 1] = CANARY_VALUE2;
	}


	stk -> data[stk -> size] = elem;
    (stk -> size)++;

    (stk -> hash) = get_hash(stk);
    (stk -> struct_hash) = get_struct_hash(stk);

    stack_assert(stk);
}




Elem_t stack_pop(Stack_t* stk)
{
    stack_assert(stk);
    
    if ((stk -> size) < (stk -> buffer_size)/2 - 1)
	{
		stk -> buffer_size /= 2;
		stk -> data = (Elem_t*) realloc(stk -> data, 
		                                (stk -> buffer_size) * sizeof(Elem_t));
		(stk -> data)[stk -> buffer_size - 1] = CANARY_VALUE2;                                
	}

	if((stk -> size) <= 0)
	{
		printf("Stack is underflow\n");
		return UNDERFLOWING_STACK;
	}
	
    (stk -> size)--;
	Elem_t poped = stk -> data[stk -> size];

    (stk -> hash) = get_hash(stk);
    (stk -> struct_hash) = get_struct_hash(stk);

    stack_assert(stk);
	
	return poped;
}



unsigned long long get_hash(const Stack_t* stk)
{

    unsigned long long hash = 0;

    for (int i = 0; i < (stk -> buffer_size); ++i)
    {
        hash = hash * i + (stk -> data)[i];
    }

     return hash;
}



int stack_OK(const Stack_t* stk)
{
	if(stk == NULL)
	{
	    printf("Bad pointer to stack\n");
	    return BAD_POINTER;
	}
	
    unsigned long long hash = get_hash(stk);
    unsigned long long struct_hash = get_struct_hash(stk);
    
    if (hash != (stk -> hash))
        return ERR_CODE_HASH;

    if ((stk -> canary1) != CANARY_VALUE1)
        return ERR_CODE_CANARY1_STRUCT;

    if ((stk -> canary2) != CANARY_VALUE2)
        return ERR_CODE_CANARY2_STRUCT;
        
    if((stk -> data)[0] != CANARY_VALUE1)
        return ERR_CODE_CANARY1_STACK;
        
    if((stk -> data)[stk -> buffer_size - 1] != CANARY_VALUE2)
        return ERR_CODE_CANARY2_STACK;
        
    if(struct_hash != (stk -> struct_hash))
        return ERR_CODE_STRUCT_HASH;

    return 1;

}



int stack_dump(Stack_t* stk)
{
    //FILE* file_dump = fopen("Dump.txt", "wb");
    if(stk -> file_dump == NULL)
    {
        printf("Can't find the file to write the errors\n");
        return BAD_POINTER;
    }
    
    if(stk == NULL)
    {
        fprintf(stk -> file_dump, 
                "Pointer to stack is bad:( \n pointer to stk = NULL\n");
        return BAD_POINTER;
    }
    
    fprintf(stk -> file_dump, "Stack stk [%p] \n", stk);
    fprintf(stk -> file_dump,"Stack buffer_size = %d\n", stk -> buffer_size);
    fprintf(stk -> file_dump, "Stack size = %d\n", stk -> size);
    for (int i = 0; i < stk -> buffer_size; i++)
    {
        fprintf(stk -> file_dump, "Data[%d] = %d\n", i, (stk -> data)[i]);
    }
    fprintf(stk -> file_dump, "result of stack_OK = %X\n", stack_OK(stk));
    fclose(stk -> file_dump);
    return 0;
}






//end;

