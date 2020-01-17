# coding:utf-8

import random
import math
import csv


class SVDPP(object):
    '''
    实例化一个SVD++
    '''

    def __init__(self, F, file_path, num, alpha=0.1, lmbd=0.1, max_iter=100):
        self.F = F
        self.P = dict()
        self.Q = dict()
        self.Y = dict()
        self.bu = dict()
        self.bi = dict()
        self.alpha = alpha
        self.lmbd = lmbd
        self.max_iter = max_iter
        self.mu = 0.0
        self.path_p = 'p.txt'
        self.path_q = 'q.txt'
        self.path_y = 'y.txt'
        self.rating_data = list()
        self.path = file_path
        self.rating_list = [list() for i in range(int(num))]
        self.item_list = list()

    '''
    训练模型
    '''

    def train(self):
        '''
        随机梯度下降法训练参数P和Q
        '''
        for step in range(self.max_iter):
            print('now at ' + str(step))
            for user, rates in self.rating_data:
                if len(rates) == 0:
                    continue
                z = [0.0 for f in range(self.F)]
                for item, _ in rates:
                    for f in range(self.F):
                        z[f] += self.Y[item][f]
                ru = 1.0 / math.sqrt(1.0 * len(rates))
                s = [0.0 for f in range(self.F)]
                for item, rui in rates:
                    hat_rui = self.predict(user, item, rates)
                    err_ui = rui - hat_rui
                    self.bu[user] += self.alpha * (err_ui - self.lmbd * self.bu[user])
                    self.bi[item] += self.alpha * (err_ui - self.lmbd * self.bi[item])
                    for f in range(self.F):
                        s[f] += self.Q[item][f] * err_ui
                        self.P[user][f] += self.alpha * (err_ui * self.Q[item][f] - self.lmbd * self.P[user][f])
                        self.Q[item][f] += self.alpha * (
                                err_ui * (self.P[user][f] + z[f] * ru) - self.lmbd * self.Q[item][f])
                for item, _ in rates:
                    for f in range(self.F):
                        self.Y[item][f] += self.alpha * (s[f] * ru - self.lmbd * self.Y[item][f])
            self.alpha *= 0.9  # 每次迭代步长要逐步缩小

    '''
    预测用户user对物品item的评分
    '''

    def predict(self, user, item, ratedItems):
        z = [0.0 for f in range(self.F)]
        for ri, _ in ratedItems:
            for f in range(self.F):
                z[f] += self.Y[ri][f]
        return sum(
            (self.P[user][f] + z[f] / math.sqrt(1.0 * len(ratedItems))) * self.Q[item][f] for f in range(self.F)) + \
               self.bu[user] + self.bi[item] + self.mu

    '''
    将模型存到本地
    '''

    def store(self):
        with open(self.path_p, 'w') as f_p:
            for d in self.P:
                f_p.write(d)
                for v in self.P[d]:
                    f_p.write(' ' + str(v))
                f_p.writelines('\n')
        f_p.close()

        with open(self.path_q, 'w') as f_q:
            for d in self.Q:
                f_q.write(d)
                for v in self.Q[d]:
                    f_q.writelines(' ' + str(v))
                f_q.writelines('\n')
        f_q.close()

        with open(self.path_y, 'w') as f_y:
            for d in self.Y:
                f_y.write(d)
                for v in self.Y[d]:
                    f_y.writelines(' ' + str(v))
                f_y.writelines('\n')
        f_y.close()

    '''
    将本地模型读入内存
    '''

    def get(self):
        with open(self.path_p, 'r') as f_p:
            f_p_reader = csv.reader(f_p)
            for row in f_p_reader:
                items = row[0].split(' ')
                self.P[items[0]] = list(map(float, items[1:]))
        f_p.close()

        with open(self.path_q, 'r') as f_q:
            f_q_reader = csv.reader(f_q)
            for row in f_q_reader:
                items = row[0].split(' ')
                self.Q[items[0]] = list(map(float, items[1:]))
        f_q.close()

        with open(self.path_p, 'r') as f_y:
            f_y_reader = csv.reader(f_y)
            for row in f_y_reader:
                items = row[0].split(' ')
                self.Y[items[0]] = list(map(float, items[1:]))
        f_y.close()

    '''
    初始化user-item矩阵和模型矩阵
    '''

    def initialize(self):
        '''获取用户物品评分矩阵'''
        with open(self.path, 'r') as f:
            reader = csv.reader(f)
            for row in reader:
                if int(row[2]) != -1:
                    if row[1] not in self.item_list:
                        self.item_list.append(row[1])
                    self.rating_list[int(row[0])].append((row[1], float(row[2])))
        i = 0
        for rating in self.rating_list:
            if i != 0:
                self.rating_data.append((str(i), rating))
            i = i + 1
        '''随机初始化矩阵P、Q、Y'''
        cnt = 0
        for user, rates in self.rating_data:
            self.P[user] = [random.random() / math.sqrt(self.F)
                            for x in range(self.F)]
            self.bu[user] = 0
            cnt += len(rates)
            for item, rate in rates:
                self.mu += rate
                if item not in self.Q:
                    self.Q[item] = [random.random() / math.sqrt(self.F)
                                    for x in range(self.F)]
                if item not in self.Y:
                    self.Y[item] = [random.random() / math.sqrt(self.F)
                                    for x in range(self.F)]
                self.bi[item] = 0
        self.mu /= cnt


if __name__ == '__main__':
    lfm = SVDPP(5, '1.csv', 41)
    lfm.initialize()
    lfm.train()
    for item in lfm.item_list:
        print(item, lfm.predict('3', item, lfm.rating_list[3]))  # 计算用户A对各个物品的喜好程度
