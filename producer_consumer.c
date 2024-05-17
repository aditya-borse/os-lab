#include <stdio.h>
int mutex = 1;
int full = 0;
int empty = 10; // buffer of size 10 
int data = 0;

void acquire_op(int *mutex) {
	*mutex -= 1;
}

void release_op(int *mutex) {
	*mutex += 1;
}

void wait_op(int *var) {
	*var -= 1;
}

void signal_op(int *var) {
	*var += 1;
}

void producer() {
	wait_op(&empty);
	acquire_op(&mutex);
	data++;
	printf("Procuder produces: %d\n", data);
	release_op(&mutex);
	signal_op(&full);
}

void consumer() {
	wait_op(&full);
	acquire_op(&mutex);	
	printf("Consumer consumes: %d\n", data);
	data--;
	release_op(&mutex);
	signal_op(&empty);
}

int main() {
	int choice = 0;
	printf("Menu\n");
	printf("1. Produce\n");
	printf("2. Consume\n");
	printf("3. Exit\n");
	while(choice != 3){
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				if (mutex == 1 && empty != 0) {
					producer();
				}
				else {
					printf("Buffer is full!\n");
				}	
				break;
			case 2:
				if (mutex == 1 && full != 0) {
					consumer();
				}
				else {
					printf("Buffer is empty!\n");
				}
				break;
			case 3:
				printf("Exiting....\n");
				break;
			default:
				printf("Invalid choice\n");
		}
	}
}	
