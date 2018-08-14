#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i;
	for (i = 2; i <= 200; i += 2) {
		printf("% 4i", i);
		if ((i % 10) == 0) {
			printf("\n");
		}
	}
	return 0;
}
