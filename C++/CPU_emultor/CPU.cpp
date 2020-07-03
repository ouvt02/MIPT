#include <stdio.h>
#include <math.h>
#include "stack.cpp"


class virtual_cpu
{
  private:

	float ax;
	float bx;
	float cx;
	float dx;
	int PC;
	float* rsp;
	
	float* RAM;
	int proga_size;
	
  public:
	enum Commands
	{
		IN_CMD = 1,
		OUT_CMD,
		MUL_CMD,
		DIV_CMD,
		ADD_CMD,
		SUB_CMD,
		SQRT_CMD,
		POP_CMD,
		PUSH_CMD,
		POPNX_CMD,
		PUSHNX_CMD,
		SIN_CMD,
		COS_CMD,
		JMP_CMD,
		JA_CMD,
		JAE_CMD,
		JB_CMD,
		JBE_CMD,
		JE_CMD,
		JNE_CMD,
		END_CMD
	}
	
	virtual_cpu();
	~virtual_cpu();
	
	void open();
	
	void in();
	void out();
	void mul();
	void div();
	void add();
	void sub();
	void sqrt();
	void popnx(float** proga)
	void pushnx(float** proga)
	void sinus();
	void cosinus();
	void ja();
	void jae();
	void jb();
	void jbe();
	void je();
	void jne();
	
}

int getsize(const char* name)
{
	FILE* file_proga = fopen(name, "rd");
	
	fseek(file_proga, 0, SEEK_END); //указатель на конец файла
	
	size_t sizeoffile = ftell (file_proga); //разница между началом и ук.
	
	rewind (file_proga); //возвращает поинтер на начало файла
	
	return sizeoffile;
}

void virtual_cpu::open(const char* proga_name)//in main
{
	this -> proga_size = getsize(proga_name);
	this -> RAM = new float [1024 + proga_size];
	
	FILE* proga_file = fopen(proga_name, "rb");
	float* proga = this -> RAM + 1024; 
	fread(proga, sizeof(char), proga_size, proga_file);
}


virtual_cpu::virtual_cpu()
{

	this -> PC = 0;
	this -> ax = 0;
	this -> bx = 0;
	this -> cx = 0;
	this -> dx = 0;
	this -> rsp = (this -> RAM) + 1024;
}


virtual_cpu::~virtual_cpu()
{
	fclose(this -> file_code);
	
	if(this -> RAM != NULL)
	{
		delete[] this -> RAM;
	}
}



int virtual_cpu::execute()

{
	float* proga = this -> RAM + 1024
	
	for(proga = this -> RAM + 1024; 
		proga < this -> RAM + 1024 + this -> proga_size; i++)
	{
		switch (&(proga))
		{
			case IN_CMD:
			{
				cpu.in();
				(this -> PC)++;
				break;
			}
			
			case OUT_CMD:
			{
				cpu.out();
				(this -> PC)++;
				break;
			}
			
			case MUL_CMD:
			{
				cpu.mul();
				(this -> PC)++;
				break;
			}
			
			case DIV_CMD:
			{
				cpu.div();
				(this -> PC)++;
				break;
			}
			
			case ADD_CMD:
			{
				cpu.add();
				(this -> PC)++;
				break;
			}
			
			case SUB_CMD:
			{
				cpu.sub();
				(this -> PC)++;
				break;
			}
			
			case SQRT_CMD:
			{
				cpu.sqrt();
				(this -> PC)++;
				break;
			}
			
			case POP_CMD:
			{
				cpu.pop();
				(this -> PC)++;
				break;
			}
			
			case PUSH_CMD:
			{
				cpu.push();
				(this -> PC)++;
				break;
			}
			
			case POPNX_CMD:
			{
				cpu.popnx(proga);
				(this -> PC)++;
				break;
			}
			
			case PUSHNX_CMD:
			{
				cpu.pushnx();
				(this -> PC)++;
				break;
			}
			
			case SIN_CMD:
			{
				cpu.sinus();
				(this -> PC)++;
				break;
			}
			
			case COS_CMD:
			{
				cpu.cosinus();
				(this -> PC)++;
				break;
			}
			
			case JMP_CMD:
			{
				this -> PC = &(proga + 1);
				break;
			}
			
			case JA_CMD:
			{
				cpu.ja();
				break;
			}
			
			case JAE_CMD:
			{
				cpu.jae();
				break;
			}
			
			case JB_CMD:
			{
				cpu.jb();
				break;
			}
			
			case JBE_CMD:
			{
				cpu.jbe();
				break;
			}
			
			case JE_CMD:
			{
				cpu.je();
				break;
			}
			
			case JNE_CMD:
			{
				cpu.jne();
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
		
		proga = this -> RAM + 1024 + PC;
	}
}

void virtual_cpu::in()
{
	float a = 0;
	scanf("%f", &a);
	&(this -> rsp) = a;
	(this -> rsp)--;
}

void virtual_cpu::out()
{
	(this -> rsp)++;
	float a = &(this -> rsp);
	printf("%f\n", a);
}

void virtual_cpu::mul()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	float c = a * b;
	
	&((this -> rsp)--) = c;
}


void virtual_cpu::div()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	float c = a / b;
	
	&((this -> rsp)--) = c;
}

