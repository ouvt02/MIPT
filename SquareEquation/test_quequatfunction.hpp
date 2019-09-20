#define UNITTEST_IS_EQUAL(test_num, a, b, disp, wanted_res) 						\
	bool result##test_num = false;													\
	result##test_num = is_equal(a, b, disp);    									\
	if (result##test_num == wanted_res)		  										\
		printf("function is_equal test %d passed : input: %g %g %g; output: %d\n", 	\
										test_num, a, b, disp, result##test_num); 	\
	else																			\
		printf("function is_equal test %d failed : input: %g %g %g; output: %d\n", 	\
										test_num, a, b, disp, result##test_num);
				

#define UNITTEST_LINEEQUAT(test_num, b, c, wanted_x, wanted_resultat)				\
int result##test_num = 0;															\
float x##test_num = 0;																\
result##test_num = lineequat(b, c, &x##test_num);									\
if (result##test_num == wanted_resultat &&											\
	x##test_num == wanted_x)														\
	printf("function lineequat test %d passed : input:%g %g; output: %d %g\n",		\
			test_num, b, c, result##test_num, x##test_num);							\
else																				\
	printf("function lineequat test %d failed : input:%g %g; output: %d %g\n",		\
			test_num, b, c, result##test_num, x##test_num);

#define UNITTEST_SOLVE(test_num, a, b, c, wanted_result, wanted_x1, wanted_x2) 		\
	int result##test_num = 0;														\
	float x1##test_num = 0;															\
	float x2##test_num = 0;															\
	result##test_num = solve(a, b, c, &x1##test_num, &x2##test_num);				\
	if (result##test_num == wanted_result 											\
		and x1##test_num == wanted_x1 												\
		and x2##test_num == wanted_x2)												\
		printf("function solve test %d passed : input: %g %g %g; output: %d %g %g\n", 	\
										test_num, a, b, c, result##test_num, 		\
										x1##test_num, x2##test_num); 				\
	else																			\
		printf("function solve test %d failed : input: %g %g %g; output: %d %g %g\n", 	\
										test_num, a, b, c, result##test_num, 		\
										x1##test_num, x2##test_num); 				\



void test_quequatfunction()
{
	/*test_is_equal();
	test_solve();*/
	UNITTEST_IS_EQUAL(1, 0.1, 0.1, 0.00001, 1);
	UNITTEST_IS_EQUAL(2, 0.2, 0.4, 0.01, 0);
	UNITTEST_IS_EQUAL(3, 0.0001, 0.0002, 0.01, 1);
	UNITTEST_IS_EQUAL(4, 0.0001, 0.0002, 0.00001, 0);
	UNITTEST_LINEEQUAT(5, 2.0, 1.0, -0.5, 1);
	UNITTEST_LINEEQUAT(6, 6.0, 0.0, 0.0, 1);
	UNITTEST_SOLVE(7, 1.0, 2.0, 1.0, 1, -1, -1);
	UNITTEST_SOLVE(8, 1.0, 2.0, 8.0, 0, 0, 0);
	UNITTEST_SOLVE(9, 0.0, 0.0, 0.0, -1, 0, 0);
} 
