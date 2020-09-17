import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.model_selection.tests.test_split import digits

x_train, x_test, y_train, y_test = train_test_split(digits.data, digits.target, test_size=0.25, random_state=0)
print(x_train)
print(y_train)
def solve(fn):
    X = []
    Y = []
    with open(fn) as file:
        for idx,line in enumerate(file):
            if idx == 0:
                N = int(line)
            else:
                x,y = line.split()
                X.append(x)
                Y.append(y)
    print('\n'.join(X))
    print('\n'.join(Y))

solve("test1.in")