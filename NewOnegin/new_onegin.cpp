#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include <ctype.h>

struct MyStr
{
	int length = 0;
	char* beginning_of_string = 0;
}
;



int read_from_file(const char* name, char* buffer);
int getsize(const char* name);
int counter_of_lines(char* buffer);
MyStr* prepare_lines(char* buffer);
void write_in_file(const char* name, MyStr* lines, int nstr);
int my_strcmp(const void* l1, const void* l2);
int my_comparator(const void* l1, const void* l2);



int main(int argc, char** argv)
{
	char* buffer = 0;
	
	int readed = read_from_file(argv[argc - 2], buffer);
	
	int nstr = counter_of_lines(buffer);
	
	MyStr* lines = prepare_lines(buffer);
	
	qsort(lines -> beginning_of_string, nstr, sizeof*(lines -> beginning_of_string),
			my_strcmp);
	write_in_file(argv[argc - 1], lines, nstr);
	
	qsort(lines -> beginning_of_string, nstr, sizeof*(lines -> beginning_of_string),
			my_comparator);
	write_in_file(argv[argc - 1], lines, nstr);
}



int read_from_file(const char* name, char* buffer)
{
	int sizeoffile = getsize(name);
	buffer = (char*)calloc(sizeof (char*), sizeoffile);
	
	FILE* file_with_onegin = fopen(name, "rb");
	
	int readed = fread(buffer, sizeof(char), sizeoffile, file_with_onegin);
	
	fclose(file_with_onegin);
	
	return readed;
}



int getsize(const char* name)
{
	FILE* file_with_onegin = fopen(name, "rd");
	
	fseek(file_with_onegin, 0, SEEK_END); //указатель на конец файла
	
	size_t sizeoffile = ftell (file_with_onegin); //разница между началом и ук.
	
	rewind (file_with_onegin); //возвращает поинтер на начало файла
	
	return sizeoffile;
}


int counter_of_lines(char* buffer)
{
	int nstr = 1;
	char* timeprary = buffer;
	while(true)
	{
		timeprary = strchr(timeprary, '\n');
		if(timeprary == NULL)
			break;
		timeprary++;
		++nstr;
	}
	return nstr;
}




MyStr* prepare_lines(char* buffer)
{
	int nstr = counter_of_lines(buffer);

	MyStr* lines = (MyStr*) calloc(nstr, sizeof(MyStr));
	
	char* point = strchr(buffer, '\n');
	*point = '\0';
	lines -> beginning_of_string = buffer;
	lines -> length = point - buffer + 1;
	++lines;
	
	while (true)
	{
		point = strchr(buffer, '\n');
		
		if (point == NULL)
			break;
			
		*point = '\0';
		
		lines -> length = point - buffer + 1;
		lines -> beginning_of_string = point + 1;
		
		point++;
		++lines;	
	}
	return lines;
}



void write_in_file(const char* name, MyStr* lines, int nstr)
{
	FILE* file_with_sort_onegin = fopen(name, "wb");
	for(int i = 0; i < nstr; ++i)
	{
		if(*(lines[i].beginning_of_string) != '\0')
		{
			fprintf(file_with_sort_onegin, "%s\n", 
					lines[i].beginning_of_string);
		}
	}
	fclose(file_with_sort_onegin);
}


int my_strcmp(const void* l1, const void* l2)
{
	const char* a = *(char**) l1;
	const char* b = *(char**) l2;	
	return strcmp(a, b);
}

int my_comparator(const void* l1, const void* l2)
{
	char* line1 = *(char**) l1;
	char* line2 = *(char**) l2;
	
	char* j = line1;
	int length_line1 = 0;
	
	while(*j == '\0')
	{
		j++;
		length_line1++;
	}
	
	
	j = line2;
	int length_line2 = 0;
	 while(*j == '\0')
	 {
	 	j++;
	 	length_line2++;
	 }
	 j = 0;
	 
	 char* pointer1 = line1 + length_line1;
	 char* pointer2 = line2 + length_line2;
	 
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
	 		(pointer2 <= line2 && pointer1 > line1))
	 		return 1;
	 		
	 	if ((*pointer2 > *pointer1) || 
	 		(pointer1 <= line1 && pointer2 > line2))
	 		return -1;
	 	
	 	--pointer1;
	 	--pointer2;
	 	
	 }
	 return 0;
	 
}








