void test_is_equal()
{
	bool result = false;
	result = is_equal(0.1, 0.1, 0.000001);
	if (result)
		printf("function is_equal test1 passed\n");
	else
		printf("function is_equal test1 failed\n");
		
	result = is_equal(0.2, 0.3, 0.000001);
	if (!result)
		printf("function is_equal test2 passed\n");
	else
		printf("function is_equal test2 failed\n");
		
	result = is_equal(0.1, 0.3, 1);
	if (result)
		printf("function is_equal test3 passed\n");
	else
		printf("function is_equal test3 failed\n");
		
	result = is_equal(0.25, 0.26, 0.000001);
	if (!result)
		printf("function is_equal test4 passed\n");
	else
		printf("function is_equal test4 failed\n");
}


void test_solve()
{
	int result = 0;
	float x1 = 0;
	float x2 = 0;
	result = solve(1, 2, 1, &x1, &x2);
	if (result == 1 && x1 == -1 && x2 == -1)
		printf("function solve test1 passed\n");
	else
		printf("function solve test1 failed\n");
	
	x1 = 0;
	x2 = 0;
	result = solve(0, 1, 2, &x1, &x2);
	if (result == 1 && x1 == -2 && x2 == 0)
		printf("function solve test2 passed\n");
	else
		printf("function solve test2 failed\n");
		
	x1 = 0;
	x2 = 0;
	result = solve(1, 2, -24, &x1, &x2);
	if (result == 2 && x1 == -6 && x2 == 4)
		printf("function solve test3 passed\n");
	else
		printf("function solve test3 failed\n");
		
	x1 = 0;
	x2 = 0;
	result = solve(0, 0, 0, &x1, &x2);
	if (result == SS_INF_ROOTS && x1 == 0 && x2 == 0)
		printf("function solve test4 passed\n");
	else
		printf("function solve test4 failed\n");
	
	x1 = 0;
	x2 = 0;
	result = solve(1, 1, 5, &x1, &x2);
	if (result == 0 && x1 == 0 && x2 == 0)
		printf("function solve test5 passed\n");
	else
		printf("function solve test5 failed\n");
		
	
}


void test_quequatfunction()
{
	test_is_equal();
	test_solve();
} 
