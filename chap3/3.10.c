#pragma GCC optimize("O0")

int f1(int x) {
	x ^= x;
	return x;
}

int f2(int x) {
	x = 0;
	return x;
}

