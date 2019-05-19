int putint(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10)
		putint(n / 10);
	putchar(n % 10 + '0');
	return 0;
}

int newline() {
	return putchar('\n');
}

int main() {
	putint(1024);
	newline();
	int condition = 0;
	// TODO: implement else and else if
	if (condition == 1) {
		putchar('F');
		putchar('a');
		putchar('i');
		putchar('l');
		putchar('!');
		newline();
		return -1;
	}
	int alphabet = 'a';
	int uppercase = 'A';
	// TODO: implement <=
	while (alphabet < 'z' || alphabet == 'z') {
		putchar(uppercase);
		putchar(alphabet);
		// TODO: implement +=
		// TODO: implement ++
		alphabet = alphabet + 1;
		uppercase = uppercase + 1;
	}
	newline();
	if ('\n' != 1 + 2 - 3 * 4 / 5 % 6 && 7 || 8 == 9 != 10) {
		// TODO: make int* functional
		putchar('H');
		putchar('e');
		putchar('l');
		putchar('l');
		putchar('o');
		putchar(',');
		putchar(' ');
		putchar('w');
		putchar('o');
		putchar('r');
		putchar('l');
		putchar('d');
		putchar('!');
		newline();
	}
	return 0;
}