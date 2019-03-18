import csv

head = ['devEUI    ', 'rssi      ', 'loraSNR   ', 'freq      ', 'dr        ', 'fCnt      ', 'fPort     ', 'data      ', 'datetime  ']

with open('gps_data.csv') as csvfile:
    readCSV = csv.reader(csvfile, delimiter=',')
    for row in readCSV:
        print(len(row))
        if(len(row) > 0):
            gp = row[7].split(',')
            print(gp)
            row.append(float(gp[0]) / 1000000)
            row.append(float(gp[1]) / 1000000)
            with open('gps_data_formatted.csv', 'a') as csvFile:
                writer = csv.writer(csvFile)
                writer.writerow(row)
            csvFile.close() 