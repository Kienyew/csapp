int switch_impl(int n) {
	int result;
	switch(n) {
		case 100:
			result = n * 2;
			break;

		case 101:
			result = n + 2;
			break;

		case 102:
			result = 1;
			break;

		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
			result = n + n - 3;
			break;

		case 888:
			result = n * 888;
			break;

		default:
			result = 0;
			break;
	}

	return result;
}


