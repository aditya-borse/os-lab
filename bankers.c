#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

int main() {
	int alloc[MAX_PROCESSES][MAX_RESOURCES];
	int max[MAX_PROCESSES][MAX_RESOURCES];
	int avail[MAX_RESOURCES];

	int n, m;
	printf("Number of processes: ");
	scanf("%d", &n);
	printf("Number of resources: ");
	scanf("%d", &m);
	
	int num;
	for(int i = 0; i < n; i++) {
		printf("Enter allocated resources to process: %d\n", i + 1);
		for (int j = 0; j < m; j++) {
			scanf("%d", &num);
			alloc[i][j] = num;
		}
	}
	
	for(int i = 0; i < n; i++) {
		printf("Enter max resources for process: %d\n", i + 1);
		for (int j = 0; j < m; j++) {
			scanf("%d", &num);
			max[i][j] = num;
		}
	}
	
	printf("Enter the available resources:\n");
	for (int i = 0; i < m; i++) {
		scanf("%d", &num);
		avail[i] = num;
	}

	// calculate need matrix
	int need[MAX_PROCESSES][MAX_RESOURCES];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	// create a work matrix
	int work[MAX_RESOURCES];
	for (int i = 0; i < m; i++) {
		work[i] = avail[i];
	}

	int count = 0;
	int finish[MAX_PROCESSES] = {0};
	int safeSq[MAX_PROCESSES];
	while (count != n) {
		bool found = false;
		for (int i = 0; i < n; i++) {
			if (finish[i] == 0) {
				int j;
				for (j = 0; j < m; j++) {
					if (need[i][j] > work[j]) {
						break;
					}
				}
				if (j == m) {
					for (int k = 0; k < m; k++) {
						work[k] += alloc[i][k];
					}
					safeSq[count++] = i + 1;
					finish[i] = 1;
					found = true;
				}
			}
		}
		if (found == false) {
			printf("System is not in safe state\n");
			break;
		}
	}
	printf("System is in safe state\nSafe Sequence: ");
	for (int i = 0; i < n; i++) {
		printf("P%d ", safeSq[i]);
	}
	printf("\n");
}
		
