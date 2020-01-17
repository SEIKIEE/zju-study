from builtins import len

csv_path_test = 'C:\\Users\\akiha\Documents\\bigdata\dataset\\test.csv'
csv_path_after_preprocess = 'C:\\Users\\akiha\Documents\\bigdata\dataset\\_test.csv'

data_path_train_spam = r'C:\Users\akiha\Documents\bigdata\dataset\test\spam'
data_path_train_ham = r'C:\Users\akiha\Documents\bigdata\dataset\test\ham'

# 创建CSV文件
import csv


def create_csv(csv_path):
    with open(csv_path, 'w', newline='') as f:
        csv_write = csv.writer(f)
        csv_head = ["label", "content"]
        csv_write.writerow(csv_head)
    f.close()


import os


def write_part_csv(data_path, csv_path, label):
    for info in os.listdir(data_path):
        domain = os.path.abspath(data_path)
        info = os.path.join(domain, info)
        info = open(info, 'rb')
        text = info.read()
        text = text.replace(b'\r\n', b' ')
        with open(csv_path, 'a+', newline='') as f:
            csv_write = csv.writer(f)
            data_row = [label, text]
            csv_write.writerow(data_row)
        info.close
        f.close


create_csv(csv_path_test)
write_part_csv(data_path_train_spam, csv_path_test, "spam")
# write_part_csv(data_path_train_ham, csv_path_test, "ham")

# 读CSV
import pandas as pd


def read_data(filepath):
    data = pd.read_csv(filepath, usecols=[0, 1], encoding='latin-1')
    data.columns = ['label', 'content']
    return data


import re
# import nltk
# nltk.download()
from nltk import word_tokenize, pos_tag
from nltk.stem import WordNetLemmatizer
from nltk.corpus import wordnet, stopwords


# 获取单词的词性
def get_wordnet_pos(tag):
    if tag.startswith('J'):
        return wordnet.ADJ
    elif tag.startswith('V'):
        return wordnet.VERB
    elif tag.startswith('N'):
        return wordnet.NOUN
    elif tag.startswith('R'):
        return wordnet.ADV
    else:
        return None


def preprocess(raw_data):
    stop = set(stopwords.words('english'))
    stop.add("subject")
    for i in range(raw_data.shape[0]):
        # 筛选英文单词
        tokens = re.findall('[A-Za-z]+', raw_data.iloc[i].content)
        tagged_sent = pos_tag(tokens)
        wnl = WordNetLemmatizer()
        lemmas_sent = []
        for tag in tagged_sent:
            wordnet_pos = get_wordnet_pos(tag[1]) or wordnet.NOUN
            word = wnl.lemmatize(tag[0], pos=wordnet_pos)
            word = word.lower()
            if word.__len__() >= 3 and word not in stop:
                lemmas_sent.append(word)
        new_content = " ".join(lemmas_sent)
        raw_data.iloc[i].content = new_content


train_data = read_data(csv_path_test)
preprocess(train_data)
train_data.to_csv(csv_path_after_preprocess)


def trans_into_txt(path):
    f = open(path, 'a')
    for i in range(train_data.shape[0]):
        new_txt_content = str(train_data.iloc[i].label) + ":" + str(i) + "\t" + str(train_data.iloc[i].content)
        f.write(new_txt_content)
        f.write("\n")
    f.close()


import math
import csv
import sys

# deal with the csv is too big
maxInt = sys.maxsize
decrement = True
while decrement:
    decrement = False
    try:
        csv.field_size_limit(maxInt)
    except OverflowError:
        maxInt = int(maxInt / 10)
        decrement = True

d = dict()  # dictionary
probabilityPath = 'Probability'
resultPath = 'result.csv'
testPath = csv_path_after_preprocess
f = open(probabilityPath)  # open probability
for line in f:
    # 否则会out of range
    if 0 < line.split().__len__():
        key = line.split()[0]
        value = float(line.split()[1])
        d[key] = value

with open(resultPath, 'w', newline='') as f:
    resultWrite = csv.writer(f)
    resultWrite.writerow(["documentID", "class"])
    document = csv.reader(open(testPath))
    for l in document:
        if l[0] == '':
            continue
        spamProbability = 0.0
        hamProbability = 0.0
        if len(l) != 2:
            for word in l[2].split():
                if d.get('spam:' + word) is not None:
                    spamProbability += math.log(d['spam:' + word])
                else:
                    spamProbability += math.log(d['spam'])
                if d.get('ham:' + word) is not None:
                    hamProbability += math.log(d['ham:' + word])
                else:
                    hamProbability += math.log(d['ham'])
            if spamProbability > hamProbability:
                resultWrite.writerow([l[0], 1])
                print(1)
            else:
                resultWrite.writerow([l[0], 0])
                print(0)
        else:
            resultWrite.writerow([l[0], 1])
            print(1)
    f.close()
