#include "disass.cpp"

int main()
{
	DisAsm disass;
	disass.open("code.txt", "cmds.txt");
	disass.disasemblering();
	disass.write_in_file();
	
	return 0;
}
