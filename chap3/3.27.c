#include <stdio.h>
#include <stdlib.h>

int test1(int x, int y) {
	int val = 4 * x;
	if (y > 0) {
		if (x < y) {
			val = x - y;
		} else {
			val = x ^ y;
		}
	} else if (y < -2) {
		val = x + y;
	}

	return val;
}


int test2(int x, int y) {
	int val = 4 * x;
	if (y > 0) {
		if (x < y) {
			val = x - y;
		} else {
			val = x ^ y;
		}
	} else if (y < -2) {
		val = x + y;
	}

	return val;
}
int main(int argc, char* argv[]) {
	int eq = 0;
	int neq = 0;
L1:
L2:
	for (int i = 0; i < 1000000; i++) {
		int x = rand() % 2000 - 1000;
		int y = rand() % 2000 - 1000;
		if (test1(x, y) == test2(x, y)) {
			eq ++;
		} else {
			neq ++;
		}
	}
	printf("eq:neq = %d:%d\n%d,%d\n", eq, neq, &&L1, &&L2);

}