void virtual_cpu::add()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	float c = a + b;
	
	&((this -> rsp)--) = c;
}

void virtual_cpu::sub()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	float c = a - b;
	
	&((this -> rsp)--) = c;
}

void virtual_cpu::sqrt()
{
	float a = &(++(this -> rsp));	
	float c = sqrtf(a);
	
	&((this -> rsp)--) = c;
}

void virtual_cpu::ja()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	if(a > b)
		(this -> PC) = &(++proga);
	else
		proga++;
}

void virtual_cpu::jae()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	if(a >= b)
		(this -> PC) = &(++proga);
	else
		proga++;
}

void virtual_cpu::jb()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	if(a < b)
		(this -> PC) = &(++proga);
	else
		proga++;
}

void virtual_cpu::jbe()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	if(a <= b)
		(this -> PC) = &(++proga);
	else
		proga++;
}

void virtual_cpu::je()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	if(a == b)
		(this -> PC) = &(++proga);
	else
		proga++;
}

void virtual_cpu::jne()
{
	float a = &(++(this -> rsp));
	float b = &(++(this -> rsp));
	
	if(a != b)
		(this -> PC) = &(++proga);
	else
		proga++;
}


void virtual_cpu::pop()
{
	if(this -> rsp < 1024)
		(this -> rsp)++;
}

void virtual_cpu::push()
{
	if(this -> rsp > 0)
		(this -> rsp)--;
}

void virtual_cpu::popnx(float** proga)//из стека в регистр
{
	if(&(++(&proga)) == 1)
	{
		this -> ax = &(++(this -> rsp));
		return;
	}
	
	if(&(++(&proga)) == 2)
	{
		this -> bx = &(++(this -> rsp));
		return;
	}
	
	if(&(++(&proga)) == 3)
	{
		this -> cx = &(++(this -> rsp));
		return;
	}
	
	if(&(++(&proga)) == 4)
	{
		this -> dx = &(++(this -> rsp));
		return;
	}
	
	printf("Unknown command\n");
	return;
}


void virtual_cpu::pushnx(float** proga)
{
	if(&(++(&proga)) == 1)
	{
		&((this -> rsp)--) = this -> ax;
		return;
	}
	
	if(&(++(&proga)) == 2)
	{
		&((this -> rsp)--) = this -> bx;
		return;
	}
	
	if(&(++(&proga)) == 3)
	{
		&((this -> rsp)--) = this -> cx;
		return;
	}
	
	if(&(++(&proga)) == 4)
	{
		&((this -> rsp)--) = this -> dx;
		return;
	}
	
	printf("Unknown command\n");
	return;
}



