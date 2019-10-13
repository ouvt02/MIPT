#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <ctype.h>

struct MyStr
{
	int length = 0;
	char* beginning_of_string = 0;
};



size_t read_from_file(const char* name, char** buffer);
size_t getsize(const char* name);
size_t counter_of_lines(char* buffer);
MyStr* prepare_lines(char** buffer, int nstr);
void write_in_file(const char* name, MyStr* lines, int nstr, char const mode[]);
int my_strcmp(const void* l1, const void* l2);
int my_comparator(const void* l1, const void* l2);
void write_in_file(const char* name, char** buffer, int sizeoffile, 
							const char mode[]);



//! int main() 
//! sorts lines alphabetically and according to rhyme
//!
//! @Note gets text from file and writes to another sorted text




int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Usage of program: ./shakespeare [input_file] [output_file]\nAborting\n");
		return 0;
	}

	char* buffer = NULL;
	
	size_t readed = read_from_file(argv[1], &buffer);	
	
	size_t nstr = counter_of_lines(buffer);
	
	MyStr* lines = prepare_lines(&buffer, nstr);
		
	qsort(lines, nstr, sizeof(MyStr), my_strcmp);
	write_in_file(argv[2], lines, nstr, "wb");
	
	qsort(lines, nstr, sizeof(MyStr), my_comparator);
	write_in_file(argv[2], lines, nstr, "ab");
	
	write_in_file(argv[2], &buffer, readed, "ab");
}




//! int read_from_file(const char* name, char** buffer)
//! reads symbols from file to array
//!
//! @param [in] name name of file
//! @param [in] buffer poiner to the array for writing
//! @param [out] readed how many symbols are readed
//!
//! @return how many symbols are readed



size_t read_from_file(const char* name, char** buffer)
{
	assert(name != NULL);
	assert(buffer != NULL);
	
	int sizeoffile = getsize(name);//size_t
	
	*buffer = (char*) calloc(sizeof(char*), sizeoffile + 1);

	FILE* file_with_onegin = fopen(name, "rb");
	
	size_t readed = fread(*buffer, sizeof(char), sizeoffile, file_with_onegin);
	
	
	fclose(file_with_onegin);
	
	return readed;
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





//! int counter_of_lines (char** buffer)
//! counts how many lines are in the array
//!
//! @param [in] buffer pointer to the array
//! @param [out] nstr how many lines are in the array
//!
//! @return how many lines are in the array


size_t counter_of_lines(char* buffer)
{
	assert(buffer != NULL);	
	
	size_t nstr = 0;
	char* temporary = buffer;

	while(true)
	{
		temporary = strchr(temporary, '\n');
		if(temporary == nullptr)
			break;
		temporary++;
		++nstr;
	}
	
	return nstr;
}


//! MyStr* prepare_lines(char** buffer, int nstr)
//! changes "\n" for "\0"; make an array with pointers to beginnings of lines
//!
//! @param [in] buffer pointer to the array with text
//! @param [in] nstr number of lines in the array buffer
//! @param [out] lines struct with pointers to beginnings of lines and lengthes
//!
//! @return pointer to struct with pointers to beginnings of lines and lentghes


MyStr* prepare_lines(char** buffer, int nstr)
{
	assert(buffer != NULL);

	MyStr* real_lines = (MyStr*) calloc(nstr, sizeof(MyStr));
	MyStr* lines = real_lines;
	char* point = strchr(*buffer, '\n');
	*point = '\0';
	lines -> beginning_of_string = *buffer;
	lines -> length = point - *buffer + 1;
	lines++;
	char* old_point = *buffer;
	
	while (true)
	{
		old_point = point + 1;
		point = strchr(point + 1, '\n');
		
		if (point == NULL)
			break;
			
		*point = '\0';
		
		lines -> length = point - old_point + 1;
		
		lines -> beginning_of_string = old_point;
		
		lines++;	
	}

	return real_lines;
}


//! void write_in_file(const char* name, MyStr* lines, int nstr, char mode[])
//!	
//! writes something from array to file
//!
//! @param [in] name name of file for writing
//! @param [in] lines struct with pointers to beginnings of lines and lengthes
//! @param [in] nstr number of lines
//! @param [in] mode[] mode for opening file
//! 
//! return nothing 


void write_in_file(const char* name, MyStr* lines, int nstr, const char mode[])
{
	assert(name != NULL);
	assert(lines != NULL);
	
	FILE* file_with_sort_onegin = fopen(name, mode);
	
	for(int i = 0; i < nstr; ++i)
	{
		if(*(lines[i].beginning_of_string) != '\0')
		{
			fprintf(file_with_sort_onegin, "%s\n", 
					lines[i].beginning_of_string);
		}
	}
	fprintf(file_with_sort_onegin, "\n\n");
	fclose(file_with_sort_onegin);
}




void write_in_file(const char* name, char** buffer, int readed, 
							const char mode[])
{
	assert(name != NULL);
	assert(buffer != NULL);
	
	FILE* file_with_sort_onegin = fopen(name, mode);
	for(int i = 0; i < readed; ++i)
	{
		if((*buffer)[i] != '\0')
		{
			fprintf(file_with_sort_onegin, "%c", 
					(*buffer)[i]);
		}
		else
		{
			fprintf(file_with_sort_onegin, "\n");
		}
	}
	fclose(file_with_sort_onegin);
}




int my_strcmp(const void* l1, const void* l2)
{
	const char* a = ((MyStr*) l1) -> beginning_of_string;
	const char* b = ((MyStr*) l2) -> beginning_of_string;
	
	return strcmp(a, b);
}



//! int my_comparator(const void* l1, const void* l2)
//! compare two lines
//!
//! @param [in] l1 pointer to the 1st line
//! @param [in] l2 pointer to the 2nd line
//! 
//! @return 1 if the 1st line > the 2nd line
//! @return -1 if the 1st line < the 2nd line
//! @return 0 if the 1st line = the 2nd line


int my_comparator(const void* l1, const void* l2)
{
	MyStr* line1 = ((MyStr*) l1);
	MyStr* line2 = ((MyStr*) l2);

	 
	 char* pointer1 = line1 -> beginning_of_string + line1 -> length - 1;
	 char* pointer2 = line2 -> beginning_of_string + line2 -> length - 1;
	 
	 while(true)
	 {
	 	if(!isalpha(*pointer1))
	 	{
	 		--pointer1;
	 		continue;
	 	}
	 	
	 	if(!isalpha(*pointer2))
	 	{
	 		--pointer2;
	 		continue;
	 	}
	 	
	 	if ((*pointer1 == *pointer2 - 32) || 
			(*pointer1 == *pointer2 + 32))
		{
			--pointer1;
			--pointer2;
		}
	 	
	 	if ((*pointer1 > *pointer2) || 
	 		(pointer2 <= (line2 -> beginning_of_string) && pointer1 > 
	 											(line1 -> beginning_of_string)))
	 		return 1;
	 		
	 	if ((*pointer2 > *pointer1) || 
	 		(pointer1 <= (line1 -> beginning_of_string) && pointer2 > 
	 											(line2 -> beginning_of_string)))
	 		return -1;
	 	
	 	--pointer1;
	 	--pointer2;
	 	
	 }
	 return 0;
	 
}

