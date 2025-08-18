#include <iostream>
#include <string>
#include <vector>


#define UNUSED(variable) (void)variable

// void testFunc(int i) {
// 	std::cout << "int" << std::endl;
// }

void testFunc(int& i) {
	std::cout << "int&" << std::endl;
}

void testFunc(int&& i) {
	std::cout << "int&&" << std::endl;
}


template<typename T>
void testUnirefFunc(T&& param) {
	// param
	testFunc(std::forward<T>(param));
}

int main() {

	int i = 42;

	testFunc(i);

	testUnirefFunc(i);            // int&
	testUnirefFunc(std::move(i)); // int&&

	return 0;
}