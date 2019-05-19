int main() {
	int condition = 0;
	// TODO: implement else and else if
	if (condition == 1) {
		putchar('F');
		putchar('a');
		putchar('i');
		putchar('l');
		putchar('!');
		putchar('\n');
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
	putchar('\n');
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
		putchar('\n');
	}
	return 0;
}