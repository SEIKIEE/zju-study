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

true_positive = 0
true_negative = 0
false_positive = 0
false_negative = 0

d = dict()  # dictionary
probabilityPath = 'Probability'
resultPath = 'result.csv'
testPath = '_test.csv'
f = open(probabilityPath)  # open probability
for line in f:
    # 否则会out of range
    if 0 < line.split().__len__():
        key = line.split()[0]
        value = float(line.split()[1])
        d[key] = value
count = 0
with open(resultPath, 'w', newline='') as f:
    resultWrite = csv.writer(f)
    resultWrite.writerow(["documentID", "class"])
    document = csv.reader(open(testPath))
    for l in document:
        count += 1
        spamProbability = 0.0
        hamProbability = 0.0
        for word in l[1].split():
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
            if l[0] == 'spam':
                true_positive += 1
            else:
                false_positive += 1
            print(1)
        else:
            if l[0] == 'spam':
                false_negative += 1;
            else:
                true_negative += 1
            resultWrite.writerow([l[0], 0])
            print(0)
f.close()

print("count:")
print(count)
print("true positive:")
print(true_positive)
print("true negative:")
print(true_negative)
print("false positive:")
print(false_positive)
print("false negative")
print(false_negative)
print("Precision:")
print(true_positive / (true_positive + false_negative))
print("Recall:")
print(true_positive / (true_positive + false_positive))
