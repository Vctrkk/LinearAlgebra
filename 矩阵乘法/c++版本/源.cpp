#include<iostream>
using namespace std;

int m1, n1, m2, n2;

int main()
{
    cout << "请输入矩阵A的行数和列数：" << endl;
    cin >> m1 >> n1;

    double** A = new double* [m1]; //动态分配二维数组：行指针数组
    cout << "请输入矩阵A的元素：" << endl;
    for (int i = 0; i < m1; i++)
    {
        A[i] = new double[n1];
    }
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            cin >> A[i][j];//矩阵A初始化
        }
    }

    //输出矩阵A
    cout << "您输入的矩阵为" << endl;
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }


    m2 = n1;
    cout << "矩阵B的行数为" << m2 << "，请输入矩阵B的列数：" << endl;
    cin >> n2;

    double** B = new double* [m2];
    cout << "请输入矩阵B的元素：" << endl;
    for (int i = 0; i < m2; i++)
    {
        B[i] = new double[n2];
    }
    for (int i = 0; i < m2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            cin >> B[i][j];//矩阵B初始化
        }
    }

    //输出矩阵B
    cout << "您输入的矩阵为" << endl;
    for (int i = 0; i < m2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }


    //AB=C
    double** C = new double* [m1];
    for (int i = 0; i < m1; i++)
    {
        C[i] = new double[n2];
    }
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            C[i][j] = 0;
            for (int p = 0; p < m2; p++)
            {
                C[i][j] = C[i][j] + A[i][p] * B[p][j];
            }
        }
    }


    //输出矩阵C
    cout << "C = AB =：" << endl;
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }


    system("pause");
    return 0;
}