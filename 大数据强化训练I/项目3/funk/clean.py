import csv

path = 'rating.csv'
file = 'rating.data'
with open(path, 'r') as f:
    f_reader = csv.reader(f)
    with open(file, 'w') as t:
        for row in f_reader:
            t.write(row[0] + '\t' + row[1] + '\t' + row[2]+'\n')
f.close()
