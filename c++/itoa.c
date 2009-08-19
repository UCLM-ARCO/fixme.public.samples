#define _GNU_SOURCE
#include <stdio.h>

int main() {
	char* s;
	int i, n = -15;

	for (i=0; i<10000; ++i) {
		asprintf(&s, "%d", n);
	}
}

