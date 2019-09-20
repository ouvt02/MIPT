//! @file quequatfumction.cpp
//!
//! @mainpage
//!
//! - quequatfumction.cpp


#include "includ.h"

bool is_equal(float a, float b, float diff) 
{
	if (((a - b) > diff) || ((a - b) < -diff))
		return 0;
	return 1;
}

//! int lineequat(float c, float b, float* x1)
//! Solves a line equation bx + c = 0
//!
//! @param [in] b b-coefficient
//! @param [in] c c-coefficient
//!
//! @param [out] x1 Pointer to the root
//!
//! @return Number of roots
int lineequat(float b, float c, float* x1)
{
 	assert(std::isfinite(b));
    assert(std::isfinite(c));
	assert(x1 != NULL);
	int nroots = 0;
	if (b != 0)
	{
		*x1 = -c / b;
		nroots = 1;
	}
	return nroots;
}

//! int solve(float a, float b, float c, float* x1, float* x2)
//!
//! Solves a square equation ax2 + bx + c = 0
//! @param [in] a a-coefficient
//! @param [in] b b-coefficient
//! @param [in] c c-coefficient
//!
//! @param [out] x1 Pointer to the 1st root
//! @param [out] x2 Pointer to the 2nd root
//!
//! @return Number of roots
//!
//! @Note In case of infinite number of roots,
//!       returns SS_INF_ROOTS

int solve(float a, float b, float c, float* x1, float* x2)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);
    
	int SS_INF_ROOTS = -1;
	int nroots = 0;
	if (is_equal(a, 0, 0.0001) && !is_equal(b, 0, 0.0001) && 
		!is_equal(c, 0, 0.0001))
	{
		nroots = lineequat(b, c, x1);
		return nroots;
	}
	if (is_equal(a, 0, 0.0001) && is_equal(b, 0, 0.0001) && 
		is_equal(c, 0, 0.0001))
	{
		nroots = SS_INF_ROOTS;
		return SS_INF_ROOTS;
	}
	
	float D = b * b - (4 * a * c);
	if (D >= 0)
	{
		float kD = sqrt(D);
		*x1 = (-b - kD) / (2 * a);
		*x2 = (-b + kD) / (2 * a);
		if (*x1 == *x2)
			nroots = 1;
		else
			nroots = 2;
	}
	return nroots;
} 


//! int main()
//!
//! Gives solves of square equation ax2 + bx + c = 0
//!
//! @Note input: 3 numbers (can be float)
//!
//! @Note output: one/two or infinity number of solutions
//!
//! @Note In case of error breaks function
int main()
{
	TESTING test_quequatfunction();
	
	float a = 0;
	float b = 0;
	float c = 0;
	float x1 = 0;
	float x2 = 0;
	
	scanf("%g %g %g", &a, &b, &c);
	int nroots = solve(a, b, c, &x1, &x2);
	switch (nroots)
	{
		case 1: 
		{
			printf("%g", x1);
			break;
		}
		case 2:
		{	
			printf("%g %g", x1, x2);
			break;
		}
		case 0:
		{
			printf("no solves");
			break;
		}
		case SS_INF_ROOTS:
		{
			printf("Any solves");
			return SS_INF_ROOTS;
			break;
		}
		default:
		{
			printf("error, nroots = %d", nroots);
			break;
		}
	}
	return 0;
}
