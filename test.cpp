#include "pch.h"
#include "../QuickSort.h"
#include <random>
#include "gtest/gtest.h"

std::default_random_engine randGenerator;


// Quick sort 
TEST(QuickSort, element_sort) {
	randGenerator.seed(time(NULL));
	const int size = 6;
	int array[size] = { 6, 7, 1, 3, 8, 4 };

	QuickSort(array, array + size - 1, [](int a, int b) { return a < b; });

	for (int i = 0; i < size - 1; ++i)
		ASSERT_LE(array[i], array[i + 1]);
}


// QS 100 elements
TEST(QuickSort, element_sort_big_size) {
	randGenerator.seed(time(NULL));
	const int size = 100;
	int array[size]{};
	std::uniform_int_distribution<int> randNumber(1, 100);

	for (int i = 0; i < size; i++)
		array[i] = randNumber(randGenerator);

	QuickSort(array, array + size - 1, [](int a, int b) { return a < b; });

	for (int i = 0; i < size - 1; ++i)
		ASSERT_LE(array[i], array[i + 1]);
}


// Q and I sort
TEST(QuickAndInsertionSort, element_sort) {
	randGenerator.seed(time(NULL));
	const int size = 6;
	int array[size] = { 6, 7, 1, 3, 8, 4 };

	QuickAndInsertionSort(array, array + size - 1, [](int a, int b) { return a < b; });

	for (int i = 0; i < size - 1; ++i)
		ASSERT_LE(array[i], array[i + 1]);
}


// QS  str array 100 elements
TEST(QuickSort, element_sort_big_size_str) {
	randGenerator.seed(time(NULL));
	const int size = 100;
	std::string array[size]{};
	std::uniform_int_distribution<int> randNumber(1, 100);

	for (int i = 0; i < size; i++)
		array[i] = std::to_string(randNumber(randGenerator));

	QuickSort(array, array + size - 1, [](std::string a, std::string b) { return a < b; });

	for (int i = 0; i < size - 1; ++i)
		ASSERT_LE(array[i], array[i + 1]);
}


// Q and I string array 35 elements
TEST(QuickAndInsertionSort, element_sort_big_size_for_str) {
	randGenerator.seed(time(NULL));
	const int size = 35;
	std::string array[size]{};
	std::uniform_int_distribution<int> randNumber(1, 100);

	for (int i = 0; i < size; i++)
		array[i] = std::to_string(randNumber(randGenerator));

	QuickAndInsertionSort(array, array + size - 1, [](std::string a, std::string b) { return a < b; });

	for (int i = 0; i < size - 1; ++i)
		ASSERT_LE(array[i], array[i + 1]);
}