#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <ctype.h>

enum comands {IN_CMD = 1, OUT_CMD, MUL_CMD, DIV_CMD, ADD_CMD, SUB_CMD,
              SQRT_CMD, POP_CMD, PUSH_CMD, POPNX_CMD, PUSHNX_CMD, SIN_CMD,
              COS_CMD, JMP_CMD, END_CMD, JA_CMD, JAE_CMD, JB_CMD, JBE_CMD,
              JE_CMD, JNE_CMD};


struct label
{
    char* title;
    int number;
};

int make_labels(label* my_labels, char* buffer, size_t sizeoffile)
{
    int number_of_label = 0;
    int j = 0;
    for(int i = 0; i < sizeoffile; i++)
    {
        if (buffer[i] = ':')
        {
           i++;
           while(buffer[i] != '\n' || buffer[i] != ' ')
           {
                (my_labels -> title)[j] = buffer[i];
                j++;
                i++;
           }
           (my_labels -> title)[j++] = buffer[i];
        }
    }
    my_labels -> number = (number_of_label)++;
    return number_of_label;
}

size_t getsize(const char* name)
{
	assert(name != NULL);
	
	FILE* file_with_onegin = fopen(name, "rd");
	
	fseek(file_with_onegin, 0, SEEK_END); //указатель на конец файла
	
	size_t sizeoffile = ftell (file_with_onegin); //разница между началом и ук.
	
	rewind (file_with_onegin); //возвращает поинтер на начало файла
	
	return sizeoffile;
}


int get_program_length(char* buffer, size_t sizeoffile)
{
    int nmb_of_cmd = 0;
   
    for(int i = 0; i < sizeoffile; i++)
    {
        if(buffer[i] == ' ' || buffer[i] == '\n')
            nmb_of_cmd++;
    }
    
    return nmb_of_cmd;
}


int read_word(char* buffer, char** cmd, int* i)
{
    int n = 0;
    int k = 0;
    while(buffer[*i] != ' ' || buffer[*i] != '\n')
    {
        (*cmd)[k] = buffer[*i];
        k++;
        *i++;
        n++;
    }
    if(n == 0)
    {
        return -1;
    }
    return 0;
    
}


size_t read_from_file(const char* name, char** buffer, size_t sizeoffile)
{
	assert(name != NULL);
	assert(buffer != NULL);
	
	*buffer = (char*) calloc(sizeof(char*), sizeoffile + 1);

	FILE* file_with_text = fopen(name, "rb");
	
	size_t readed = fread(*buffer, sizeof(char), sizeoffile, file_with_text);
	
	
	fclose(file_with_text);
	
	return readed;
}


void compilate_asm(const char* name_of_file)
{
    FILE* file_code = fopen("filewithcode", "wb");
    
    size_t sizeoffile = getsize(name_of_file);
    
    char* buffer = NULL;
    
    read_from_file(name_of_file, &buffer, sizeoffile);
    
    int nmb_of_cmd = get_program_length(buffer, sizeoffile);
    
    char* cmd = (char*) calloc(sizeof(char), 10);
    
    int* code = (int*) calloc(nmb_of_cmd, sizeof(int));
    
    
    label* my_labels = (label*) calloc(nmb_of_cmd/4, sizeof(label));
    
    int number_of_label = make_labels(my_labels, buffer, sizeoffile);

    int j = 0;
    int k = 0;
    
    for(int i = 0; i < sizeoffile; ++i)
    {
        if(!read_word(buffer, &cmd, &i))
        {
            printf("Can't read the word\n");
            return;
        }
        
        
        if (buffer[i] == ' ' || buffer[i] == '\n')
        {
            if(!strcmp(cmd, "in"))
            {
                code[j] = IN_CMD;
                ++j;
            }
            else if(!strcmp(cmd, "out"))
           {
                code[j] = OUT_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "mul"))
           {
                code[j] = MUL_CMD;
                ++j;           
           }
           else if(!strcmp(cmd, "div"))
           {
                code[j] = DIV_CMD;
                ++j;           
           }
           else if(!strcmp(cmd, "add"))
           {
                code[j] =ADD_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "sub"))
           {
                code[j] = SUB_CMD;
                ++j;           
           }
           else if(!strcmp(cmd, "sqrt"))
           {
                code[j] = SQRT_CMD;
                ++j;
           }    

           else if(!strcmp(cmd, "pop"))
           {
                if((buffer[i+2] != 'a' && buffer[i+3] != 'x' ) && 
                   (buffer[i+2] != 'b' && buffer[i+3] != 'x' ) && 
                   (buffer[i+2] != 'c' && buffer[i+3] != 'x' ) && 
                   (buffer[i+2] != 'd' && buffer[i+3] != 'x' ))
                {   
                    code[j] = POP_CMD;
                    ++j;
                }
                else
                {
                    code[j] = POPNX_CMD;
                    ++j;
                }
           }  
           else if(!strcmp(cmd, "push"))
           {
                if(!isalpha(buffer[i+2]))
                {   
                    code[j] = PUSH_CMD;
                    ++j;
                }
                else
                {
                    code[j] = PUSHNX_CMD;
                    ++j;
                }
           }
           else if(!strcmp(cmd, "ax"))
           {
                code[j] = 1;
                ++j;
           } 
           else if(!strcmp(cmd, "bx"))
           {
                code[j] = 2;
                ++j;
           } 
           else if(!strcmp(cmd, "cx"))
           {
                code[j] = 3;
                ++j;
           } 
           else if(!strcmp(cmd, "dx"))
           {
                code[j] = 4;
                ++j;
           } 
           

           else if(cmd[0] == ':')
                j++;
           
           else if(!strcmp(cmd, "sin"))
           {
                code[j] = SIN_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "cos"))
           {
                code[j] = COS_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "end"))
           {
                code[j] = END_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "jmp"))
           {
                code[j] = JMP_CMD;
                ++j;
                int m = j;
                if(!read_word(buffer, &cmd, &i))
                {
                    printf("Can't read the word\n");
                    return;
                }
                for(int n = 0; n < number_of_label; n++)
                {
                    if(!strcmp(my_labels[n].title, cmd))
                    {
                        code[j] = my_labels[n].number;
                        j++;
                        break;
                    }                  
                }
                if (m == j)
                {
                    printf("There isn't label with that title\n");
                }
                
           }
           else if(!strcmp(cmd, "ja"))
           {
                code[j] = JA_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "jae"))
           {
                code[j] = JAE_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "jb"))
           {
                code[j] = JB_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "jbe"))
           {
                code[j] = JBE_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "je"))
           {
                code[j] = JE_CMD;
                ++j;
           }
           else if(!strcmp(cmd, "jne"))
           {
                code[j] = JNE_CMD;
                ++j;
           }
           
           else if(!isalpha(cmd[0]) && cmd[0] != ':')
           {
                code[j] = atoi(cmd);
                ++j;
           }
           
           for(k == 0; k <= i; k++)
           {
                cmd[k] = 0;
           }                           
        }
    }
    for(int i = 0; i < nmb_of_cmd; ++i)
    {
        fprintf(file_code, "%d ", code[i]);
    }
    fclose(file_code);
}

    
