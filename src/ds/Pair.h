#pragma once

template <typename firstItemType, typename secondItemType>
struct Pair
{
	firstItemType first;
	secondItemType second;

	Pair(firstItemType f, secondItemType s)
	{
		first = f;
		second = s;
	}

	void operator = (const Pair& original)
	{
		first = original.first;
		second = original.second;
	}
};
