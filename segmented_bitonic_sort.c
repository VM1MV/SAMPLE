#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// segmentedBitonicSort.h 内容
#ifndef SEGMENTED_BITONIC_SORT_H
#define SEGMENTED_BITONIC_SORT_H
#ifdef __cplusplus
extern "C" {
#endif
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m);
#ifdef __cplusplus
}
#endif
#endif // SEGMENTED_BITONIC_SORT_H

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
        int pow2 = nextPowerOf2(len);
        float* buf = (float*)malloc(pow2 * sizeof(float));
        memcpy(buf, data + start, len * sizeof(float));
        for (int i = len; i < pow2; ++i) buf[i] = 1.0f/0.0f;
        bitonicSort(buf, 0, pow2, 1);
        memcpy(data + start, buf, len * sizeof(float));
        free(buf);
    }
}

// main.c 内容
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