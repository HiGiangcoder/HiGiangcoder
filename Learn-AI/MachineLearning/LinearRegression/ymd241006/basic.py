import numpy as np
import pandas
import matplotlib.pyplot as plt

# tao data
def MakeData():
    # tao ra mot array [-69, -68, -67, ..., 68, 69]
    x = np.arange(-69, 69, 1)
    numData = len(x)
    noise = np.random.normal(0, 10, numData)
    y = 6 * x + 9 + noise
    return [x, y]

trainingData = MakeData()

numData = len(trainingData[0])
ones = np.ones((1, numData))
X = np.concatenate((ones, [trainingData[0]]))
Y = np.array([list(trainingData[1])])


# khoi tao tham so: theta, alpha, eps
theta = np.array([[1.0], [1.0]])
alpha = 10
eps = 10**-1

def predict(i):
    result = theta.T @ X[:, i:i+1]
    return result[0][0]


def MSError():
    numerror = 0.0
    for i in range(numData):
        numerror += (predict(i) - Y[0][i]) ** 2
    numerror /= numData
    return numerror

plt.plot(X[1], Y[0], "ro")


# Lap de toi uu ham MSE
while True:
    nabla = (X @ (Y - theta.T @ X).T) / numData

    theta += alpha * nabla

    # truc quan hoa qua trinh
    x_vis = [-69, 69]
    y_vis = x_vis * theta[1] + theta[0]
    plt.plot(x_vis, y_vis)
    plt.pause(0.01)

    newnabla = (X @ (Y - theta.T @ X).T) / numData

    if newnabla[0][0] * nabla[0][0] < 0: 
        alpha /= 10

    if abs(newnabla[0][0]) < eps and abs(newnabla[1][0]) < eps: break

plt.clf()
plt.plot(X[1], Y[0], "ro")

x_vis = [-69, 69]
y_vis = x_vis * theta[1] + theta[0]
plt.plot(x_vis, y_vis)

plt.show()
    
print(theta)
