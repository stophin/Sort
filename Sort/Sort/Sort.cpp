// Sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <conio.h>

#include "Sort.h"

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);

	srand(time(NULL));

	static int size = 1000;
	Sort sort(size);

	for (int i = 0; i < size; i++) {
		if (rand() % 2 == 0) {
			sort.set(i, -(rand() % 1000 + 1));
		}
		else {
			sort.set(i, rand() % 1000 + 1);
		}
		//sort.set(i, (i + 1) * 1000);
	}
	//sort.view();


	sort.prepare();
	sort.startTime();
	sort.countingSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("countingSort");

	_getch();

	sort.prepare();
	sort.startTime();
	sort.radixSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("radixSort");

	sort.prepare();
	sort.startTime();
	sort.bucketSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("bucketSort");

	_getch();

	sort.prepare();
	sort.startTime();
	sort.shellSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("shellSort");

	sort.prepare();
	sort.startTime();
	sort.quickSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("quickSort");

	sort.prepare();
	sort.startTime();
	sort.heapSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("heapSort");

	_getch();

	sort.prepare();
	sort.startTime();
	sort.mergeSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("mergeSort");

	_getch();

	sort.prepare();
	sort.startTime();
	sort.bubbleSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("bubbleSort");

	sort.prepare();
	sort.startTime();
	sort.selectSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("selectSort");

	sort.prepare();
	sort.startTime();
	sort.insertSort();
	sort.endTime();
	//sort.result();
	sort.check();
	sort.time("insertSort");

	printf("Test end\n");

	_getch();
    return 0;
}

