#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define CANARY_VALUE1 0xDEADBEAF
#define CANARY_VALUE2 0xBADF00D
#define ERR_CODE_HASH 0xBADCAD
#define ERR_CODE_CANARY1 0xBADBE
#define ERR_CODE_CANARY2 0xBADED


typedef int Elem_t;


struct Stack_t
{
    int canary1;

	Elem_t* data;
	int size;
	int buffer_size;
    unsigned long long hash;

    int canary2;
};

void stack_construct(Stack_t* stk, int size);
void stack_push(Stack_t* stk, Elem_t elem);
Elem_t stack_pop(Stack_t* stk);
unsigned long long get_hash(const Stack_t* stk);
int stack_OK(const Stack_t* stk);
void stack_assert(Stack_t* stk);
void stack_dump(Stack_t* stk);
//TODO struct hash
//TODO buffer canaries
//TODO if in dumps
//TODO dump is a part of stack struct 

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
        stack_dump(stk);
        assert(!"error");
    }
}



void stack_construct(Stack_t* stk, int size)
{
	assert(stk);
    
    (stk -> canary1) = CANARY_VALUE1;

	stk -> data = (Elem_t*) calloc(sizeof(Elem_t), size);
	stk -> size = 0;
	stk -> buffer_size = size;
	stk -> hash = get_hash(stk);

    (stk -> canary2) = CANARY_VALUE2;

    stack_assert(stk);

}



void stack_push(Stack_t* stk, Elem_t elem)
{
    stack_assert(stk);

	if ((stk -> size) >= (stk -> buffer_size))
	{
	    //printf("reallocing from %d to %d\n", stk -> buffer_size, stk -> buffer_size*2);
		stk -> buffer_size *= 2;
		stk -> data = (Elem_t*) realloc(stk -> data, 
		                               (stk -> buffer_size) * sizeof(Elem_t));
	}


	stk -> data[stk -> size] = elem;
    (stk -> size)++;

    (stk -> hash) = get_hash(stk);

    stack_assert(stk);
}




Elem_t stack_pop(Stack_t* stk)
{
    stack_assert(stk);
    
    if ((stk -> size) < (stk -> buffer_size)/2)
	{
	    //printf("reallocing from %d to %d\n", stk -> buffer_size, stk -> buffer_size/2);
		stk -> buffer_size /= 2;
		stk -> data = (Elem_t*) realloc(stk -> data, 
		                                (stk -> buffer_size) * sizeof(Elem_t));
	}

	if((stk -> size) <= 0)
	{
		printf("Stack is underflow\n");
		return 0;
	}
	
    (stk -> size)--;
	Elem_t poped = stk -> data[stk -> size];

    (stk -> hash) = get_hash(stk);

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
	assert(stk);
	
    unsigned long long hash = get_hash(stk);
    
    if (hash != (stk -> hash))
        return ERR_CODE_HASH;

    if ((stk -> canary1) != CANARY_VALUE1)
        return ERR_CODE_CANARY1;

    if ((stk -> canary2) != CANARY_VALUE2)
        return ERR_CODE_CANARY2;

    return 1;

}



void stack_dump(Stack_t* stk)
{
    FILE* file_dump = fopen("Dump.txt", "wb");
    fprintf(file_dump, "Stack stk [%p] \n", stk);
    fprintf(file_dump,"Stack buffer_size = %d\n", stk -> buffer_size);
    fprintf(file_dump, "Stack size = %d\n", stk -> size);
    for (int i = 0; i < stk -> buffer_size; i++)
    {
        fprintf(file_dump, "Data[%d] = %d\n", i, (stk -> data)[i]);
    }
    fprintf(file_dump, "%X\n", stack_OK(stk));
    fclose(file_dump);
}






//end;

