#include <stdio.h>
#include <math.h>
#include <cassert>
#include <stdlib.h>

#ifndef RELEASE
	#define DEBUG printf("\x1b[35m>> debug from <%s::%d>\n\x1b[0m", __FILE__, __LINE__);
#else
	#define DEBUG
#endif

static const int NO_MEMORY = -1;
#define CANARY_VALUE1 0xDEADBEAF
#define CANARY_VALUE2 0xBADF00D

template <class D>
class Stack 
{
  private:
  
  	int canary1;
  	
  	D* buffer;
  	int length;
  	int pointer;
  	int checking_level;
  	unsigned long long hash; 
  	FILE* file_dump;
  	
  	int canary2;
  	
  public:
  
  	enum Level
  	{
  		NO_CHECK,
  		EASY_CHECK,
  		HARD_CHECK
  	};
  	
  	enum Errors
  	{
  		OK,
  		NO_MEMORY,
  		NO_ELEM,
  		BAD_POINTER,
  		ERR_CODE_HASH,
  		ERR_CODE_CANARY1,
  		ERR_CODE_CANARY2,
  		ERRORS_COUNT
  	};
  	  	
  	Stack();
  	~Stack();
  	int push(D data);
  	D pop();
  	unsigned long long get_hash(unsigned long long get_elem_hash(D)); //get_elem_hash непосредственно перед использованием.
  	int Check(unsigned long long get_elem_hash(D elem)); // Check
  	int dump();
  	void asserting();
};




/////////////////////////////////////////////////


unsigned long long get_elem_hash(int elem)
{
	return (unsigned long long)elem;
}

int main()
{
	Stack<int> stk;
	
	stk.push(5);
	stk.push(7);
	stk.push(123);
	int a = stk.pop();
	int b = stk.pop();
	int c = stk.pop();
	printf("Poped = %d %d %d\n", a, b, c);

	stk.dump();
	
	return 0;
}

/////////////////////////////////////////////////



template <class D>
Stack<D>::Stack()
{
	this -> file_dump = fopen("Dump.txt", "wb");
	
	this -> length = 4;
	//this -> buffer = (D*) calloc(this -> length, sizeof(D));
	this -> buffer = new D[this -> length]; // delete[] this -> buffer
	
	this -> pointer = 0;
	
	this -> canary1 = CANARY_VALUE1;
	this -> canary2 = CANARY_VALUE2;
	
}

template <class D>
Stack<D>::~Stack()  
{
	fclose(file_dump);
	
	if (this -> buffer != NULL)
		delete[] this -> buffer;
}

template <class D>
int Stack<D>::push(D data)
{
	this -> asserting();

	if (this -> pointer >= (this -> length) - 1)
	{
		int new_length = (this -> length) * 2;
		
		//this -> buffer = (D*) realloc(this -> buffer, this -> length * sizeof(D)); 
		D* new_buffer = new D[new_length];
		
		for (int i = 0; i < this -> length; i++)
		{
			new_buffer[i] = (this -> buffer)[i];
		}
		
		delete[] (this -> buffer);
		this -> buffer = new_buffer;
		this -> length = new_length;
		
		if (this -> buffer == NULL)
		{
			printf("Cannot allocate memory\n");
			return NO_MEMORY;
		}
	}
	
	this -> buffer[++(this -> pointer)] = data;
	
	this -> asserting();
	
	return 0;
	
}

template <class D>
D Stack<D>::pop()
{

	this -> asserting();

	if((this -> pointer) <= 0)
		assert(!"Stack is underflow");
		
	D elem = (this -> buffer)[this -> pointer];
	(this -> pointer)--;
	
	if((this -> length) >= 2 * ((this -> pointer) + 2))
	{
		int new_length = (this -> length)/2;
		D* new_buffer = new D[new_length];
		for(int i = 0; i < this -> length; i++)
		{
			new_buffer[i] = (this -> buffer)[i];
		}
		
		delete[] (this -> buffer);
		this -> buffer = new_buffer;
		this -> length = new_length;
		
	}	
	
	this -> asserting();
	
	return elem;
}



template <class D>
unsigned long long Stack<D>::get_hash(unsigned long long get_elem_hash(D))
{
	unsigned long long hash = 0;
	for (int i = 0; i < (this -> length) - 1; i++)
	{
		hash = hash * i + get_elem_hash((this -> buffer)[i]);
	}
	
	return hash;
}


template <class D>
void Stack<D>::asserting()
{
	
	if (!(this -> Check(get_elem_hash)))
	{
		if (this -> checking_level == this -> EASY_CHECK)
		{
			printf("ERROR!!! %X\n", this -> Check(get_elem_hash));
		}
		
		if (this -> checking_level == this -> HARD_CHECK)
		{
			this -> dump();
			assert(!"error\n");
		}
	}
}


template <class D>
int Stack<D>::dump()
{
	if (this -> file_dump == NULL)
	{
		printf("Can't find the file to write the errors\n");
        return this -> BAD_POINTER;
	}
	
	if(this == NULL)
	{
		fprintf(this -> file_dump, "Pointer to this stack is bad:(\n");
		return this -> BAD_POINTER;
	}
	
	fprintf(this -> file_dump, "This stack [%p]\n", this);
	fprintf(this -> file_dump, "Stack length = %d\n", this -> length);
	fprintf(this -> file_dump, "Pointer in stack = %d\n", this -> pointer);
	for (int i = 0; i < (this -> length); i++)
	{
		fprintf(this -> file_dump, "Data[%d] = %d\n", i, (this -> buffer)[i]);
	}
	
	fprintf(this -> file_dump, "Canary 1 = %d (%d)\n", this -> canary1, CANARY_VALUE1);
	fprintf(this -> file_dump, "Canary 2 = %d (%d)\n", this -> canary2, CANARY_VALUE2);
	
	return 0;
}


template <class D>
int Stack<D>::Check(unsigned long long get_elem_hash(D elem))
{
	unsigned long long hash = 0;
	for(int i = 0; i < this -> length; i++)
	{
		hash = hash + get_hash(get_elem_hash);
	}
	
	if(hash != (this -> hash))
		return this -> ERR_CODE_HASH;
		
	if((this -> canary1) != CANARY_VALUE1)
		return this -> ERR_CODE_CANARY1;
		
	if((this -> canary2) != CANARY_VALUE2)
		return this -> ERR_CODE_CANARY2;
		
	return OK;
}




















