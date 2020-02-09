#include <stdio.h>
#include <stdlib.h>

int absdiff(int x, int y) {
	int result;
	if (x > y) {
		goto x_g_y;
	}
	result = y - x;
	goto done;
x_g_y:
	result = x - y;

done:
	return result;

}

// 3.18

int test(int x, int y) {
	int val = x * y;
	if (x >= -3) {
		if (x > 2) {
			val = x - y;
		} else {
			val = x ^ y;
		}
	} else if (x <= y) {
		val = x + y;
	}

	return val;
}

int test1(int x, int y) {
	int val = x ^ y;
	if (x < -3) {
		if (y < x)
			val = x * y;
		else
			val = x + y;
	} else if (x > 2)
		val = x - y;

	return val;
}

int main() {
	int not_equal_count = 0;
	int equal_count = 0;
	for (int i = 0; i < 1000000; ++i) {
		int x = rand() % 10000 - 5000;
		int y = rand() % 10000 - 5000;
		if (test(x, y) == test1(x, y)) {
			++ equal_count;
		} else {
			++ not_equal_count;
		}
	}
	printf("ne:eq = %d:%d\n", not_equal_count, equal_count);

}
