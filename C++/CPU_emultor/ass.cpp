#include <cstdio>
#include <cstring>
#include <cstdlib>

#ifndef RELEASE
	#define DEBUG printf("\x1b[35m>> debug from <%s::%d>\n\x1b[0m", __FILE__, __LINE__);
#else
	#define DEBUG
#endif


int getsize(const char* name);
char* read_word_buf(char* buffer, int* i);



class Assembler
{

  public:
  
	class label
	{

		friend Assembler;
		
	  protected:
		char* name = nullptr;
		int address = 0;
		
	  public:
	  	label();
	  	~label();
	};

  private:
  
  	label* my_labels = nullptr;
  	int number_of_labels = 0;
  	float* code = nullptr;
  	int number_of_cmd = 0;
  	
  	char* name_of_file = nullptr;
  	char* code_name = nullptr;
  	int sizeoffile = 0;
  	char* text_of_program = nullptr;
  	
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
	};
	
  public:
  	
  	Assembler(const char* file_name);
  	~Assembler();
  	void get_program_length();
  	void make_labels();
  	int find_adr_lbl(int* i);
  	void compilate_asm();
  	void write_code(const char* code_file_name);
  	void open_file();
  	int get_nmb_of_labels();
};


Assembler::label::label()
{}


Assembler::label::~label()
{
	if(this -> name != nullptr)
		delete[] this -> name;
}

	
Assembler::Assembler(const char* file_name)
{
	this -> name_of_file = new char[strlen(file_name) + 1]{0};
	strcpy(this -> name_of_file, file_name);
}



Assembler::~Assembler()
{
	if(this -> name_of_file != NULL)
		delete[] this -> name_of_file;
		
	if(this -> text_of_program != NULL)
		delete[] this -> text_of_program;	
	
	if(this -> code != NULL)
		delete[] this -> code;
	
}


void Assembler::open_file()
{
	FILE* program_file = fopen(this -> name_of_file, "rb");
	
	this -> sizeoffile = getsize(this -> name_of_file);
	this -> text_of_program = new char[this -> sizeoffile];
	fread(text_of_program, sizeof(char), this -> sizeoffile, program_file);
	
	fclose(program_file);
}

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


void Assembler::get_program_length()
{
	this -> number_of_cmd = 0;
	
	for(int i = 0; i < this -> sizeoffile; i++)
	{
		if((this -> text_of_program)[i] == ' ' or 
										(this -> text_of_program)[i] == '\n')
			(this -> number_of_cmd)++;
	}
}


void Assembler::make_labels()
{
	this -> number_of_labels = get_nmb_of_labels();
	char* data_title;
	
	int position = 0;
	int counter_of_labels = 0;
	
	this -> my_labels = new label[this -> number_of_labels];
	
	for(int i = 0; i < this -> sizeoffile; i++)
	{
		if((this -> text_of_program)[i] == ' ' or 
										(this -> text_of_program)[i] == '\n')
		{
			i++;
			position++;
		}
		
		if((this -> text_of_program)[i] == ':')
		{	
			i++;
			position--;

			data_title = read_word_buf(text_of_program, &i);
			
			(this -> my_labels)[counter_of_labels].name = new char[strlen(data_title) + 1]{0};	
					
			strcpy((this -> my_labels)[counter_of_labels].name, data_title);
			(this -> my_labels)[counter_of_labels].address = ++position;
			
			counter_of_labels++;
			
		}
	}
}


int Assembler::find_adr_lbl(int* i)
{
	char* name_of_label = read_word_buf(this -> text_of_program, i);
	int adr_lbl = 0;
	
	int j = 0;
	
	for(int k = 0; k < this -> number_of_labels; k++)
	{		
		if(!strcmp(name_of_label, (this -> my_labels)[k].name))
		{
			adr_lbl = (this -> my_labels)[k].address;
			j++;
			break;
		}
	}
	
	if(j == 0)
	{
		adr_lbl = -1;
		printf("there is no matching label for %s\n", name_of_label);
	}
	
	return adr_lbl;
}

int Assembler::get_nmb_of_labels()
{
	int number_of_labels = 0;
	for(int i = 0; i < this -> sizeoffile; i++)
	{
		if((this -> text_of_program)[i] == ':')
		{
			(this -> number_of_cmd)--;
			number_of_labels++;
		}
	}
	return number_of_labels;
}



