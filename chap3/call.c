int func() {
	return 0xff;
}

int main() {
	volatile int a = func();
}
