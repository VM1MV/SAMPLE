#include "segmented_bitonic_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bitonic sort implementation based on: https://en.wikipedia.org/wiki/Bitonic_sorter
// and https://www.geeksforgeeks.org/bitonic-sort/

static void swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

static void bitonicMerge(float arr[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            if (dir == (arr[i] > arr[i + k])) {
                swap(&arr[i], &arr[i + k]);
            }
        }
        bitonicMerge(arr, low, k, dir);
        bitonicMerge(arr, low + k, k, dir);
    }
}

static void bitonicSort(float arr[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(arr, low, k, 1);      // ascending
        bitonicSort(arr, low + k, k, 0);  // descending
        bitonicMerge(arr, low, cnt, dir);
    }
}

// Helper to find the next power of two >= n
static int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
    for (int seg = 0; seg < m; ++seg) {
        int start = seg_start[seg];
        int end = seg_start[seg + 1];
        int len = end - start;
        if (len <= 1) continue;
        // Bitonic sort requires length to be a power of 2
        int pow2 = nextPowerOf2(len);
        float* buf = (float*)malloc(pow2 * sizeof(float));
        memcpy(buf, data + start, len * sizeof(float));
        // Pad with +inf for ascending sort
        for (int i = len; i < pow2; ++i) buf[i] = 1.0f/0.0f;
        bitonicSort(buf, 0, pow2, 1);
        memcpy(data + start, buf, len * sizeof(float));
        free(buf);
    }
}