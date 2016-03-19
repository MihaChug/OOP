#include "vectorProcessor.h"

void MaxMultMinDiv(std::vector<double> &numbers)
{
	double max = *boost::max_element(numbers);
	double min = *boost::min_element(numbers);

	for (int i = 0; i < numbers.size(); i++)
	{
		min != 0 ? numbers[i] *= max / min : numbers[i] *= max;
	}
}