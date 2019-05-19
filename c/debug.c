// Temporary standard library.
int* __cxci_malloc(int len) {return 0;}
int __cxci_getc() {return 0;}
int __cxci_putc(int ch) {return 0;}

// Returns the length of a string.
int strlen(int* str) {
	int len = 0;
	while (*str != 0) {
		str = str + 1;
		len = len + 1;
	}
	return len;
}

// Concatenates two strings.
int* strcat(int* a, int* b) {
	int len1 = strlen(a);
	int len2 = strlen(b);
	int* buffer = __cxci_malloc(len1 + len2);
	if (!buffer) {
		return 0;
	}
	int i = 0;
	while (i < len1) {
		buffer[i] = a[i];
	}
	int j = 0;
	while (j < len2) {
		buffer[j + len1] = b[j];
	}
	return buffer;
}

// Get a string from stdin.
int* gets() {
	int* buffer = __cxci_malloc(1024);
	if (!buffer) {
		return 0;
	}
	int i = 0;
	int ch = 0;
	while ((ch = __cxci_getc()) != '\n') {
		buffer[i] = ch;
		i = i + 1;
	}
	buffer[i] = 0;
	return buffer;
}

// Print a string to stdout.
int puts(int* str) {
	int len = strlen(str);
	int i = 0;
	while (i < len) {
		__cxci_putc(str[i]);
		i = i + 1;
	}
	return 0;
}

// Hello world.
int main() {
	puts("What is your name?");
	int* name = gets();
	puts(strcat("Hello, ", strcat(name, "!")));
	return 0;
}