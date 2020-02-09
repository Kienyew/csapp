int accum = 0;

int sum(int x, int y)
{
	int z = x + y;
	accum += z;
	return z;
}

