#include <stdio.h>
#include <math.h>
#include <cstring>


class VirtualCPU
{
  private:

	float ax = 0;
	float bx = 0;
	float cx = 0;
	float dx = 0;
	int ip = 0;
	float* sp = nullptr;
	
	float* RAM = nullptr;
	float* proga = nullptr;
	int proga_size = 0;
	char* file_proga_name = nullptr;
	int size_of_proga_file = 0;
	
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
		CALL_CMD,
		RET_CMD,
		END_CMD
	};
	
	VirtualCPU();
	~VirtualCPU();
	
	void open(const char* proga_name);
	void execute();
	void get_program_length(char* buffer);
};


int getsize(const char* name)
{
	FILE* file_proga = fopen(name, "rd");
	
	fseek(file_proga, 0, SEEK_END); //указатель на конец файла
	
	size_t sizeoffile = ftell (file_proga); //разница между началом и ук.
	
	rewind (file_proga); //возвращает поинтер на начало файла
	
	return sizeoffile;
}

char* read_word_buf(char* buffer, int* i)
{
	int size_of_cmd = 4;
	char* command = new char[size_of_cmd];
	
	if(buffer[*i] == ' ' or buffer[*i] == '\n')
		(*i)++;
		
	int number_of_letters = 0;
	while(buffer[*i] != ' ' and buffer[*i] != '\n')
	{
		if(number_of_letters >= size_of_cmd)
		{
			int new_size_of_cmd = size_of_cmd * 2;
			char* new_cmd = new char[new_size_of_cmd];
			for(int j = 0; j < size_of_cmd; j++)
				new_cmd[j] = command[j];
			delete[] command;
			command = new_cmd;
			size_of_cmd = new_size_of_cmd;
		}
		
		command[number_of_letters] = buffer[*i];
		number_of_letters++;
		(*i)++;
	}
	
	return command;
}



void VirtualCPU::get_program_length(char* buffer)
{
	this -> proga_size = 0;
	
	for(int i = 0; i < this -> size_of_proga_file; i++)
	{
		if(buffer[i] == ' ')
			(this -> proga_size)++;
	}
}


VirtualCPU::VirtualCPU()
{}


VirtualCPU::~VirtualCPU()
{
	if(this -> RAM != nullptr)
		delete[] this -> RAM;
}


void VirtualCPU::open(const char* proga_name)
{
	this -> file_proga_name = new char[strlen(proga_name) + 1]{0};
	strcpy(this -> file_proga_name, proga_name);
	
	this -> size_of_proga_file = getsize(this -> file_proga_name);
	
	FILE* file_proga = fopen(this -> file_proga_name, "rb");
	
	char* buffer = new char[this -> size_of_proga_file];
	fread(buffer, sizeof(char), this -> size_of_proga_file, file_proga);
	
	fclose(file_proga);	
	
	get_program_length(buffer);
	this -> RAM = new float[1024 + this -> proga_size];
	
	this -> proga = this -> RAM + 1024;
	this -> sp = this -> RAM + 1023;
	
	for(int i = 0; i < this -> size_of_proga_file; i++)
	{
		char* cmd = read_word_buf(buffer, &i);
		*(this -> proga) = atof(cmd);
		(this  -> proga)++;
	}
	
	this -> proga = this -> RAM + 1024;
}

