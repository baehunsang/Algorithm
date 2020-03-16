#include <stdio.h>
void MergeSort(int input[], int start, int end);
void Merge(int input[], int start, int mid, int end);
	
int main() {
	printf("Enter the length of array\n");
	int length;
	scanf("%d", &length);
	int* array = malloc(sizeof(int) * length);
	printf("Enter %d inteagers\n", length);
	for (int i = 0; i < length; i++) {
		scanf("%d", &array[i]);
	}
	MergeSort(array, 0, length - 1);
	printf("\n");
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);

	return 0;
}

void Merge(int input[], int start, int mid, int end) {
	int i, j, k;
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int* LeftArr = malloc(sizeof(int) * (n1 + 1));
	int* RightArr = malloc(sizeof(int) * (n2 + 1));
	for (i = 0; i < n1; i++) {
		LeftArr[i] = input[start + i];
	}
	for (j = 0; j < n2; j++) {
		RightArr[j] = input[mid + 1 + j];
	}
	LeftArr[n1] = 9999;
	RightArr[n2] = 9999;  //sorting 한계, 오름타순 내림차순 결정
	i = 0; j = 0;
	for (k = start; k <= end; k++) {
		if (LeftArr[i] <= RightArr[j]) {//오름차순, 내림차순
			input[k] = LeftArr[i];
			i++;
		}
		else {
			input[k] = RightArr[j];
			j++;
		}

	}
	free(LeftArr);
	free(RightArr);
}

void MergeSort(int input[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(input, start, mid);
		MergeSort(input, mid + 1, end);
		Merge(input, start, mid, end);
	}
}