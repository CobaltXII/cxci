// // Returns the length of a string.
// size_t strlen(char* str) {
// 	size_t len = 0;
// 	while (*(str++) != 0) {
// 		len++;
// 	}
// 	return len;
// }

// Returns the length of a string.
int strlen(int* str) {
	int len = 0;
	while (*str != 0) {
		str = str + 1;
		len = len + 1;
	}
}