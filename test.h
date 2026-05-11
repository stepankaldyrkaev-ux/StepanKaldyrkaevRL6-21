#ifndef _test_h_
#define _test_h_

#include <iostream>
#include <string>
#include <cstring>

void reset_global_count_test();

template<class T>
void run_test(T f, const std::string& name_func, const std::string& file_name, int num_string) {
	reset_global_count_test();
	std::cout << "-----------------------" << std::endl;
	std::cout << file_name << ":" << num_string << " -- TEST : \"" << name_func << "\"" << std::endl;
	f();
	std::cout << "-----------------------" << std::endl;
}
#define RUN_TEST(func)	run_test(func, #func, __FILE__, __LINE__)


int my_assert(bool expr_true, const std::string& expr_str, int num_test = -1);
#define ASSERT(expr_true)	my_assert(expr_true, #expr_true)
#define ASSERT_NUM_TEST(expr_true, num_test)	my_assert(expr_true, #expr_true, num_test)


template<typename T> 
void my_assert_equal(T expr_true, T expr, const std::string& expr_true_str, const std::string& expr_str, int num_test = -1) {
	if (expr_true == expr) {
		std::cout << "\tTEST " << num_test << " OK" << std::endl;
		return;
	}
	std::cout	<< "\tTEST " << num_test << " BAD {" 
				<< expr_str << " = " << expr << " not equal to " 
				<< expr_true_str << " = " << expr_true 
				<< std::endl;
}
#define ASSERT_EQUAL(expr_true, expr)	my_assert_equal(expr_true, expr, #expr_true, #expr)

#endif