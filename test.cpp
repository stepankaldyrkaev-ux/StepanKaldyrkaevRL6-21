#include "test.h"

static int count_test = 1;

void reset_global_count_test() {
	count_test = 1;
}

int my_assert(bool expr_true, const std::string& expr_str, int num_test) {
	int cur_test =  num_test;
	if (num_test < 0) {
		cur_test = count_test;
		count_test++;
	}

	if (expr_true == true) {
		std::cout << "\tTEST " << cur_test++ << " OK" << std::endl;
		return 0;
	}

	std::cout << "\tTEST " << cur_test++ << " BAD {" << expr_str << "}" << std::endl;

	return 1;
}