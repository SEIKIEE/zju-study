import csv

read_path = '/Users/zjy/Desktop/rating.csv'
write_path = 'rating_cut.csv'
cut_num = 350

with open(read_path, 'r') as f:
    reader = csv.reader(f)
    with open(write_path, 'w') as f_w:
        writer = csv.writer(f_w)
        for row in reader:
            if int(row[0]) < cut_num:
                writer.writerow(row)
            else:
                break
    f_w.close()
f.close()
