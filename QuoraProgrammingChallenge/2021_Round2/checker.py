#!/usr/bin/env python3

import lightgbm as lgb
import numpy as np
import sys
from sklearn.metrics import roc_auc_score

inp = sys.argv[1]
tes = sys.argv[2]
oup = sys.argv[3]


X_train = []
y_train = []
with open(inp) as f:
    K,D,M = (int(x) for x in f.readline().strip().split())
    for _ in range(K):
        parts = f.readline().strip().split()        
        X_train.append(list(float(x) for x in parts))
    for _ in range(K):
        y_train.append(int(f.readline().strip()))


X_test = []
y_test = []
with open(tes) as f:
    lines = f.readlines()
    for line in lines:
        parts = line.strip().split()
        if len(parts) > 1:
            X_test.append(list(float(x) for x in parts))
        elif len(parts) == 1:
            y_test.append(int(parts[0]))
X_train_mod = X_train.copy()
y_train_mod = y_train.copy()


with open(oup) as f:
    lines = f.readlines()
    split_lines = [l.strip().split() for l in lines]
    X_train_mod.extend([[float(x) for x in l] for l in split_lines[:M]])
    y_train_mod.extend([int(x[0]) for x in split_lines[M:]])
    
    
def train_and_eval(X, y, X_test, y_test):
    train_data = lgb.Dataset(np.array(X), label=np.array(y))
    num_round = 10
    param = {'num_leaves': 15, 'objective': 'binary', 'num_threads':1, 'verbosity': -1}
    param['metric'] = 'auc'
    bst = lgb.train(param, train_data, num_round)
    
    y_hat = bst.predict(X_test)
    
    return roc_auc_score(y_test, y_hat)

before_auc = train_and_eval(X_train, y_train, X_test, y_test)
after_auc = train_and_eval(X_train_mod, y_train_mod, X_test, y_test)
res = min(1,max(0, (before_auc - after_auc)*10))
print(format(res, '0.5f'))