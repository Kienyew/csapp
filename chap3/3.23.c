// reverse bit of x
int fun_b(unsigned x) {
	int val = 0;
	int i;
	for (i = 0; i != 32; ++i) {
		val = (val << 1) | (x & 1)
		x >>= 1;
	}
	return val;
}

// 3.24

int sum = 0;
int i = 0;

if (i < 10) {
	do {
		if (i & 1) {
			goto UPDATE_EXPR;
		}
		sum += 1;
UPDATE_EXPR:
		++i;
	} while (i < 10);
}
