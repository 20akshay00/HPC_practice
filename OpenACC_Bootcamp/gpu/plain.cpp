#include<iostream>
#include<chrono>

#define N 100000

using namespace std::chrono;

int main()
{
float A[N], B[N], C[N];
for(long i = 0; i < N; i++)
{
        A[i] = i;
        B[i] = i*i;
}

auto start = high_resolution_clock::now();
for(long j =0; j < N; j++)
{
        C[j] = A[j] + B[j];
}
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
std::cout << duration.count() << std::endl;

}

