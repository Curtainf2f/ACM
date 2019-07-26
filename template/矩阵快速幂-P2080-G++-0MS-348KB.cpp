#include<stdio.h>
#include<string.h>
using namespace std;

typedef long long LL;
const int MAXN = 2;
const int MOD = 10000;

int matrixFirst[MAXN][MAXN] = {
    {1, 0},
    {0, 0}
};

int matrixData[MAXN][MAXN] = {
    {1, 1},
    {1, 0}
};

template <typename T>
class Matrix {
public:
    T data[MAXN][MAXN];
    Matrix() {
        memset(data, 0, sizeof(data));
    }
    Matrix operator * (const Matrix &b) {
        Matrix res;
        for(int i = 0; i < MAXN; i ++) {
            for(int j = 0; j < MAXN; j ++) {
                for(int k = 0; k < MAXN; k ++) {
                    res.data[i][j] += this->data[i][k] * b.data[k][j] % MOD;
                    res.data[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    Matrix friend operator ^ (Matrix a, int n) {
        Matrix res;
        for(int i = 0; i < MAXN; i ++) {
            res.data[i][i] = 1;
        }
        while(n) {
            if(n & 1)
                res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
    Matrix friend operator ^ (Matrix a, LL n) {
        Matrix res;
        for(int i = 0; i < MAXN; i ++) {
            res.data[i][i] = 1;
        }
        while(n) {
            if(n & 1)
                res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
    void getData(const T x[MAXN][MAXN]) {
        memcpy(this->data, x, sizeof(T) * MAXN * MAXN);
    }
};

int main() {
    Matrix<int> first, mul;
    first.getData(matrixFirst);
    mul.getData(matrixData);
    int n;
    while(scanf("%d", &n) != EOF && n != -1) {
        if(n == 0)
            puts("0");
        else if(n == 1)
            puts("1");
        else {
            printf("%d\n", ((mul ^ (n - 1)) * first).data[0][0]);
        }
    }
    return 0;
}
