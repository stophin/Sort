#pragma once

#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

class Sort {
public:
	Sort(int size) : size(size), data(NULL), sort(NULL) {
		data = new int[size];
		sort = new int[size];
	}
	~Sort() {
		delete[] data;
		data = NULL;
		delete[] sort;
		sort = NULL;
	}

	void set(int index, int value) {
		if (index >= size || index < 0) {
			return;
		}
		data[index] = value;
	}

	void set(int n, ...) {
		va_list argptr;
		va_start(argptr, n);
		for (int i = 0; i < n; ++i) {
			data[i] = va_arg(argptr, int);
		}
		va_end(argptr);
	}
	void prepare() {
		for (int i = 0; i < size; i++) {
			sort[i] = data[i];
		}
	}
	void view() {
		for (int i = 0; i < size; i++) {
			printf("%d\t", data[i]);
		}
		printf("\n");
	}
	void check() {
		for (int i = 0; i < size; i++) {
			int error = 0;
			if (i > 0) {
				if (sort[i - 1] > sort[i]) {
					error = 1;
				}
			}
			if (error) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("%d\t", sort[i]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			}
		}
		printf("\n");
	}
	void result() {
		for (int i = 0; i < size; i++) {
			int error = 0;
			if (i > 0) {
				if (sort[i - 1] > sort[i]) {
					error = 1;
				}
			}
			if (error) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			}
			printf("%d\t", sort[i]);
			if (error) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			}

		}
		printf("\n");
	}
	void startTime() {
		start = clock();
	}
	void endTime() {
		finish = clock();
		timesplash = (double)(finish - start);
	}
	void time(const char * name = NULL) {
		printf("%s Time: %lf\n", name ? name : "", timesplash);
	}
