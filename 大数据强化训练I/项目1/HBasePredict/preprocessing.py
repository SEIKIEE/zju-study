#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 27 19:35:33 2019

@author: zjy
"""

import sys

"""
csv_path_train = sys.argv[1]
csv_path_after_preprocess = sys.argv[2]
data_path_train = sys.argv[3]
"""

csv_path_train = r'/Users/zjy/Desktop/大数据强化训练I/项目1/HBasePredict/train.csv'
csv_path_after_preprocess = r'/Users/zjy/Desktop/大数据强化训练I/项目1/HBasePredict/'
data_path_train = r'/Users/zjy/Desktop/大数据强化训练I/项目1/HBasePredict/1'

#创建CSV文件
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

create_csv(csv_path_train)
write_part_csv(data_path_train, csv_path_train, "")

# 读CSV
import pandas as pd
def read_data(filepath):
    data = pd.read_csv(filepath, usecols=[0, 1], encoding='latin-1')
    data.columns = ['label', 'content']
    return data

import re
#import nltk
#nltk.download()
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
                print(word)
        new_content = " ".join(lemmas_sent)
        raw_data.iloc[i].content = new_content

train_data = read_data(csv_path_train)
preprocess(train_data)

print(train_data)
train_data.to_csv(csv_path_after_preprocess)