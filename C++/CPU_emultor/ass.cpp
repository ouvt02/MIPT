#include <stdio.h>


struct Label
{
	char* namel;
	int address;
}

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
	
	
	
	
char* program_text(const char* name_of_file)
{
	int sizeoffile = getsize(name_of_file);
	FILE* program_file = fopen(name_of_file, "rb");
	
	char* buffer = new char[sizeoffile];
	fread(buffer, sizeof(char), sizeoffile, program_file);
	
	fclose(program_file);
	
	return buffer;
}




char* read_word_buf(char* buffer, int* i)
{
	int size_of_cmd = 4;
	char* command = new char[size_of_cmd];
	
	if(buffer[*i] == ' ' or buffer[*i] == '\n')
		(*i)++;
		
	int number_of_letters = 0;
	while(buffer[*i] != ' ' and buffer[*i] != \'n')
	{
		if(number_of_letters >= size_of_cmd)
		{
			int new_size_of_cmd = size_of_cmd * 2;
			char* new_cmd = new char[new_size_of_cmd]
			for(int j = 0; j < size_of_cmd; j++)
				new_cmd[j] = cmd[j];
			delete[] cmd;
			cmd = new_cmd;
			size_of_cmd = new_size_of_cmd;
		}
		
		cmd[number_of_letters] = buffer[*i];
		number_of_letters++;
		(*i)++;
	}
	
	return cmd;
}


int get_program_length(char* buffer, int sizeoffile)
{
	int number_of_cmd = 0;
	
	for(int i = 0 i < sizeoffile; i++)
	{
		if(buffer[i] == ' ' or buffer[i] == '\n')
			number_of_cmd++;
	}
	
	return number_of_cmd;
}


int* compilate_asm(char* buffer, int sizeoffile, )
{
	int i = 0;
	char* cmd;
	int number_of_cmd = get_program_length(buffer, sizeoffile);
	int* code = new int[number_of_cmd];
	int j = 0;
	
	for(i = 0; i < sizeoffile; i++)
	{
		cmd = read_word_buf(buffer, &i);
		
		if(!strcmp(cmd, "in"))
		{
			code[j] = IN_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "out"))
		{
			code[j] = OUT_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "mul"))
		{
			code[j] = MUL_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "div"))
		{
			code[j] = DIV_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "add"))
		{
			code[j] = ADD_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "sub"))
		{
			code[j] = SUB_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "sqrt"))
		{
			code[j] = SQRT_CMD;
			j++;
		}
		
		else if(!strcmp(cmd, "pop"))
		{
			code[j] = POP_CMD;
			j++;
		}/////////////////////////////////////////////////////////////////////
	}
}













