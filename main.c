#include <stdio.h>
#include "segmented_bitonic_sort.h"

int main() {
    float data[5] = {0.8, 0.2, 0.4, 0.6, 0.5};
    int seg_id[5] = {0, 0, 1, 1, 1};
    int seg_start[3] = {0, 2, 5};
    int n = 5;
    int m = 2;

    segmentedBitonicSort(data, seg_id, seg_start, n, m);

    printf("Sorted data: ");
    for (int i = 0; i < n; ++i) {
        printf("%.1f ", data[i]);
    }
    printf("\n");
    return 0;
}