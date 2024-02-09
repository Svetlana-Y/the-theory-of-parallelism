#include <iostream>
#include <cmath>
#include <vector>
#define _USE_MATH_DEFINES

#ifdef FLOAT
#define TYPE float
#endif
#ifdef DOUBLE
#define TYPE double
#endif

#define getStringType(TYPE) getValueType(TYPE)
#define getValueType(TYPE) #TYPE

int main(int argc, char* argv[]) {
	
	TYPE sum = 0, value;
	std::vector<TYPE> arrayOfValueSin;

	for (int i = 0; i < 10000000; i++) {

		value = static_cast<TYPE>(std::sin((i * M_PI * 2) / 10000000));
		arrayOfValueSin.push_back(value);
		sum += value;
		
	}

	std::cout << "Result of sum " << getStringType(TYPE)<< " " << sum << std::endl;
	return 0;
}
