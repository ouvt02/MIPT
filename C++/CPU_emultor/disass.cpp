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

class DisAsm
{


  public:
  
	class label
	{

		friend DisAsm;
		
	  protected:
		char* name = nullptr;
		int address = 0;
		
	  public:
	  	label();
	  	~label();
	};

  private:
  
  	label* my_labels = nullptr;
  	char* code_name = nullptr;
  	char* cmds_name = nullptr;
  	int number_of_cmd = 0;
  	int number_of_labels = 0;
  	float* code = nullptr;
  	char** commands = nullptr;
  	int size_of_code_file = 0;
  	
  	
  	enum Commands
	{
		IN_CMD = 1,
		OUT_CMD = 2,
		MUL_CMD = 3,
		DIV_CMD = 4,
		ADD_CMD = 5,
		SUB_CMD = 6,
		SQRT_CMD = 7,
		POP_CMD = 8,
		PUSH_CMD = 9,
		POPNX_CMD = 10,
		PUSHNX_CMD = 11,
		SIN_CMD = 12,
		COS_CMD = 13,
		JMP_CMD = 14,
		JA_CMD = 15,
		JAE_CMD = 16,
		JB_CMD = 17,
		JBE_CMD = 18,
		JE_CMD = 19,
		JNE_CMD = 20,
		CALL_CMD = 21,
		RET_CMD = 22,
		END_CMD = 23
	};
  	
  	
  public:
  	DisAsm();
  	~DisAsm();
  	void open(const char* name_file_code, const char* name_file_cmd);
  	void get_program_length(char* buffer);
  	void get_number_of_labels();
  	void get_position_of_lables();
  	const char* coinsidence_of_label_addresses(int pointer);
  	void disasemblering();
  	void write_in_file();
};

DisAsm::label::label()
{}


DisAsm::label::~label()
{
	if(this -> name != nullptr)
		delete[] this -> name;
}


DisAsm::DisAsm()
{}

