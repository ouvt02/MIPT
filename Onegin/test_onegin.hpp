#define UNITTEST_COUNT_LINES(test_number, name, length, wanted_nstr)			\
	char* buffer##test_number = 0;												\
	read_from_file(name, &buffer##test_number);									\
	size_t nstr##test_number = 0;												\
	nstr##test_number = count_lines(&buffer, length)							\
	if (wanted_nstr == nstr##test_number)										\
		printf("function count_lines test %d passed:input:%d : output:%d",      \
				test_number, wanted_nstr, nstr##test_number);					\
	else																		\
		printf("function count_lines test %d failed:input:%d : output:%d",      \
				test_number, wanted_nstr, nstr##test_number);
#define UNITTEST_WRITE_IN_FILE
#define UNITTEST_PREPARE_LINES
#define UNITTEST_COMPARE_LINES
