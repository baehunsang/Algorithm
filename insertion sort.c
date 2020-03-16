#include <stdio.h>
void InsertionSort(int input[], int length) {
	int i, j, key;
	for (j = 1; j < length; j++) {
		key = input[j];
		//input[j]보다 앞에 있으면서 큰 수들은 input[j] 뒤로
		for (i = j - 1; i >= 0; i--) {
			if (key <input[i]) {//오름차순, 내림차순 결정
				input[i+1] = input[i];
				input[i] = key;
			}
		}
	}
}
int main() {
	printf("Enter the length of array\n");
	int length; 
	scanf("%d", &length);
	int* array = malloc(sizeof(int)*length);
	printf("Enter %d inteagers\n", length);
	for (int i = 0; i < length; i++) { 
		scanf("%d", &array[i]);
	}
	InsertionSort(array, length);
	for (int i = 0; i < length; i++) {
		printf("\n%d\n", array[i]);
	}
	free(array);

	return 0;
}