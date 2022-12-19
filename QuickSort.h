#include <iostream>

#define OPTIMAL_SIZE 42


// Get pivot

template<typename T, typename Compare>
T Pivot(T* first, T* last, Compare comp)
{
	T* mid = first + (last - first) / 2;
	if ((comp(*first, *mid) && comp(*last, *first)) || (comp(*first, *last) && comp(*mid, *first)))
		return *first;
	else if ((comp(*mid, *first) && comp(*last, *mid)) || (comp(*mid, *last) && comp(*first, *mid)))
		return *mid;
	else
		return *last;
}


// Quicksort

template<typename T, typename Compare>
void QuickSort(T* first, T* last, Compare comp)
{
	while (first < last)
	{
		T pivot = Pivot(first, last, comp);
		T* f = first;
		T* l = last;

		while (f <= l)
		{
			while (comp(*f, pivot))
				++f;

			while (comp(pivot, *l))
				--l;

			if (f <= l)
			{
				std::swap(*f, *l);
				++f;
				--l;
			}
		}

		if (last - l < l - first)
		{
			QuickSort(first, l, comp);
			first = l + 1;
		}
		else
		{
			QuickSort(l + 1, last, comp);
			last = l;
		}
	}
}


// Insertion Sort

template<typename T, typename Compare>
void InsertionSort(T * first, T * last, Compare comp)
{
	for (auto it = first; it <= last; ++it)
	{
		T* j = it - 1;
		T temp = std::move(*it);

		while (j >= first && comp(temp, *j))
		{
			*(j + 1) = std::move(*j);
			j--;
		}

		*(j + 1) = std::move(temp);
	}
}


// Print Array

template<typename T>
void printArray(T * first, T * last)
{
	for (auto it = first; it != last; ++it)
	{
		std::cout << *it << " ";
	}

	std::cout << std::endl;
}


// Qick and Insertion Sort

template<typename T, typename Compare>
void QuickAndInsertionSort(T * first, T * last, Compare comp)
{
	while (first < last)
	{
		// Insertion sort is faster when the array size < than some N
		
		if (last - first < OPTIMAL_SIZE)
		{
			InsertionSort(first, last, comp);
			return;
		}

		// Else - Quick sort

		T pivot = Pivot(first, last, comp);
		T* f = first;
		T* l = last;

		while (f <= l)
		{
			while (comp(*f, pivot))
				++f;

			while (comp(pivot, *l))
				--l;

			if (f <= l)
			{
				std::swap(*f, *l);
				++f;
				--l;
			}
		}

		if (last - l < f - first)
		{
			QuickSort(first, l, comp);
			first = l + 1;
		}
		else
		{
			QuickSort(l + 1, last, comp);
			last = l;
		}
	}
}

class QuickSort
{
public:
	QuickSort();
	~QuickSort();
};

