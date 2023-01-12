#include "GraphGenerator.h"

void GraphGenerator::randomSplit() {
	int left_c = comm_num;
	int left_n = node_num;

	srand((unsigned)time(NULL));

	while (left_c > 0) {
		int upper = left_n - left_c + 1;
		int lower = 1;
		int cnode = (rand() % (upper - lower + 1)) + lower;
		left_c--;
	}
}