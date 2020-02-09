#include <stdio.h>

unsigned float2bit(float f) {
	union {
		float f;
		unsigned u;
	} temp;
	temp.f = f;
	return temp.u;
}

unsigned copy(unsigned u) {
	return u;
}

int main() {
	float f = 3.14159;
	unsigned a = float2bit(f);
	unsigned b = copy(a);
	printf("equal? %d\n", a == b);	
}