DisAsm::~DisAsm()
{
	if(this -> code != NULL)
		delete[] this -> code;
		
	if(this -> commands != NULL)
		delete[] this -> commands;
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


void DisAsm::open(const char* name_file_code, const char* name_file_cmd)
{	
	this -> code_name = new char[strlen(name_file_code) + 1]{0};
	strcpy(this -> code_name, name_file_code);
	
	this -> cmds_name = new char[strlen(name_file_cmd) + 1]{0};
	strcpy(this -> cmds_name, name_file_cmd);
	
	this -> size_of_code_file = getsize(this -> code_name);
	char* buffer = new char[this -> size_of_code_file];
	FILE* file_code = fopen(this -> code_name, "rb");
	fread(buffer, sizeof(char), this -> size_of_code_file, file_code);
	fclose(file_code);
	
	get_program_length(buffer);	
	this -> code = new float[this -> number_of_cmd];
	int cmd_counter = 0;
	for(int i = 0; i < this -> size_of_code_file; i++)
	{
		char* cmd = read_word_buf(buffer, &i);
		(this -> code)[cmd_counter] = atof(cmd);
		cmd_counter++;
	}
}

void DisAsm::get_program_length(char* buffer)
{
	this -> number_of_cmd = 0;
	
	for(int i = 0; i < this -> size_of_code_file; i++)
	{
		if(buffer[i] == ' ')
			(this -> number_of_cmd)++;
	}
}


void DisAsm::get_number_of_labels()
{
	for(int i = 0; i < this -> number_of_cmd; i++)
	{		
		if((this -> code)[i] == JMP_CMD or (this -> code)[i] == JA_CMD 
			or (this -> code)[i] == JAE_CMD or (this -> code)[i] == JB_CMD or
			(this -> code)[i] == JBE_CMD or (this -> code)[i] == JNE_CMD or
			(this -> code)[i] == JE_CMD or (this -> code)[i] == CALL_CMD)
			(this -> number_of_labels)++;
	}
}

void DisAsm::get_position_of_lables()
{
	this -> my_labels = new label[this -> number_of_labels];
	int label_counter = 0;
	for(int i = 0; i < this -> number_of_cmd; i++)
	{		
		if((this -> code)[i] == JMP_CMD or (this -> code)[i] == JA_CMD 
			or (this -> code)[i] == JAE_CMD or (this -> code)[i] == JB_CMD or
			(this -> code)[i] == JBE_CMD or (this -> code)[i] == JNE_CMD or
			(this -> code)[i] == JE_CMD or (this -> code)[i] == CALL_CMD)
		{
			(this -> my_labels)[label_counter].address = (this -> code)[++i];
			(this -> my_labels)[label_counter].name = new char[8];
			sprintf((this -> my_labels)[label_counter].name, ":label%d", label_counter);
			label_counter++;
		}
	}
}

const char* DisAsm::coinsidence_of_label_addresses(int pointer)
{
	char* finded_name = nullptr;
	for(int i = 0; i < this -> number_of_labels; i++)
	{	
		if(pointer == (this -> my_labels)[i].address)
			finded_name = (this -> my_labels)[i].name;
	}

	return (const char*)finded_name;
}


void DisAsm::write_in_file()
{

	FILE* proga_file = fopen(this -> cmds_name, "wb");
	
	for(int i = 0; i < (this -> number_of_cmd) + this -> number_of_labels; i++)
	{
		if(!strcmp((this -> commands)[i], "jmp") or !strcmp((this -> commands)[i], "ja") or
			!strcmp((this -> commands)[i], "jae") or !strcmp((this -> commands)[i], "jb") or
			!strcmp((this -> commands)[i], "jbe") or !strcmp((this -> commands)[i], "jne") or
			!strcmp((this -> commands)[i], "je") or !strcmp((this -> commands)[i], "call") or
			!strcmp((this -> commands)[i], "push"))
			fprintf(proga_file, "%s ", (this -> commands)[i]);
			
		else
			fprintf(proga_file, "%s\n", (this -> commands)[i]);
	}
		
	fclose(proga_file);
}

void DisAsm::disasemblering()
{
	get_number_of_labels();	
	get_position_of_lables();
	
	char temporary_array[20] = {};//for CHARing numbers
	int counter = 0;
	
	this -> commands = new char*[(this -> number_of_cmd) + this -> number_of_labels];
	int counter_commands = 0;
	int counter_code = 0;
	
	for(counter_commands = 0; counter_commands < (this -> number_of_cmd) + this -> number_of_labels; )
	{
		const char* coinsidence_name = coinsidence_of_label_addresses(counter_code);
		if(coinsidence_name != nullptr)
		{
			(this -> commands)[counter_commands]= new char[8];
			strcpy((this -> commands)[counter_commands], coinsidence_name);
			counter_commands++;
			
		}
		
		if((this -> code)[counter_code] == IN_CMD)
		{
			(this -> commands)[counter_commands] = new char[3];
			strcpy((this -> commands)[counter_commands], "in");
			counter_code++;
			counter_commands++;
		}

		else if((this -> code)[counter_code] == OUT_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "out");
			counter_code++;
			counter_commands++;
		}
		
		else if((this -> code)[counter_code] == MUL_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "mul");
			counter_commands++;
			counter_code++;
		}
		
		else if((this -> code)[counter_code] == DIV_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "div");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == ADD_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "add");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == SUB_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "sub");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == SQRT_CMD)
		{
			(this -> commands)[counter_commands] = new char[5];
			strcpy((this -> commands)[counter_commands], "sqrt");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == POP_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "pop");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == PUSH_CMD)
		{
			(this -> commands)[counter_commands] = new char[5];
			strcpy((this -> commands)[counter_commands], "push");
			counter_code++;
			counter_commands++;;
			
			
			sprintf(temporary_array, "%g", (this -> code)[counter_code]);
			counter = 0;
			while(temporary_array[counter] != '\0')
				counter++;
			(this -> commands)[counter_commands]  = new char[counter + 1];
			strcpy((this -> commands)[counter_commands], temporary_array);
			
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == POPNX_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "popnx");
			counter_code++;
			counter_commands++;;
			
			if((this -> code)[counter_code] == 1)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "ax");
				counter_code++;
				counter_commands++;;
			}
			
			if((this -> code)[counter_code] == 2)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "bx");
				counter_code++;
				counter_commands++;;
			}
			
			if((this -> code)[counter_code] == 3)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "cx");
				counter_code++;
				counter_commands++;;
			}
			
			if((this -> code)[counter_code] == 4)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "dx");
				counter_code++;
				counter_commands++;;
			}
		}
		
		else if((this -> code)[counter_code] == PUSHNX_CMD)
		{
			(this -> commands)[counter_commands] = new char[5];
			strcpy((this -> commands)[counter_commands], "push");
			counter_code++;
			counter_commands++;;
			
			if((this -> code)[counter_code] == 1)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "ax");
				counter_code++;
				counter_commands++;;
			}
			
			if((this -> code)[counter_code] == 2)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "bx");
				counter_code++;
				counter_commands++;;
			}
			
			if((this -> code)[counter_code] == 3)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "cx");
				counter_code++;
				counter_commands++;;
			}
			
			if((this -> code)[counter_code] == 4)
			{
				(this -> commands)[counter_commands] = new char[3];
				strcpy((this -> commands)[counter_commands], "dx");
				counter_code++;
				counter_commands++;;
			}
		}
		
		else if((this -> code)[counter_code] == SIN_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "sin");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == COS_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "cos");
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JMP_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "jmp");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JA_CMD)
		{
			(this -> commands)[counter_commands] = new char[3];
			strcpy((this -> commands)[counter_commands], "ja");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JAE_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "jae");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JB_CMD)
		{
			(this -> commands)[counter_commands] = new char[3];
			strcpy((this -> commands)[counter_commands], "jb");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JBE_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "jbe");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JE_CMD)
		{
			(this -> commands)[counter_commands] = new char[3];
			strcpy((this -> commands)[counter_commands], "je");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == JNE_CMD)
		{
			(this -> commands)[counter_commands] = new char[4];
			strcpy((this -> commands)[counter_commands], "jne");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else if((this -> code)[counter_code] == CALL_CMD)
		{
			(this -> commands)[counter_commands] = new char[5];
			strcpy((this -> commands)[counter_commands], "call");
			counter_code++;
			counter_commands++;;
			
			(this -> commands)[counter_commands] = new char[7];
			coinsidence_name = coinsidence_of_label_addresses((int)((this -> code)[counter_code]));
			strcpy((this -> commands)[counter_commands], coinsidence_name + 1);
			counter_code++;
			counter_commands++;;
		}
		
		else
			printf("Unknown command\n");
	}
	
}

















