int fact_for_goto(int n) {
	int i = 2;
	int result = 1;
	if (!(i <= n)) {
		goto done;
	}

loop:
	result *= i;
	i++;

	if (i <= n) {
		goto loop;
	}

done:
	return result;
}