void Assembler::compilate_asm()
{
	int i = 0;
	char* cmd;
	get_program_length();
															
	char* new_cmd;
	this -> code = new float[this -> number_of_cmd]{0};
	int j = 0;
	char* next_word;
	
	make_labels();
	
	for(i = 0; i < this -> sizeoffile; i++)
	{
		cmd = read_word_buf(this -> text_of_program, &i);
		
		if(!strcmp(cmd, "in"))
		{
			(this -> code)[j] = IN_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "out"))
		{
			(this -> code)[j] = OUT_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "mul"))
		{
			(this -> code)[j] = MUL_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "div"))
		{
			(this -> code)[j] = DIV_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "add"))
		{
			(this -> code)[j] = ADD_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "sub"))
		{
			(this -> code)[j] = SUB_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "sqrt"))
		{
			(this -> code)[j] = SQRT_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "pop"))
		{
			new_cmd = read_word_buf(this -> text_of_program, &i);
			
			if(!strcmp(new_cmd, "ax"))
			{
				(this -> code)[j] = POPNX_CMD;
				(this -> code)[++j] = 1;
			}
			
			else if(!strcmp(new_cmd, "bx"))
			{
				(this -> code)[j] = POPNX_CMD;
				(this -> code)[++j] = 2;
			}
			
			else if(!strcmp(new_cmd, "cx"))
			{
				(this -> code)[j] = POPNX_CMD;
				(this -> code)[++j] = 3;
			}
			
			else if(!strcmp(new_cmd, "dx"))
			{
				(this -> code)[j] = POPNX_CMD;
				(this -> code)[++j] = 4;
			}
			
			else
			{
				(this -> code)[j] = POP_CMD;
				(this -> code)[++j] = atoi(new_cmd);
			}
				
			j++;
		}
		
		else if(!strcmp(cmd, "push"))
		{
			new_cmd = read_word_buf(this -> text_of_program, &i);
			
			if(!strcmp(new_cmd, "ax"))
			{
				(this -> code)[j] = PUSHNX_CMD;
				(this -> code)[++j] = 1;
			}
			
			else if(!strcmp(new_cmd, "bx"))
			{
				(this -> code)[j] = PUSHNX_CMD;
				(this -> code)[++j] = 2;
			}
			
			else if(!strcmp(new_cmd, "cx"))
			{
				(this -> code)[j] = PUSHNX_CMD;
				(this -> code)[++j] = 3;
			}
			
			else if(!strcmp(new_cmd, "dx"))
			{
				(this -> code)[j] = PUSHNX_CMD;
				(this -> code)[++j] = 4;
			}
			
			else
			{
				(this -> code)[j] = PUSH_CMD;
				(this -> code)[++j] = atoi(new_cmd);
			}
				
			j++;
		}
		
		else if(!strcmp(cmd, "sin"))
		{
			(this -> code)[j] = SIN_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "cos"))
		{
			(this -> code)[j] = COS_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "jmp"))
		{
			(this -> code)[j] = JMP_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(!strcmp(cmd, "ja"))
		{
			(this -> code)[j] = JA_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(!strcmp(cmd, "jae"))
		{
			(this -> code)[j] = JAE_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(!strcmp(cmd, "jb"))
		{
			(this -> code)[j] = JB_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(!strcmp(cmd, "jbe"))
		{
			(this -> code)[j] = JBE_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(!strcmp(cmd, "jn"))
		{
			(this -> code)[j] = JE_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(!strcmp(cmd, "jne"))
		{
			(this -> code)[j] = JNE_CMD;
			(this -> code)[++j] = find_adr_lbl(&i);
			j++;
		}
		
		else if(cmd[0] == ':')
			continue;
		
		else
			printf("unknown command\n");
	}
}

void Assembler::write_code(const char* code_file_name)
{
	this -> code_name = new char[strlen(code_file_name) + 1]{0};
	strcpy(this -> code_name, code_file_name);
	
	FILE* file_write_code = fopen(this -> code_name, "wb");
	
	for(int k = 0; k < this -> number_of_cmd; k++)
		fprintf(file_write_code, "%g ", (this -> code)[k]);
	fprintf(file_write_code, "\n");
	
	fclose(file_write_code);
}











