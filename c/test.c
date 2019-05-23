int puts(int* string) {
	int i = 0;
	while (string[i]) {
		putchar(string[i]);
		i = i + 1;
	}
	return 1;
}

int puti(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10)
		puti(n / 10);
	putchar(n % 10 + '0');
	return 0;
}

int main() {
	int x = 0;
	int y = 1;
	int z = 2;
	while (x < 100000) {
		puti(x);
		putchar('\n');

		z = x + y;
		x = y;
		y = z;
	}
	return 1;
}