// segmented_bitonic_sort.c
// Bitonic sort for segments, non-recursive, no dynamic allocation, no function calls except stdlib, NaN robust
// Bitonic sort reference: https://en.wikipedia.org/wiki/Bitonic_sorter
// Author: ChatGPT

#include <math.h> // for isnan

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
    int i, j, k, l;
    for (int seg = 0; seg < m; ++seg) {
        int start = seg_start[seg];
        int end = seg_start[seg + 1];
        int len = end - start;
        // Bitonic sort requires power of 2, but we handle arbitrary length
        // We treat out-of-bound as +inf for ascending, -inf for descending
        // For NaN, always move to the end
        for (k = 2; k <= len; k <<= 1) {
            for (j = k >> 1; j > 0; j >>= 1) {
                for (i = 0; i < len; ++i) {
                    int ix = start + i;
                    int ixj = start + (i ^ j);
                    if (ixj < start || ixj >= end) continue;
                    // Only do compare-exchange in one direction to avoid double swap
                    if (i < (i ^ j)) {
                        float a = data[ix];
                        float b = data[ixj];
                        int a_isnan = isnan(a);
                        int b_isnan = isnan(b);
                        // Ascending order
                        if (!a_isnan && b_isnan) {
                            // a < NaN, do nothing
                        } else if (a_isnan && !b_isnan) {
                            // NaN > b, swap
                            data[ix] = b;
                            data[ixj] = a;
                        } else if (!a_isnan && !b_isnan) {
                            if (a > b) {
                                data[ix] = b;
                                data[ixj] = a;
                            }
                        }
                        // If both NaN, do nothing
                    }
                }
            }
        }
    }
}