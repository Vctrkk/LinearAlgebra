#include<iostream>
using namespace std;

double det(double** A, int n);
double det3(double** A);
double det2(double** A);

int main() {
	int n;
	cout << "请输入方阵A的阶数n，且n≥2" << endl;
	cin >> n;
    if (n < 2)return -1;
    double** A = new double* [n]; //动态分配二维数组：行指针数组
    cout << "请输入矩阵a的元素：" << endl;
    for (int i = 0; i < n; i++)
    {
        A[i] = new double[n];
    }
    //矩阵A初始化
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }
    cout << "A的行列式为" << det(A, n) << endl;
    return 0;
}

double det(double** A, int n) {
    switch (n) {
    case 1:
        return A[0][0];
    case 2:
        return det2(A);
    case 3:
        return det3(A);
    default:
        //取遍前三行的所有三阶子式，该子式从i,j,k三列中取出
        double sum = 0;//待会就return这个值
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = i + 2; k < n; k++) {
                    double A1[3][3];//取出的3阶矩阵
                    double** A2 = new double* [n-3]; //代数余子式的矩阵
                    for (int l = 0; l < n - 3; l++) {
                        A2[l] = new double[n - 3];
                    }
                    //搜索第l列，若是i,j,k就加入3阶子式，若不是i,j,k就加入该子式的代数余子式
                    for (int l = 0; l < n; l++) {
                        int m1 = 0, m2 = 0;//m1给A1用，m2给A2用
                        if (l == i || l == j || l == k) {
                            A1[0][m1] = A[0][l]; A1[1][m1] = A[1][l]; A1[2][m1] = A[2][l];//A1初始化
                            m1++;
                        }
                        else {
                            for (int p = 0; p < n - 3; p++) A2[p][m2] = A[p + 3][l];//A2初始化
                            m2++;
                        }
                    }
                    //求逆序数
                    int exp = 0;//-1的幂次，就是下面要求的逆序数






                    //把子式*代数余子式的值加进sum
                    switch (exp % 2) {
                        case 0:
                            sum += det3(A1) * det(A2, n - 3);//凭啥A1报错？？？？？？？？
                            break;
                        case 1:
                            sum -= det3(A1) * det(A2, n - 3);//凭啥A1报错？？？？？？？？
                            break;
                    }
                    //动态数组A2消亡防止内存泄漏
                    for (int l = 0; l < n - 3; l++) delete[]A2[l];
                    delete[]A2;
                }
            }
        }
        return sum;
    }
}

double det3(double** A) {
    return A[0][0] * A[1][1] * A[2][2]
        + A[0][1] * A[1][2] * A[2][0]
        + A[1][0] * A[2][1] * A[0][2]
        - A[0][2] * A[1][1] * A[2][0]
        - A[0][0] * A[1][2] * A[2][1]
        - A[0][1] * A[1][0] * A[2][2];
}

double det2(double** A) {
    return A[0][0] * A[1][1] - A[0][1] * A[1][0];
}