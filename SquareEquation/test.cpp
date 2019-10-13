#define TestFunc(test_num, a, b, disp, res) 	\
	bool result = false;			\
	result = is_equal(a, b, disp);	\
	if (result == res)				\
		printf("test %d passed: input: %g %g %g, output: %d", test_num, a, b, disp, result); \
	else	\
		printf("test");

int TestFunction()
{
	TestFunc(1, 0.02, 0.03, 0.1, 1)
	TestFunc(2, )
}
