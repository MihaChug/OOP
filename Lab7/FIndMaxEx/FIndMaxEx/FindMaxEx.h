#pragma once
#include <vector>
#include <algorithm>
#include "SportsMan.h"

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const &less)
{
	if (arr.size() == 0)
	{
		return false;
	}
	auto tempMax = &arr[0];
	for (auto const &it: arr)
	{
		if (less(*tempMax, it))
		{
			tempMax = &it;
		}
	}
	maxValue = *tempMax;

	return true;
}