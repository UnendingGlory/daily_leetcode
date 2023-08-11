import numpy as np
from collections import OrderedDict


class MatMul:
    def __init__(self, W, b) -> None:
        self.W, self.b = W, b
        self.dW, self.db = None, None
        self.x = None
    
    def forward(self, x):
        self.x = x
        return x @ self.W + self.b
    
    def backward(self, dout):
        # x of shape (m, n), w (n, p), dout (m, p)
        dx = dout @ self.W.T
        self.dW = self.x.T @ dout
        self.db = np.sum(dout, axis=0) # (p, 1)
        return dx


class Relu:
    def __init__(self) -> None:
        self.mask = None
    
    def forward(self, x):
        self.mask = (x <= 0)
        out = x.copy()
        out[self.mask] = 0
        return out
    
    def backward(self, dout):
        dout[self.mask] = 0
        return dout


class MSELoss:
    def __init__(self) -> None:
        self.y = self.y_hat = None
        
    def forward(self, y, y_hat):
        self.y = y
        self.y_hat = y_hat
        return np.mean(0.5 * (y - y_hat) ** 2)
    
    def backward(self, dout):
        return dout * (self.y_hat - self.y)


class ThreeLayerMLP:
    def __init__(self, input_size, hidden_size, output_size, init_std=0.001) -> None:
        self.params = {}
        self.params['W1'] = init_std * np.random.randn(input_size, hidden_size)
        self.params['b1'] = np.zeros(hidden_size)
        self.params['W2'] = init_std * np.random.randn(hidden_size, output_size)
        self.params['b2'] = np.zeros(output_size)
        
        self.layers = OrderedDict()
        self.layers['Matmul1'] = MatMul(self.params['W1'], self.params['b1'])
        self.layers['Relu'] = Relu()
        self.layers['Matmul2'] = MatMul(self.params['W2'], self.params['b2'])

        self.last_layer = MSELoss()

    def forward(self, x):
        for layer in self.layers.values():
            x = layer.forward(x)
        return x
    
    def backward(self, dout):
        layers = list(self.layers.values())
        layers.reverse()
        for layer in layers:
            dout = layer.backward(dout)
        
        grad = {}
        grad['W1'], grad['b1'] = self.layers['Matmul1'].dW, self.layers['Matmul1'].db
        grad['W2'], grad['b2'] = self.layers['Matmul2'].dW, self.layers['Matmul2'].db
        return grad


class SGD:
    def __init__(self, lr) -> None:
        self.lr = lr
    
    def update(self, param, grad):
        for key in param.keys():
            param[key] -= self.lr * grad[key]


X = np.random.randn(20, 784)
Y = np.random.randint(0, 2, size=(20, 1))
criterion = MSELoss()
lr = 0.001
epochs = 1000
opt = SGD(lr=lr)
net = ThreeLayerMLP(784, 64, 1)
for epoch in range(epochs):
    y_hat = net.forward(X)
    loss = criterion.forward(Y, y_hat)
    # acc = np.sum (y_hat == Y) / X.shape[0]
    
    dout = 1
    dout = criterion.backward(dout)
    grad = net.backward(dout)

    opt.update(net.params, grad)

    if epoch % 100 == 0:
        print("epoch {}, loss {:.5f}".format(epoch, loss))
