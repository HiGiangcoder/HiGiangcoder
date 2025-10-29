#include <iostream>
#include <cmath>
#include <cuda_runtime.h>

using namespace std;
using ll = long long;
const unsigned long long K = (1ULL << 63) | 13ULL;

__device__ long long simulate_device(long long s, long long n) {
    int v0[128];
    int v1[128];
    int len0 = 0, len1 = 0;

    double f = 0, na = 0, ng = 0;
    double a = -19;
    long long r = -19;
    const unsigned long long K = (1ULL << 63) | 13ULL;

    while (a < 1.0 * s * s) {
        na += 1.0 / 19.0;
        double f1 = f;

        // Sinh bit cho v0, v1
        for (int i2 = 0; i2 < 2; ++i2) {
            long long m = 19;
            int* v = (i2 == 0 ? v0 : v1);
            int& len = (i2 == 0 ? len0 : len1);
            len = 0;

            while (m) {
                m = n;
                len = 0;
                while (m > 0 && len < 128) {
                    int bit = (r & 1LL) ? 1 : 0;
                    v[len++] = bit;
                    long long rb = (r >> 1);
                    unsigned long long next = (unsigned long long)rb ^ (bit ? K : 0ULL);
                    r = (long long)next;
                    m -= 1 + bit;
                }
            }
        }

        bool e = true;
        int L = len0 < len1 ? len0 : len1;
        for (int i = 0; i < L; ++i) {
            if (v0[i] != v1[i]) { e = false; break; }
        }

        if (e) {
            ng += s;
            f = llround(ng / na);
            a = (f == f1) ? (a + 1.0 / 1919.0) : 0;
        }
    }
    return (long long)f;
}

__global__ void kernel_simulate(long long *s_arr, long long *n_arr, long long *out, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N) {
        out[idx] = simulate_device(s_arr[idx], n_arr[idx]);
    }
}

int main() {
    const int N = 10000;
    ll *h_s = new ll[N];
    ll *h_n = new ll[N];
    for (int i = 0; i < N; ++i) {
        h_s[i] = 1 + i / 100;
        h_n[i] = 1 + i % 100;
    }

    ll *d_s, *d_n, *d_out;
    cudaMalloc(&d_s, N * sizeof(ll));
    cudaMalloc(&d_n, N * sizeof(ll));
    cudaMalloc(&d_out, N * sizeof(ll));

    cudaMemcpy(d_s, h_s, N * sizeof(ll), cudaMemcpyHostToDevice);
    cudaMemcpy(d_n, h_n, N * sizeof(ll), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;
    kernel_simulate<<<blocks, threads>>>(d_s, d_n, d_out, N);

    ll *h_out = new ll[N];
    cudaMemcpy(h_out, d_out, N * sizeof(ll), cudaMemcpyDeviceToHost);

    for (int i = 0; i < 10; ++i) // in thử 10 kết quả đầu
        cout << h_s[i] << " " << h_n[i] << " -> " << h_out[i] << "\n";

    cudaFree(d_s);
    cudaFree(d_n);
    cudaFree(d_out);
    delete[] h_s;
    delete[] h_n;
    delete[] h_out;

    return 0;
}