#include "ass.cpp"

int main()
{
	Assembler ass("asm_text.txt");
	ass.open_file();
	ass.compilate_asm();
	ass.write_code("code.txt");
	return 0;
}
