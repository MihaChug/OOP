#include "vectorProcessor.h"

void MaxMultMinDiv(std::vector<double> &numbers)
{
	if (!numbers.empty())
	{
		double max = *boost::max_element(numbers);
		double min = *boost::min_element(numbers);
		for (auto &i : numbers)
		{
			min != 0 ? i *= max / min : i *= max;
		}
	}
}