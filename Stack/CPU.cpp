#include <stdio.h>
#include <math.h>

enum comands {IN_CMD = 1, OUT_CMD, MUL_CMD, DIV_CMD, ADD_CMD, SUB_CMD,
              SQRT_CMD, POP_CMD, PUSH_CMD, POPNX_CMD, PUSHNX_CMD, SIN_CMD,
              COS_CMD, JMP_CMD, END_CMD, JA_CMD, JAE_CMD, JB_CMD, JBE_CMD
              JE_CMD, JNE_CMD};

struct buf 
{
    Elem_t ax;
    Elem_t bx;
    Elem_t cx;
    Elem_t dx;
}

int execution_program(argv[1])
{
 
    buf memory;
    
    Stack_t stk;
    
    FILE* file_code = fopen(argv[1], "rb");
    
    size_t sizeoffile = getsize(argv[1]);
    
    int* buffer = (int*) calloc(sizeoffile, sizeof(int));
    
    fread(buffer, sizeof(int), sizeoffile, file_code);   

    int PC = 0;    
    
    for(int i = 0; i < sizeoffile; i++) 
    {
    	switch (buffer[i])
	    {
	    	case IN_CMD:
	    	{ 
                in(&stk);
                PC++;
                break;
            }
                
	    	case OUT_CMD:
	        {
	        	out(&stk);
	        	PC++;
	        	break;
	        }	
	    	case MUL_CMD:
	    	{
	    	    mul(&stk);
	    	    PC++;
	    	    break;
	    	}   
	    	case DIV_CMD:
	    	{
	    	    div(&stk);
	    	    PC++;
	    	    break;
	    	}   
	    	case ADD_CMD:
	    	{
	    	    add(&stk);
	    	    PC++;
	    	    break;
	    	}    
	    	case SUB_CMD:
	    	{
	    	    sub(&stk);
	    	    PC++;
	    	    break;
	    	}    
	    	case SQRT_CMD:
	    	{
	    	    sqrt(&stk);
	    	    PC++;
	    	    break;
	    	}    
	    	case POP_CMD:
	    	{
	    	    pop(&stk);
	    	    PC++;
	    	    break;
	    	}   
	    	case POPNX_CMD:
	    	{
	    	    popnx(&stk, &memory, buffer[i++]);
	    	    PC++;
	    	    break;
	    	}    
	        case PUSH_CMD:
	        {
	            push(&stk, buffer[i]);
	            i++;
	            PC++;
	            break;
	        }
	    	    
	    	case PUSHNX_CMD:
	    	{
	    	    pushnx(&stk, &memory, buffer[i++]);
	    	    PC++;
	    	    break;
	    	} 
	    	   
	    	case SIN_CMD:
	    	{
	    	    sinus(&stk);
	    	    PC++;
	    	    break;
	    	}    
	    	
	        case COS_CMD:
	        {
	            cosinus(&stk);
	            PC++;
	            break;
	        }  
	        
	        case JMP_CMD:
	        {
	            PC = jmp(title_of_label);
	            break;
	        }
	          
	        case END_CMD:
	        {
	            break;
	        }
	        
	    	    
	    	default:
	    	{
	    		printf("Unknown command\n");
	    		break;
	    	}
	    }
	}


void in(Stack_t* stk)
{
    Elem_t a = 0;
    scanf("d", &a);
    stack_push(stk, elem);
}

void out(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    printf("%d", a);
}

void mul(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    Elem_t b = stack_pop(stk);
    Elem_t c = a * b;
    stack_push(stk, c);
}

void div(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    Elem_t b = stack_pop(stk);
    Elem_t c = a / b;
    stack_push(stk, c);
}

void add(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    Elem_t b = stack_pop(stk);
    Elem_t c = a + b;
    stack_push(stk, c);
}

void sub(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    Elem_t b = stack_pop(stk);
    Elem_t c = a - b;
    stack_push(stk, c);
}

void sqrt(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    Elem_t b = sqrt(a);
    stack_push(stk, b);
}

void popnx(Stack_t* stk, buf* memory, buffer[i + 1])
{
    if (buffer[i + 1] == 1)
    {
        stack_push(stk, memory -> ax);
        return;
    }
    if (buffer[i + 1] == 2)
    {
        stack_push(stk, memory -> bx);
        return;
    }
    if (buffer[i + 1] == 3)
    {
        stack_push(stk, memory -> cx);
        return;
    }
    if (buffer[i + 1] == 4)
    {
        stack_push(stk, memory -> dx);
        return;
    }
    printf("Unknown command\n");
    return;
}

void pushnx(Stack_t* stk, buf* memory, buffer[i + 1])
{
    if (buffer[i + 1] == 1)
    {
        memory -> ax = stack_pop(stk);
        return;
    }
    if (buffer[i + 1] == 2)
    {
        memory -> bx = stack_pop(stk);
        return;
    }
    if (buffer[i + 1] == 3)
    {
        memory -> cx = stack_pop(stk);
        return;
    }
    if (buffer[i + 1] == 4)
    {
        memory -> dx = stack_pop(stk);
        return;
    }
    
    printf("Unknown command\n");
    return;
}

void sinus(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    stack_push(stk, sin(a));
}

void cosinus(Stack_t* stk)
{
    Elem_t a = stack_pop(stk);
    stack_push(stk, a);
}



void jmp(char* title_of_label, int number_of_label, int* PC)
{
    for(int i = 0; i < number_of_label; i++)
    {
        if((!strcmp((my_labels[i] -> title), title_of_label)))
        {
            *PC = my_labels[i] -> number;
            break;
        }
    }
}












