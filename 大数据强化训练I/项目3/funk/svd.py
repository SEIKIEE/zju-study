import csv
import random
import math


class BiasLFM(object):

    def __init__(self, F, file_path, num, alpha=0.1, lmbd=0.1, max_iter=100):
        """
        :param rating_data: rating_data是[(user,[(anime,score)]]类型
        :param file_path: 训练文件
        :param num: 用户数量+1
        :param F: 隐因子个数
        :param alpha: 学习率
        :param lmbd: 正则化
        :param max_iter:最大迭代次数
        """
        self.F = F
        self.P = dict()
        self.Q = dict()
        self.bu = dict()
        self.bi = dict()
        self.alpha = alpha
        self.lmbd = lmbd
        self.max_iter = max_iter
        self.mu = 0.0
        self.path_p = 'p.txt'
        self.path_q = 'q.txt'
        self.rating_data = list()
        self.path = file_path
        self.rating_list = [list() for i in range(int(num))]
        self.item_list = list()

    def train(self):
        for step in range(self.max_iter):
            print('now at ' + str(step))
            """
            随机梯度下降法训练参数P和Q
            """
            for user, rates in self.rating_data:
                for item, rui in rates:
                    hat_rui = self.predict(user, item)
                    err_ui = rui - hat_rui
                    self.bu[user] += self.alpha * (err_ui - self.lmbd * self.bu[user])
                    self.bi[item] += self.alpha * (err_ui - self.lmbd * self.bi[item])
                    for f in range(self.F):
                        self.P[user][f] += self.alpha * (err_ui * self.Q[item][f] - self.lmbd * self.P[user][f])
                        self.Q[item][f] += self.alpha * (err_ui * self.P[user][f] - self.lmbd * self.Q[item][f])
            self.alpha *= 0.9 #每一次迭代步长要逐步缩小

    def predict(self, user, item):
        return sum(self.P[user][f] * self.Q[item][f] for f in range(self.F)) + self.bu[user] + self.bi[item] + self.mu

    """
    把矩阵存到本地
    """

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

    """
    从本地读一个矩阵
    """

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

    def initialize(self):
        """
        获得rating_data
        """
        with open(self.path, 'r') as f:
            reader = csv.reader(f)
            for row in reader:
                if int(row[2]) != -1:
                    if row[1] not in self.item_list:
                        self.item_list.append(row[1])  # 有用户评分的anime集合
                    self.rating_list[int(row[0])].append((row[1], float(row[2])))  # rating_list是[(anime,score),...]
        i = 0
        for rating in self.rating_list:
            if i != 0:
                self.rating_data.append((str(i), rating))
            i = i + 1
        """
        随机初始化PQ矩阵
        """
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
                self.bi[item] = 0
        self.mu /= cnt


if __name__ == '__main__':
    lfm = BiasLFM(5, '1.csv', 41)
    lfm.initialize()
    lfm.train()
    # 预测userID=3会给anime集合打的分数
    for item in lfm.item_list:
        print(item, lfm.predict('3', item))
