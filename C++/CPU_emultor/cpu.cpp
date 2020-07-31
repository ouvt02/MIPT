#include "CPU.cpp"

int main()
{
	VirtualCPU proc;
	proc.open("code.txt");
	proc.execute();
	return 0;
}
