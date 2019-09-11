#include <stdio.h>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

#define DEBUG if(1) printf(">debug from %d line\n", __LINE__);


size_t getsize(const char* name);
int read_from_file(const char* name, char** buffer);
void write_in_file(const char* name1, char** lines, size_t nstr);
size_t count_lines(char* buffer, size_t length);
char** prepare_lines(char* buffer, size_t nstr,size_t length);
int my_strcmp(const void* a, const void* b);
int compares_lines(const void* line1, const void* line2);


//! int main() 
//! sorts lines alphabetically and according to rhyme
//!
//! @Note gets text from file and writes to another sorted text


int main()
{
	char* buffer = 0;

	size_t readed = read_from_file("onegin.txt", &buffer);

	size_t nstr = count_lines(buffer, readed);

	char** lines = prepare_lines(buffer, nstr, readed);
	
	qsort(lines, nstr, sizeof(*lines), my_strcmp);
	write_in_file("onegin1.txt", lines, nstr);

	qsort(lines, nstr, sizeof(*lines), compares_lines);
	write_in_file("onegin2.txt", lines, nstr);
	
	return 0;
	
}



void unittest_qsort1()
{
	lines[]
}

//! int read_from_file(const char* name, char** buffer)
//! reads symbols from file to array
//!
//! @param [in] name name of file
//! @param [in] buffer poiner to the array for writing
//! @param [out] readed how many symbols are readed
//!
//! @return how many symbols are readed


int read_from_file(const char* name, char** buffer)
{
	assert(name != NULL);
	assert(buffer != NULL);
	
	size_t sizeoffile = getsize(name);
	*buffer = (char*) calloc(sizeof(char), sizeoffile);
	FILE* file = fopen("onegin.txt", "rb");
	int readed = fread(*buffer, sizeof(char), sizeoffile, file);
	fclose(file);
	
	return readed;
}


//! size_t count_lines (char* buffer, size_t length)
//! counts how many lines are in the array
//!
//! @param [in] buffer pointer to the array
//! @param [in] length length of the array
//! @param [out] nstr how many lines are in the array
//!
//! @return how many lines are in the array



size_t count_lines (char* buffer, size_t length)
{
	assert(buffer != NULL);	
	
	size_t nstr = 1;
	for (int i = 0; i < length; ++i)
	{
		if (buffer[i] == '\n')
		{
			nstr++;
			buffer[i] = '\0';
		}
	}
	
	return nstr;
}



//! char** prepare_lines(char* buffer, size_t nstr, size_t length)
//! changes "\n" for "\0"; make an array with pointers to beginnings of lines
//!
//! @param [in] buffer pointer to the array with text
//! @param [in] nstr number of lines in the array buffer
//! @param [in] length length of the array buffer
//! @param [out] lines array with pointers to beginnings of lines
//!
//! @return array with pointers to beginnings of lines



char** prepare_lines(char* buffer, size_t nstr, size_t length)
{
	assert(buffer != NULL);
	
	if ((nstr == 0) || (length == 0))
		return 0;
	
	char** lines = (char**) calloc(sizeof(char*), nstr);
	
	int j = 1;
	int nsym = 0;
	lines[0] = nsym + buffer;
	
	for (nsym = 1; nsym < length; nsym++)
	{
		if (buffer[nsym] == '\0')
		{
			lines[j] = nsym + buffer + 1;
			++j;
		}
	}
	
	return lines;
}


//! void write_in_file(const char* name1,const char* name, 	
//!										char** lines, size_t nstr)	
//! writes something from array to file
//!
//! @param [in] name1 name of file for writing
//! @param [in] lines array with pointers to beginnings of lines
//! @param [in] nstr number of lines
//! 
//! return nothing 




void write_in_file(const char* name1, char** lines, size_t nstr)	
{
	assert(name1 != NULL);
	assert(lines != NULL);
	
	FILE* file = fopen(name1, "w");
	assert(file != NULL);
	
	for (int i = 0; i < nstr; i++)
	{
		if (*(lines[i]) != '\0')
			fprintf(file, "%s\n", lines[i]);
	}
	fclose(file);
}


//! size_t getsize(const char* name)
//! finds size of file
//!
//! @param [in] name name of file
//! @param [out] sizeoffile size of file
//!
//! @return size of file



size_t getsize(const char* name)
{
	assert(name != NULL);
	
	FILE* file = fopen(name, "rb");
	assert(file != NULL);
	
	fseek (file, 0, SEEK_END); // поинтер на конец файла
    size_t sizeoffile = ftell (file); // разница между началом и поинтером
    rewind (file); // возвращает поинтер на начало файла
    
    fclose(file);
    
    return sizeoffile;
}


int my_strcmp(const void* a, const void* b)
{	
	const char* l1 = *(char **) a;
	const char* l2 = *(char **) b;
		
	return strcmp(l1, l2);
}


//! int compares_lines(const void* line1, const void* line2)
//! compare two lines
//!
//! @param [in] line1 pointer to the 1st line
//! @param [in] line2 pointer to the 2nd line
//! 
//! @return 1 if the 1st line > the 2nd line
//! @return -1 if the 1st line < the 2nd line
//! @return 0 if the 1st line = the 2nd line


int compares_lines(const void* line1, const void* line2)
{
	const char* l1 = *(char**) line1;
	const char* l2 = *(char**) line2;
	
	int lengthl1 = 0;
	const char* j = l1;
	for (;*j != '\0'; j++)// while(true) for(;;)
	{
		++lengthl1;
	}

	int lengthl2 = 0;
	j = l2;
	for (; *j != '\0'; j++)
	{
		++lengthl2;
	}
	
	const char* pointer2 = lengthl2 + l2;
	const char* pointer1 = lengthl1 + l1;
	while(pointer1 >= l1 && pointer2 >= l2)
	{
		if (!isalpha(*(pointer1)))
		{
			--pointer1;
			continue;
		}
		
		if (!isalpha(*(pointer2)))
		{
			--pointer2;
			continue;
		}
		
		if ((*(pointer1) == *(pointer2) - 32) || 
										(*(pointer1) == *(pointer2) + 32))
		{
			--pointer1;
			--pointer2;
		}
		
		if ((*(pointer1) > *(pointer2)) || ((pointer1 >= l1) && 
															(pointer2 < l2)))
			return 1;
		if ((*(pointer1) < *(pointer2)) || ((pointer1 == l1) && 
															(pointer2 > l2)))
			return -1;
			
		--pointer1;	 
		--pointer2;
	}
	return 0;
	
}

