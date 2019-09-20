#define TESTING if(true)


#include <stdio.h>
#include <math.h>
#include <cassert>

bool is_equal(float a, float b, float diff);
int lineequat(float b, float c, float* x1);
int solve(float a, float b, float c, float* x1, float* x2);
const int SS_INF_ROOTS = -1;
#include "test_quequatfunction.hpp"
