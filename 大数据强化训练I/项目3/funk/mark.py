import csv

read_path = '/Users/zjy/Desktop/raing_test.csv'
write_path = 'rating_clean.csv'
with open(read_path, 'r') as f_r:
    reader = csv.reader(f_r)
    with open(write_path, 'w') as f_w:
        f_csv = csv.writer(f_w)
        f_write_row = list()
        for row in reader:
            print(row)
            write_row = row
            if (int(row[2]) == -1):
                write_row[2] = '-1'
            elif (int(row[2]) > 8):
                write_row[2] = '1'
            else:
                write_row[2] = '0'
            f_write_row.append(write_row)
        f_csv.writerows(f_write_row)
    f_w.close()
f_r.close()
