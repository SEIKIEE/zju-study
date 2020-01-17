import csv

path = 'rating.csv'
file = 'clean.csv'
with open(path, 'r') as f:
    f_reader = csv.reader(f)
    with open(file, 'w') as t:
        for row in f_reader:
            if (int(row[2]) != -1):
                t.write(row[0] + ',' + row[1] + ',' + row[2] + '\n')
    t.close()
f.close()
