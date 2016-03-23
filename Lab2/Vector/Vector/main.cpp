#include "vectorProcessor.h"

void main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	MaxMultMinDiv(numbers);
	boost::sort(numbers);
	for (auto i : numbers)
	{
		std::cout << std::setprecision(4) << i << ', ';
	}
}