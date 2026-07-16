#include <stdio.h>

int main() {
	int total = 0, counter = 0;
	int input = 0;
	printf("Enter first grade : \n");
	scanf_s("%d", &input);
	while (input != -1)
	{
		total = total + input;
		counter++;
		printf("Enter first grade: \n");
		scanf_s("%d", &input);
	}

	if (counter != 0) {
		printf("%d", total / counter);
	}
	else {
		printf("No grades where entered! \n");
	}

	return 0;
}