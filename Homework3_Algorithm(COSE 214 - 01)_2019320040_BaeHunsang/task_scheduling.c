/* Assignment for Algorithm(COSE 214 - 01)
   
   Program which solves the unit task scheduling problem
   
   Working environment: Visual Studio 2019 */


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
typedef struct {
	char taskName[20];
	int deadLine;
	int panalty;
} Task;                 

typedef struct{
	int count;
	int capacity;
	Task* task;
}Head;        // Header which contains the meta datas and the pointer to a task array.  

int compare(const void* n1, const void* n2) {
	const Task* input1 = n1;
	const Task* input2 = n2;
	if (input1->panalty < input2->panalty) {
		return 1;
	}
	else if (input1->panalty == input2->panalty) {
		return 0;
	}
	else {
		return -1;
	}
}                     // Compare function for quick sort.

Head* MakeHead() {
	Head* head = (Head*)malloc(sizeof(Head));
	head->count = 0;
	head->capacity = 1;
	head->task = (Task*)malloc(sizeof(Task) * (head ->capacity));
	return head;
}

int TaskSchedule(Head* head, Task* output) {
	int index;
	int panalty = 0;
	for (int i = 0; i < head->count; i++) {
		index = ((head->task)[i].deadLine) - 1;
		if (output[index].deadLine == 0) {
			strcpy(output[index].taskName, (head->task)[i].taskName);
			output[index].panalty = (head->task)[i].panalty;
			output[index].deadLine = (head->task)[i].deadLine;
		}
		else {
			index = ((head->task)[i].deadLine) - 1;
			while (output[index].deadLine != 0 && index >= 0) {
				index--;
				if (index <0) {
					break;
				}
			}
			if (index < 0) {
				panalty += (head->task)[i].panalty;         
			}
			else {
				strcpy(output[index].taskName, (head->task)[i].taskName);
				output[index].panalty = (head->task)[i].panalty;
				output[index].deadLine = (head->task)[i].deadLine;
			}
		}
	}
	return panalty;
}                                      // Task scheduling algorithm

void InsertTask(FILE* fp, Head* head, int index) {
	char buffer[50];
	char* strPtr;
	if (head->capacity == head->count) {
		head->capacity *= 2;
		head->task = (Task*)realloc(head->task, sizeof(Task) * (head->capacity));
	}
	fgets(buffer, sizeof(buffer), fp);
	strPtr = strtok(buffer, ",");
	strcpy((head->task)[index].taskName, strPtr);
	strPtr = strtok(NULL, ",");
	(head->task)[index].deadLine = atoi(strPtr);
	strPtr = strtok(NULL, ",");
	(head->task)[index].panalty = atoi(strPtr);
	head->count++;
}                  


int main(int argc, char** argv) {
	Head* head = MakeHead();
	FILE* fp = fopen(argv[1], "r");
	char* buffer[50];
	int panalty = 0;
	int i = 0;
	assert(fp != NULL);
	fgets(buffer, sizeof(buffer), fp);
	while (!feof(fp)) {
		InsertTask(fp, head, i);
		i++;
	}                    // Insert task in array.

	qsort(head->task, head->count, sizeof(Task), compare);   // Sort the tasks.

	Task* outputArr = (Task*)malloc(sizeof(Task) * (head->count));
	memset(outputArr, 0, sizeof(Task) * (head->count));
	
	panalty = TaskSchedule(head, outputArr); // Schedule the tasks in the output array.

	printf("===============\n");   //Print output.
	printf("  Time  |  Task\n");
	printf("===============\n");
	for (i = 0; i < head->count; i++) {          
		printf("[%d - %d] |", i, i+1);
		printf("  %s\n", outputArr[i].taskName);
	}
	printf("\n");
	printf("Panalty: %d\n", panalty);

	free(outputArr);
	free(head->task);
	free(head);
	fclose(fp);
	
}


