import numpy as np

# Sigmoid 激活函数及其导数
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# sigmoid导数 f'(x) = f(x) * （1 - f(x))
def sigmoid_derivative(x):
    return x * (1 - x)

# 输入数据，修改为(30, 28 * 28)
X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])

# 真实标签
y = np.array([[0], [1], [1], [0]])
print(y.shape)
# 设置超参数
input_size = 2 # 784
hidden_size = 4
output_size = 1
learning_rate = 0.1
epochs = 10000

# 初始化权重和偏置
np.random.seed(0)
weights_input_hidden = np.random.normal(size=(input_size, hidden_size)) # (2, 4)
weights_hidden_output = np.random.normal(size=(hidden_size, output_size)) # (4, 1)
bias_hidden = np.zeros(shape=(1, hidden_size))
bias_output = np.zeros(shape=(1, output_size))


# https://zhuanlan.zhihu.com/p/621327569
# 训练模型
for epoch in range(epochs):
    # 前向传播
    hidden_layer = (X @ weights_input_hidden) + bias_hidden
    hidden_layer_act = sigmoid(hidden_layer)
    output_layer = (hidden_layer_act @ weights_hidden_output) + bias_output
    
    y_hat = sigmoid(output_layer)
    
    # 计算损失
    loss = np.mean(0.5 * (y - y_hat) ** 2)
    
    # 反向传播
    output_error = y - y_hat # 对 loss求导, size of (4, 1)
    output_delta = output_error * sigmoid_derivative(y_hat) # 链式法则，激活函数求导，矩阵点乘, shape of (4, 1)

    hidden_layer_error = output_delta @ weights_hidden_output.T # shape of (4, 1) @ (1, 4)
    hidden_layer_delta = hidden_layer_error * sigmoid_derivative(hidden_layer_act) # shape of (4, 4)

    # 更新权重和偏置，为什么这里是加号？
    weights_hidden_output += learning_rate * (hidden_layer_act.T @ output_delta)
    weights_input_hidden += learning_rate * (X.T @ hidden_layer_delta)

    bias_output += np.sum(output_delta, axis=0, keepdims=True) * learning_rate
    bias_hidden += np.sum(hidden_layer_delta, axis=0, keepdims=True) * learning_rate

    if epoch % 1000 == 0:
        print(f'Epoch: {epoch}, Loss: {loss}')

# 测试模型
test_data = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
test_predictions = sigmoid(np.dot(sigmoid(np.dot(test_data, weights_input_hidden) + bias_hidden),
                                  weights_hidden_output) + bias_output)

print("\nTest Predictions:")
print(test_predictions)