private:
	int size;
	int * data;
	int * sort;


	clock_t start, finish;
	double timesplash;

	void swap(int * arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
public:
	void bubbleSort() {
		for (int i = 1; i < size; i++) {
			//循环没有进行交换，已经有序，排序完成
			int flag = 1;
			for (int j = 0; j < size - i; j++) {
				if (sort[j] > sort[j + 1]) {
					swap(sort, j, j + 1);
					
					flag = 0;
				}
			}
			if (flag) {
				break;
			}
		}
	}

	void selectSort() {
		//N-1次比较
		for (int i = 0; i < size - 1; i++) {
			int min = i;
			//每次比较N-i
			for (int j = i + 1; j < size; j++) {
				if (sort[j] < sort[min]) {
					//记录目前最小元素下标
					min = j;
				}
			}
			//将找到的最小元素下标和i两个位置元素交换
			if (i != min) {
				swap(sort, i, min);
			}
		}
	}
	void insertSort() {
		//从下标为1的元素开始选择合适的位置插入
		for (int i = 1; i < size; i++) {
			//记录要插入的数据
			int temp = sort[i];
			//从已经排序的序列最右边开始比较，找到比其小的元素，同时移动比其大的数
			int j = i;
			for (; j > 0 && temp < sort[j - 1]; j--) {
				sort[j] = sort[j - 1];
			}
			//存在比其小的数
			if (j != i) {
				sort[j] = temp;
			}
		}
	}
	void shellSort() {
		int gap = 1;
		while (gap < size / 3) {
			gap = gap * 3 + 1;
		}
		while(gap > 0) {
			for (int i = gap; i < size; i++) {
				int temp = sort[i];
				int j = i - gap;
				while (j >= 0 && sort[j] > temp) {
					sort[j + gap] = sort[j];
					j -= gap;
				}
				sort[j + gap] = temp;
			}
			gap = (int)floor(gap / 3.0);
		}
	}
	void mergeSort() {
		int * result = mergeSortSub(sort, size);
		for (int i = 0; i < size; i++) {
			sort[i] = result[i];
		}
	}
	int * mergeSortSub(int * arr, int size) {
		if (size < 2) {
			return arr;
		}
		int middle = (int)floor(size / 2.0);

		int * left = new int[middle];
		int * right = new int[size - middle];

		for (int i = 0; i < middle; i++) {
			left[i] = arr[i];
		}
		for (int i = middle; i < size; i++) {
			right[i - middle] = arr[i];
		}

		return mergeSortMerge(mergeSortSub(left, middle), middle, mergeSortSub(right, size - middle), size - middle);
	}
	int * mergeSortMerge(int * left, int sizeLeft, int * right, int sizeRight) {
		int * result = new int[sizeLeft + sizeRight];
 		int i = 0; 
		while (sizeLeft > 0 && sizeRight > 0) {
			if (left[0] <= right[0]) {
				result[i++] = left[0];
				for (int j = 1; j < sizeLeft; j++) {
					left[j - 1] = left[j];
				}
				sizeLeft--;
			}
			else {
				result[i++] = right[0];
				for (int j = 1; j < sizeRight; j++) {
					right[j - 1] = right[j];
				}
				sizeRight--;
			}
		}
		while (sizeLeft > 0) {
			result[i++] = left[0];
			for (int j = 1; j < sizeLeft; j++) {
				left[j - 1] = left[j];
			}
			sizeLeft--;
		}
		while (sizeRight > 0) {
			result[i++] = right[0];
			for (int j = 1; j < sizeRight; j++) {
				right[j - 1] = right[j];
			}
			sizeRight--;
		}
		delete[] left;
		delete[] right;
		return result;
	}

	void quickSort() {
		int * result = quickSortSub(sort, 0, size - 1);
	}
	int * quickSortSub(int * arr, int left, int right) {
		if (left < right) {
			int par = quickSortPartition(arr, left, right);
			quickSortSub(arr, left, par - 1);
			quickSortSub(arr, par + 1, right);
		}
		return arr;
	}
	int quickSortPartition(int * arr, int left, int right) {
		//设定基准值pivot
		int pivot = left;
		int index = pivot + 1;
		for (int i = index; i <= right; i++) {
			if (arr[i] < arr[pivot]) {
				swap(arr, i, index);

				index++;
			}
		}
		swap(arr, pivot, index - 1);
		return index - 1;
	}

	void heapSort() {
		int len = size;
		heapSortBuildMaxHeap(sort, len);

		for (int i = len - 1; i > 0; i--) {
			swap(sort, 0, i);
			len--;
			heapSortHeapify(sort, 0, len);
		}
	}
	void heapSortBuildMaxHeap(int * arr, int len) {
		for (int i = (int)floor(len / 2.0); i >= 0; i--) {
			heapSortHeapify(arr, i, len);
		}
	}
	void heapSortHeapify(int * arr, int i, int len) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int largest = i;

		if (left < len && arr[left] > arr[largest]) {
			largest = left;
		}
		if (right < len && arr[right] > arr[largest]) {
			largest = right;
		}
		if (largest != i) {
			swap(arr, i, largest);
			heapSortHeapify(arr, largest, len);
		}
	}

	void countingSort() {
		int minValue = countintSortMinValue(sort, size);
		int defValue = 0;
		if (minValue < 0) {
			//将所有元素补足为正数
			defValue = -minValue;
			for (int i = 0; i < size; i++) {
				sort[i] += defValue;
			}
		}
		int maxValue = countingSortMaxValue(sort, size);

		int bucketLen = maxValue + 1;
		int * bucket = new int[bucketLen];
		for (int i = 0; i < bucketLen; i++) {
			bucket[i] = 0;
		}
		for (int i = 0; i < size; i++) {
			bucket[sort[i]] ++;
		}

		int index = 0;
		for (int j = 0; j < bucketLen; j++) {
			while (bucket[j] > 0) {
				sort[index++] = j;
				bucket[j] --;
			}
		}
		if (minValue < 0) {
			//恢复正数补足
			for (int i = 0; i < size; i++) {
				sort[i] -= defValue;
			}
		}
		delete[] bucket;
	}
	int countintSortMinValue(int * arr, int len) {
		int minValue = arr[0];
		for (int i = 1; i < len; i++) {
			if (minValue > arr[i]) {
				minValue = arr[i];
			}
		}
		return minValue;
	}
	int countingSortMaxValue(int * arr, int len) {
		int maxValue = arr[0];
		for (int i = 1; i < len; i++) {
			if (maxValue < arr[i]) {
				maxValue = arr[i];
			}
		}
		return maxValue;
	}

	void bucketSort() {
		bucketSortSub(sort, 5);
	}
	void bucketSortSub(int *arr, int bucketSize) {
		if (size == 0) {
			return;
		}

		int minValue = arr[0];
		int maxValue = arr[0];
		for (int i = 0; i < size; i++) {
			if (arr[i] < minValue) {
				minValue = arr[i];
			}
			else if (arr[i] > maxValue) {
				maxValue = arr[i];
			}
		}

		int bucketCount = (int)floor((maxValue - minValue) / bucketSize) + 1;
		int** buckets = new int*[bucketCount];
		//利用映射函数将数据分配到各个桶中
		//首先获取桶的大小
		int *bucketMat = new int[bucketCount];
		int *bucketUse = new int[bucketCount];
		for (int i = 0; i < bucketCount; i++) {
			bucketMat[i] = 0;
			bucketUse[i] = 0;
		}
		for (int i = 0; i < size; i++) {
			int index = (int)floor((arr[i] - minValue) / bucketSize);
			bucketMat[index]++;
		}
		//分配桶空间
		for (int i = 0; i < bucketCount; i++) {
			buckets[i] = new int[bucketMat[i] + 1];
			for (int j = 0; j < bucketMat[i] + 1; j++) {
				buckets[i][j] = 0;
			}
		}
		//分配数据
		for (int i = 0; i < size; i++) {
			int index = (int)floor((arr[i] - minValue) / bucketSize);
			buckets[index][bucketUse[index]] = arr[i];
			bucketUse[index] ++;
		}

		int arrIndex = 0;
		for (int i = 0; i < bucketCount; i++) {
			int *bucket = buckets[i];
			if (bucketUse[i] <= 0) {
				continue;
			}

			//使用插入排序对每个桶进行排序
			//从下标为1的元素开始选择合适的位置插入
			for (int j = 1; j < bucketUse[i]; j++) {
				//记录要插入的数据
				int temp = bucket[j];
				//从已经排序的序列最右边开始比较，找到比其小的元素，同时移动比其大的数
				int k = j;
				for (; k > 0 && temp < bucket[k - 1]; k--) {
					bucket[k] = bucket[k - 1];
				}
				//存在比其小的数
				if (k != j) {
					bucket[k] = temp;
				}
			}

			for (int j = 0; j < bucketUse[i]; j++) {
				sort[arrIndex++] = bucket[j];
			}
		}
		for (int i = 0; i < bucketCount; i++) {
			delete[] buckets[i];
		}
		delete[] buckets;
		delete[] bucketMat;
		delete[] bucketUse;
	}

	void radixSort() {
		int digit = radixSortGetMaxDigit(sort);
		radixSortSub(sort, digit);
	}
	int radixSortGetMaxDigit(int * arr) {
		int maxValue = radixSortGetMaxValue(arr);
		return radixSortGetNumLen(maxValue);
	}
	int radixSortGetMaxValue(int * arr) {
		int maxValue = arr[0];
		for (int i = 0; i < size; i++) {
			if (maxValue < arr[i]) {
				maxValue = arr[i];
			}
		}
		return maxValue;
	}
	int radixSortGetNumLen(long num) {
		if (num == 0) {
			return 1;
		}
		int len = 0;
		for (long temp = num; temp != 0; temp /= 10) {
			len++;
		}
		return len;
	}
	void radixSortSub(int * arr, int maxDigit) {
		int mod = 10;
		int dev = 1;

		//负数占用0~9，正数占用10~19，所以*2
		int maxLen = 20;// (int)pow(mod, maxDigit) * 2;
		int minLen = size;
		int ** counter = new int*[maxLen];
		for (int i = 0; i < maxLen; i++) {
			counter[i] = new int[minLen];
			for (int j = 0; j < minLen; j++) {
				counter[i][j] = 0;
			}
		}
		int * counterUse = new int[maxLen];
		for (int i = 0; i < maxDigit; i++, dev *= 10, mod *= 10) {
			for (int j = 0; j < maxLen; j++) {
				counterUse[j] = 0;
			}
			for (int j = 0; j < size; j++) {
				int bucket = ((arr[j] % mod) / dev) + 10;// +mod;
				counter[bucket][counterUse[bucket]++] = arr[j];
			}
			int pos = 0;
			for (int j = 0; j < maxLen; j++) {
				for (int k = 0; k < counterUse[j]; k++) {
					arr[pos++] = counter[j][k];
				}
			}
		}
		for (int i = 0; i < maxLen; i++) {
			delete[] counter[i];
		}
		delete[] counter;
		delete[] counterUse;
	}
};