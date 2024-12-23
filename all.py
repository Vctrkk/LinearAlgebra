import numpy as np

print("请输入学号")
id = input()
id_num=[int(x) for x in id]

#生成对应矩阵
num_list = []
temp = []
exp = 1
while True:
    for i in range(len(id_num)):
        temp = [int(x) for x in str(id_num[i] ** exp)]
        num_list += temp
    exp += 1
    if len(num_list) > 169:
        break
num_list = num_list[:169]
A = np.array(num_list).reshape(13, 13)
print("\n生成的矩阵A=\n", A)

#行列式
print("\n行列式|A|=", np.linalg.det(A))

#Hermite标准型
def hermite(A):
    matrix = np.copy(A)
    rank = np.linalg.matrix_rank(matrix)
    n = matrix.shape[0]
    i = 0#从上到下依次归1，i是正在归1的行
    for j in range(n):#从左到右依次作hermite标准型，j是正在归1的列
        for h in range(i, n):#把非零行换到上面作为基准，h是可以活动的行
            if matrix[h, j]!=0:
                #matrix[h, :], matrix[i, :] = matrix[i, :], matrix[h, :]# 这一步有bug！只会把i行赋值给h行而不会把h行赋值给i行！以后再改
                temp=np.copy(matrix[i, :])
                matrix[i, :]=matrix[h, :]
                matrix[h, :]=temp
                break
        if matrix[i, j] != 0:
            matrix[i, :] = matrix[i, :] / matrix[i, j]
            for h in range(n):#把各行按照非零元素变为0，h是活动行
                if matrix[h, j]!=0:
                    if i != h:
                        matrix[h, :] = matrix[h, :] - matrix[i, :] * matrix[h, j]
            i+=1
    return matrix

print("\nHermite标准型=\n", hermite(A))

#通解
def general_solution(A):
    matrix = np.copy(A)
    rank = np.linalg.matrix_rank(matrix)
    n = matrix.shape[0]
    i = 0#从上到下依次归1，i是正在归1的行
    j_set = []
    for j in range(n):#从左到右依次作hermite标准型，j是正在归1的列
        for h in range(i, n):#把非零行换到上面作为基准，h是可以活动的行
            if matrix[h, j]!=0:
                temp=np.copy(matrix[i, :])
                matrix[i, :]=matrix[h, :]
                matrix[h, :]=temp
                break
        if matrix[i, j] != 0:
            matrix[i, :] = matrix[i, :] / matrix[i, j]
            for h in range(n):#把各行按照非零元素变为0，h是活动行
                if matrix[h, j]!=0:
                    if i != h:
                        matrix[h, :] = matrix[h, :] - matrix[i, :] * matrix[h, j]
            i+=1
            j_set.append(j)
    i_set = [x for x in range(n) if x not in j_set]#自由元
    order = j_set + i_set
    ordered_matrix = matrix[:, order]
    gen_sol = np.zeros((n, n-rank))
    gen_sol = -ordered_matrix[:, -(n-rank):]
    gen_sol[rank:, :] = np.eye(n-rank)
    return gen_sol

print("\n通解=\n", general_solution(A) if np.linalg.det(A) == 0 else "零向量")

#列向量组的极大无关组
def maximal_independent_set(A):
    matrix = np.copy(A)
    rank = np.linalg.matrix_rank(matrix)
    n = matrix.shape[0]
    i = 0#从上到下依次归1，i是正在归1的行
    j_set = []
    for j in range(n):#从左到右依次作hermite标准型，j是正在归1的列
        for h in range(i, n):#把非零行换到上面作为基准，h是可以活动的行
            if matrix[h, j]!=0:
                temp=np.copy(matrix[i, :])
                matrix[i, :]=matrix[h, :]
                matrix[h, :]=temp
                break
        if matrix[i, j] != 0:
            matrix[i, :] = matrix[i, :] / matrix[i, j]
            for h in range(n):#把各行按照非零元素变为0，h是活动行
                if matrix[h, j]!=0:
                    if i != h:
                        matrix[h, :] = matrix[h, :] - matrix[i, :] * matrix[h, j]
            i+=1
            j_set.append(j)
    return np.array([A[:, j] for j in j_set])# 这里会报错，TypeError: list indices must be integers or slices, not tuple，但不知道怎么改，AI说不会

print("\n列向量组的极大无关组=\n", maximal_independent_set(A))

#Schmidt正交化
print("\nSchmidt正交化的结果=\n", np.linalg.qr(A)[0])

#正、负惯性指数
M = A + A.T
eig_val, eig_vec = np.linalg.eig(M)
p_inertia_idx = n_inertia_idx = 0
for i in range(len(eig_val)):
    if eig_val[i] > 0:
        p_inertia_idx += 1
    elif eig_val[i] < 0:
        n_inertia_idx += 1
print("\n正惯性指数=", p_inertia_idx, "，负惯性指数=", n_inertia_idx)