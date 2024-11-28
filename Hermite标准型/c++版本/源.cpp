#include<iostream>
using namespace std;

int m, n;

//判断主元位置
int zhuyuan(double** A, int m)//输入矩阵指针及要检测的行数
{
    int i = 0;
    for (int j = 0; j < n; j++)
    {
        if (A[m][j] == 0)
        {
            i++;
        }
        else
        {
            break;
        }
    }
    return i;
}

//化简为hermit标准型
void huajian(double** A, int p, int q)//输入矩阵指针及该行的主元位置 第p+1行第q+1列
{
    double standard = A[p][q];
    //
    for (int j = 0; j < n; j++)
    {
        A[p][j] = A[p][j] / standard;//把主元化为1
    }
    //
    for (int j = 0; j < m; j++)
    {
        if (j != p)
        {
            double times = A[j][q];
            for (int k = 0; k < n; k++)
            {
                A[j][k] = A[j][k] - times * A[p][k];//将该行的每个元素减去主元所在行的该位置元素与该行主元所在位置的元素的积
            }
        }
    }
}

void swap(double** p1, double** p2)
{
    double* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


int main()
{
    cout << "请输入矩阵a的行数和列数：" << endl;
    cin >> m >> n;

    double** A = new double* [m]; //动态分配二维数组：行指针数组
    cout << "请输入矩阵a的元素：" << endl;
    for (int i = 0; i < m; i++)
    {
        A[i] = new double[n];
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];//矩阵A初始化
        }
    }

    //输出化简前的矩阵A
    cout << "您输入的矩阵为" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < m; i++)
    {
        int zy = zhuyuan(A, i);
        for (int j=i; zy != i; j++)
        {
            swap(&A[i],&A[j + 1]);
        }
        huajian(A, i, zy);
    }

    //输出化简后的矩阵A
    cout << "Hermite标准型：" << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }

    delete[]A;
    return 0;
}