import numpy as np

class NearestNeighbor:
    def __init__(self):
        self.X_train = None
        self.y_train = None

    def train(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, X_test):
        num_test = X_test.shape[0]
        y_pred = np.zeros(num_test, dtype=self.y_train.dtype)

        for i in range(num_test):
            # L1距离计算
            distances = np.sum(np.abs(self.X_train - X_test[i, :]), axis=1)
            # 找到最近的训练样本索引
            min_index = np.argmin(distances)
            y_pred[i] = self.y_train[min_index]

        return y_pred

# 创建一个简单的数据集
X_train = np.array([[1, 2], [2, 3], [3, 4], [4, 5]])
y_train = np.array([0, 1, 0, 1])
X_test = np.array([[2, 3], [4, 4]])

# 初始化并训练最近邻模型
nn = NearestNeighbor()
nn.train(X_train, y_train)

# 预测测试集数据
y_pred = nn.predict(X_test)
print("预测结果:", y_pred)
