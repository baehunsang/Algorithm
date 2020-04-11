#include <stdio.h>
void MatrixChainOrder(int dimension[], int table[][5], int parenthesize[][5], int size);
int main() {
	int dimension[6] = {2, 4, 5, 6, 2, 3};
	
	/*A1 : 2 X 3
	  A2 : 4 X 5
	  A3 : 5 X 6
	  A4 : 6 X 2
	  A5 : 2 X 3*/

	int table[5][5] = {0, };
	int parenthesize[5][5] = {0, };
	int numOfMatrix = 5;
	MatrixChainOrder(dimension, table, parenthesize, sizeof(dimension)/sizeof(int));
	printf("< Table m >\n");
	printf("index j\t1\t2\t3\t4\t5\nindex i\n");
	for (int i = 0; i < 5; i++) {
		printf("%d\t", i+1);
		for (int j = 0; j < 5; j++) {
			printf("%d\t", table[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("< Table s >\n");
	printf("index j\t1\t2\t3\t4\t5\nindex i\n");
	for (int i = 0; i < 5; i++) {
		printf("%d\t", i + 1);
		for (int j = 0; j < 5; j++) {
			printf("%d\t", parenthesize[i][j]);
		}
		printf("\n");
	}


	return 1;
}

/*Thomas H. Cormen(1990). Introduction to Algorithms(2nd ed.). p.287 - p.288 */
void MatrixChainOrder(int dimension[], int table[][5], int parenthesize[][5], int size) {
	int n = size -1;                             
	int i, j, k, l;                              
	int q;                                        
	for (i = 0; i < n; i++) {                    
		table[i][i] = 0;
	}

	for (l = 2; l <= n; l++) {                  
		for (i = 0; i <= n - l; i++) {
			j = i + l - 1;
			table[i][j] = 999999;

			for (k = i; k <= j - 1; k++) {
				q = table[i][k] + table[k + 1][j] + dimension[i] * dimension[k + 1] * dimension[j + 1];
				if (table[i][j] > q) {
					table[i][j] = q;
					parenthesize[i][j] = k + 1;
				}
			}
		}
	}
}
