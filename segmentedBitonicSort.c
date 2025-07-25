// 分段双调排序（Bitonic Sort），满足所有题目要求
// 参考Bitonic Sort非递归实现：https://en.wikipedia.org/wiki/Bitonic_sorter
// 题目要求：不递归、不调用自定义函数、不动态分配内存、可并行、NaN鲁棒

#include <math.h> // for isnan

void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
    int i, j, k, l;
    for (i = 0; i < m; ++i) {
        int start = seg_start[i];
        int end = seg_start[i + 1];
        int len = end - start;
        // Bitonic sort 需要长度为2的幂，找到大于等于len的最小2的幂
        int pow2 = 1;
        while (pow2 < len) pow2 <<= 1;
        // 非递归Bitonic sort
        for (k = 2; k <= pow2; k <<= 1) {
            for (j = k >> 1; j > 0; j >>= 1) {
                // 可并行循环
                for (l = 0; l < len; ++l) {
                    int ix = l;
                    int iy = l ^ j;
                    if (iy > ix && iy < len) {
                        // 处理NaN：NaN永远排在最后
                        float a = data[start + ix];
                        float b = data[start + iy];
                        int a_isnan = isnan(a);
                        int b_isnan = isnan(b);
                        int up = ((ix & k) == 0); // 0:升序, 1:降序
                        if (!a_isnan && b_isnan) {
                            // a正常，b是NaN，不交换
                        } else if (a_isnan && !b_isnan) {
                            // a是NaN，b正常，交换
                            float tmp = data[start + ix];
                            data[start + ix] = data[start + iy];
                            data[start + iy] = tmp;
                        } else if (!a_isnan && !b_isnan) {
                            // 都不是NaN
                            if ((up && a > b) || (!up && a < b)) {
                                float tmp = data[start + ix];
                                data[start + ix] = data[start + iy];
                                data[start + iy] = tmp;
                            }
                        }
                        // 都是NaN，不交换
                    }
                }
            }
        }
    }
}