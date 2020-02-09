// A. argument x;
// B:
int rfun(unsigned x) {
	if (x == 0)
		return 0;
	
	unsigned nx = x >> 1 ;
	int rv = rfun(nx);
	return (x & 1) + rv;
}

// C, count the 1's bits in unsigned number