void VirtualCPU::execute()
{

	float a = 0;
	float b = 0;
	float c = 0;
	
	
	for(this -> ip = 0; this -> ip < this -> proga_size; )
	{	
		switch((int)((this -> proga)[this -> ip]))
		{
			case IN_CMD:
			{
				scanf("%f", &a);
				*((this -> sp)--) = a;
				(this -> ip)++;
				break;
			}
			
			case OUT_CMD:
			{
				a = *(++(this -> sp));
				printf("%g\n", a);
				(this -> ip)++;
				break;
			}
			
			case MUL_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				c = a * b;
				
				*((this -> sp)--) = c;
				(this -> ip)++;
				break;
			}
			
			case DIV_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				c = a / b;
				
				*((this -> sp)--) = c;
				(this -> ip)++;
				break;
			}
			
			case ADD_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				c = a + b;
				
				*((this -> sp)--) = c;
				(this -> ip)++;
				break;
			}
			
			case SUB_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				c = a - b;
				
				*((this -> sp)--) = c;
				(this -> ip)++;
				break;
			}
			
			case SQRT_CMD:
			{
				a = *(++(this -> sp));	
				b = sqrtf(a);
				
				*((this -> sp)--) = b;
				(this -> ip)++;
				break;
			}
			
			case POP_CMD:
			{
				//if(this -> sp < this -> RAM + 1023)
				(this -> sp)++;
				(this -> ip)++;
				break;
			}
			
			case PUSH_CMD:
			{
				//if(this -> sp > 0)
				*(this -> sp) = ((this -> proga)[++(this -> ip)]);
				(this -> sp)--;
				(this -> ip)++;
				break;
			}
			
			case POPNX_CMD:
			{
				if((this -> RAM)[++(this -> ip)] == 1)
					this -> ax = *(++(this -> sp));

				else if((this -> RAM)[++(this -> ip)] == 2)
					this -> bx = *(++(this -> sp));

				else if((this -> RAM)[++(this -> ip)] == 3)
					this -> cx = *(++(this -> sp));

				else if((this -> RAM)[++(this -> ip)] == 4)
					this -> dx = *(++(this -> sp));
				
				else
					printf("Unknown command\n");

				(this -> ip)++;
				break;
			}
			
			case PUSHNX_CMD:
			{
				if((this -> RAM)[++(this -> ip)] == 1)
					*((this -> sp)--) = this -> ax;
				
				else if((this -> RAM)[++(this -> ip)] == 2)
					*((this -> sp)--) = this -> bx;

				else if((this -> RAM)[++(this -> ip)] == 3)
					*((this -> sp)--) = this -> cx;

				else if((this -> RAM)[++(this -> ip)] == 4)
					*((this -> sp)--) = this -> dx;
				
				else
					printf("Unknown command\n");

				(this -> ip)++;
				break;
			}
			
			case SIN_CMD:
			{
				a = *(++(this -> sp));
				b = sin(a);
				*((this -> sp)--) = b;
				(this -> ip)++;
				break;
			}
			
			case COS_CMD:
			{
				a = *(++(this -> sp));
				b = cos(a);
				*((this -> sp)--) = b;
				(this -> ip)++;
				break;
			}
			
			case JMP_CMD:
			{
				this -> ip = (this -> proga)[++(this -> ip)];
				break;
			}
			
			case JA_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));

				if(a > b)
					(this -> ip) = (this -> proga)[++(this -> ip)];
				else
					++(this -> ip);
				break;
			}
			
			case JAE_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				if(a >= b)
					(this -> ip) = (this -> proga)[++(this -> ip)];
				else
					++(this -> ip);
				break;
			}
			
			case JB_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				if(a < b)
					(this -> ip) = (this -> proga)[++(this -> ip)];
				else
					++(this -> ip);
				break;
			}
			
			case JBE_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				if(a <= b)
					(this -> ip) = (this -> proga)[++(this -> ip)];
				else
					++(this -> ip);
				break;
			}
			
			case JE_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				if(a == b)
					(this -> ip) = (this -> proga)[++(this -> ip)];
				else
					++(this -> ip);
				break;
			}
			
			case JNE_CMD:
			{
				a = *(++(this -> sp));
				b = *(++(this -> sp));
				
				if(a != b)
					(this -> ip) = (this -> proga)[++(this -> ip)];
				else
					++(this -> ip);
				break;
			}
			
			case CALL_CMD:
			{
				*((this -> sp)--) = (this -> ip);
				this -> ip = (this -> proga)[++(this -> ip)];
				break;				
			}
			
			case RET_CMD:
			{
				this -> ip = *(++(this -> sp));
				break;
			}
			
			case END_CMD:
			{
				(this -> ip)++;
				break;
			}
			
			default:
			{
				printf("Unknown command\n");
				break;
			}
		}
	}
	
}


























