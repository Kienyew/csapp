#include <stdio.h>

#define N 16
typedef int fix_matrix[N][N];
void fix_set_diag(fix_matrix A, int val) {
	for (int i = 0; i != N * (sizeof(int) * (N + 1)); i += sizeof(int) * (N + 1)) {
		*((int*)(((char*)A) + i)) = val;
	}
}
