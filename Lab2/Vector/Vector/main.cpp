#include "vectorProcessor.h"

void main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	MaxMultMinDiv(numbers);
	boost::sort(numbers);
	std::copy(begin(numbers), end(numbers), std::ostream_iterator<double>(std::cout, " "));
}