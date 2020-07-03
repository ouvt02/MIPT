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
	int ip;
	float* sp;
	
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
	void execute();
	
	
/*	void in();
	void out();
	void mul();
	void div();
	void add();
	void sub();
	void sqrt();
	void popnx(float** proga);
	void pushnx(float** proga);
	void sinus();
	void cosinus();
	void ja();
	void jae();
	void jb();
	void jbe();
	void je();
	void jne();*/
	
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

	this -> ip = 0;
	this -> ax = 0;
	this -> bx = 0;
	this -> cx = 0;
	this -> dx = 0;
	this -> sp = (this -> RAM) + 1024;
}


virtual_cpu::~virtual_cpu()
{
	fclose(this -> file_code);
	
	if(this -> RAM != NULL)
	{
		delete[] this -> RAM;
	}
}



void virtual_cpu::execute()

{
	float* proga = this -> RAM + 1024
	float a = 0;
	float b = 0;
	
	for(proga = this -> RAM + 1024; 
		proga < this -> RAM + 1024 + this -> proga_size; i++)
	{
		switch (&(proga))
		{
			case IN_CMD:
			{
				float written = 0;
				scanf("%f", &a);
				&(this -> sp) = a;
				(this -> sp)--;
				(this -> ip)++;
				break;
			}
			
			case OUT_CMD:
			{
				(this -> sp)++;
				float outed = &(this -> sp);
				printf("%f\n", a);
				(this -> ip)++;
				break;
			}
			
			case MUL_CMD:
			{
				float mn1 = &(++(this -> sp));
				float mn2 = &(++(this -> sp));
				
				float pr = mn1 * mn2;
				
				&((this -> sp)--) = pr;
				(this -> ip)++;
				break;
			}
			
			case DIV_CMD:
			{
				float delim = &(++(this -> sp));
				float delit = &(++(this -> sp));
				
				float chastn = delim / delit;
				
				&((this -> sp)--) = chastn;
				(this -> ip)++;
				break;
			}
			
			case ADD_CMD:
			{
				float sl1 = &(++(this -> sp));
				float sl2 = &(++(this -> sp));
				
				float summ = sl1 + sl2;
				
				&((this -> sp)--) = summ;
				(this -> ip)++;
				break;
			}
			
			case SUB_CMD:
			{
				float slr1 = &(++(this -> sp));
				float slr2 = &(++(this -> sp));
				
				float razn = slr1 - slr2;
				
				&((this -> sp)--) = razn;
				(this -> ip)++;
				break;
			}
			
			case SQRT_CMD:
			{
				float perem = &(++(this -> sp));	
				float sq = sqrtf(perem);
				
				&((this -> sp)--) = sq;
				(this -> ip)++;
				break;
			}
			
			case POP_CMD:
			{
				if(this -> sp < 1024)
					(this -> sp)++;
				(this -> ip)++;
				break;
			}
			
			case PUSH_CMD:
			{
				if(this -> sp > 0)
					(this -> sp)--;
				(this -> ip)++;
				break;
			}
			
			case POPNX_CMD:
			{
				if(&(++proga) == 1)
					this -> ax = &(++(this -> sp));
				
				else if(&(++proga) == 2)
					this -> bx = &(++(this -> sp));
				
				else if(&(++proga) == 3)
					this -> cx = &(++(this -> sp));
				
				else if(&(++proga) == 4)
					this -> dx = &(++(this -> sp));
				
				else
					printf("Unknown command\n");

				(this -> ip)++;
				break;
			}
			
			case PUSHNX_CMD:
			{
				if(&(++proga) == 1)
					&((this -> sp)--) = this -> ax;
				
				else if(&(++proga) == 2)
					&((this -> sp)--) = this -> bx;
				
				else if(&(++proga) == 3)
					&((this -> sp)--) = this -> cx;
				
				else if(&(++proga) == 4)
					&((this -> sp)--) = this -> dx;
				
				else
					printf("Unknown command\n");

				(this -> ip)++;
				break;
			}
			
			case SIN_CMD:
			{
				(this -> sp)++;
				a = &(this -> sp);
				b = sin(a);
				&((this -> sp)--) = b;
				(this -> ip)++;
				break;
			}
			
			case COS_CMD:
			{
				(this -> sp)++;
				a = &(this -> sp);
				b = cos(a);
				&((this -> sp)--) = b;
				(this -> ip)++;
				break;
			}
			
			case JMP_CMD:
			{
				this -> ip = &(proga + 1);
				break;
			}
			
			case JA_CMD:
			{
				a = &(++(this -> sp));
				b = &(++(this -> sp));

				if(a > b)
					(this -> ip) = &(++proga);
				else
					proga++;
				break;
			}
			
			case JAE_CMD:
			{
				a = &(++(this -> sp));
				b = &(++(this -> sp));
				
				if(a >= b)
					(this -> ip) = &(++proga);
				else
					proga++;
				break;
			}
			
			case JB_CMD:
			{
				a = &(++(this -> sp));
				b = &(++(this -> sp));
				
				if(a < b)
					(this -> ip) = &(++proga);
				else
					proga++;
				break;
			}
			
			case JBE_CMD:
			{
				a = &(++(this -> sp));
				b = &(++(this -> sp));
				
				if(a <= b)
					(this -> ip) = &(++proga);
				else
					proga++;
				break;
			}
			
			case JE_CMD:
			{
				a = &(++(this -> sp));
				b = &(++(this -> sp));
				
				if(a == b)
					(this -> ip) = &(++proga);
				else
					proga++;
				break;
			}
			
			case JNE_CMD:
			{
				a = &(++(this -> sp));
				b = &(++(this -> sp));
				
				if(a != b)
					(this -> ip) = &(++proga);
				else
					proga++;
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
		
		proga = this -> RAM + 1024 + ip;
	}
}

/*void virtual_cpu::in()
{
	float a = 0;
	scanf("%f", &a);
	&(this -> sp) = a;
	(this -> sp)--;
}*/

/*void virtual_cpu::out()
{
	(this -> sp)++;
	float a = &(this -> sp);
	printf("%f\n", a);
}*/

/*void virtual_cpu::mul()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	float c = a * b;
	
	&((this -> sp)--) = c;
}*/


/*void virtual_cpu::div()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	float c = a / b;
	
	&((this -> sp)--) = c;
}*/

/*void virtual_cpu::add()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	float c = a + b;
	
	&((this -> sp)--) = c;
}*/

/*void virtual_cpu::sub()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	float c = a - b;
	
	&((this -> sp)--) = c;
}*/

/*void virtual_cpu::sqrt()
{
	float a = &(++(this -> sp));	
	float c = sqrtf(a);
	
	&((this -> sp)--) = c;
}*/

/*void virtual_cpu::ja()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	if(a > b)
		(this -> ip) = &(++proga);
	else
		proga++;
}*/

/*void virtual_cpu::jae()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	if(a >= b)
		(this -> ip) = &(++proga);
	else
		proga++;
}*/

/*void virtual_cpu::jb()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	if(a < b)
		(this -> ip) = &(++proga);
	else
		proga++;
}*/

/*void virtual_cpu::jbe()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	if(a <= b)
		(this -> ip) = &(++proga);
	else
		proga++;
}*/

/*void virtual_cpu::je()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	if(a == b)
		(this -> ip) = &(++proga);
	else
		proga++;
}*/

/*void virtual_cpu::jne()
{
	float a = &(++(this -> sp));
	float b = &(++(this -> sp));
	
	if(a != b)
		(this -> ip) = &(++proga);
	else
		proga++;
}*/


/*void virtual_cpu::pop()
{
	if(this -> sp < 1024)
		(this -> sp)++;
}*/

/*void virtual_cpu::push()
{
	if(this -> sp > 0)
		(this -> sp)--;
}*/

/*void virtual_cpu::popnx(float** proga)//из стека в регистр
{
	if(&(++(&proga)) == 1)
	{
		this -> ax = &(++(this -> sp));
		return;
	}
	
	if(&(++(&proga)) == 2)
	{
		this -> bx = &(++(this -> sp));
		return;
	}
	
	if(&(++(&proga)) == 3)
	{
		this -> cx = &(++(this -> sp));
		return;
	}
	
	if(&(++(&proga)) == 4)
	{
		this -> dx = &(++(this -> sp));
		return;
	}
	
	printf("Unknown command\n");
	return;
}*/


/*void virtual_cpu::pushnx(float** proga)
{
	if(&(++(&proga)) == 1)
	{
		&((this -> sp)--) = this -> ax;
		return;
	}
	
	if(&(++(&proga)) == 2)
	{
		&((this -> sp)--) = this -> bx;
		return;
	}
	
	if(&(++(&proga)) == 3)
	{
		&((this -> sp)--) = this -> cx;
		return;
	}
	
	if(&(++(&proga)) == 4)
	{
		&((this -> sp)--) = this -> dx;
		return;
	}
	
	printf("Unknown command\n");
	return;
}*/



