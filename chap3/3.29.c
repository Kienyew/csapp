// 3.29 @ 2019-06-03 19:39:00
int switcher(int a, int b, int c) {
	int answer;
	switch (a) {
		case 5:
			c = b ^ 15;
		case 0:
			answer = c + 112;
			break;

		case 2:
		case 7:
			answer = (b + c) << 2;
			break;

		case 4:
			answer = 4;
			break;
		
		default:
			answer = b;
	}

	return answer;
}
