import numpy as np
# 简单神经元的实现

# 输入
# batch (输入的数据)
a11 = -0.9
a12 = -0.5
a13 = -0.7

a21 = 0.3
a22 = -0.2
a23 = 0.6

a31 = 0.4
a32 = 0.9
a33 = 0.2

inputs = np.array([[a11, a12, a13],
                  [a21, a22, a23],
                  [a31, a32, a33]])

# 权重
w11 = 0.8
w12 = -0.4
w13 = 0.1

w21 = 0.4
w22 = -0.6
w23 = 0.2

weights = np.array([[w11, w21],
                    [w12, w22],
                    [w13, w23]])

# 偏置
b1 = 1


sum2 = np.dot(inputs, weights) + b1
print(sum2)

# 激活函数
# 输入的值大于0，输出为输入的值，否则输出为0
def activation_ReLU(x):
    return np.maximum(0, x)

print(activation_ReLU(sum2))