//
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "QuickSort.h"

typedef std::chrono::nanoseconds ns;
typedef std::chrono::system_clock::time_point type_;
typedef std::chrono::high_resolution_clock time_;

#define AVG_COUNT_SIZE 100000
#define ARRAY_SIZE 60

int main() {

	std::default_random_engine gen;
	std::uniform_int_distribution<int> rand(1, 100);
	gen.seed(time(NULL));

	std::ofstream f("time.csv");
	//std::ofstream f1("time1.csv");
	//std::ofstream f2("time2.csv");


	// Test time (Array size)

	for (int size = 1; size <= ARRAY_SIZE; ++size)
	{
		ns time1 = std::chrono::nanoseconds(0);
		ns time2 = std::chrono::nanoseconds(0);

		// Average x AVG_COUNT_SIZE
		// get time 1 and time 2, then add next t1 t2, repeat n times, get average (t/n)

		for (int j = 0; j < AVG_COUNT_SIZE; ++j)
		{

			int* array1 = new int[size];
			int* array2 = new int[size];
			
			// Arrays with random values

			for (int i = 0; i < size; ++i) {

				array1[i] = rand(gen);
				array2[i] = array1[i];

			}
				

			//for (int i = 0; i < size; ++i)
			//	array2[i] = rand(gen);
			
			//for (int i = size - 1, k = 1; i >= 0; i--, k++)
			//	array2[i] = k;




			// time 1 - QS

			auto start1 = time_::now();
			QuickSort(array1, array1 + size - 1, [](int a, int b) { return a < b; });
			auto end1 = time_::now();

			time1 += (end1 - start1);

		
			// time 2 - IS

			auto start2 = time_::now();
			InsertionSort(array2, array2 + size - 1, [](int a, int b) { return a < b; });
			auto end2 = time_::now();

			time2 += (end2 - start2);

			delete[] array1;
			delete[] array2;
			
		}
		

		// Average time value

		time1 /= AVG_COUNT_SIZE;
		time2 /= AVG_COUNT_SIZE;


		// Write data to file

		if (f.is_open())
			f << time1.count() << " ; " << time2.count() << "\n";

		//if (f1.is_open())
		//	f1 << time1.count() << "\n";

		//if (f2.is_open())
		//	f2 << time2.count() << "\n";
	}

	f.close();
	//f1.close();
	//f2.close();
	return 0;
}
