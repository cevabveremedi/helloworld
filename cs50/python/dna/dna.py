import sys
import csv

if len(sys.argv) != 3:
    print("Invalid Command Line Arguments! \
Usage: python3 dna.py arg1 arg2")
    exit(1)
#1 csv
#2 txt
#sys.argv[1]
with open(sys.argv[2], "r") as file:
    for i in file:
        str = i

list = ["AGATC","TTTTTTCT","AATG","TCTAG","GATA","TATC","GAAA","TCTG"]
dna = {"AGATC": 0, "TTTTTTCT": 0, "AATG": 0, "TCTAG": 0, 
"GATA": 0, "TATC": 0, "GAAA": 0, "TCTG": 0}

for sqnce in list:
    strcpy = str
    while True:
        if len(strcpy) == 0:
            break
        index = strcpy.find(sqnce)
        if index == -1:
            break
        count = 0
        while True:
            try:
                word = strcpy[index:index+len(sqnce)]
            except IndexError:
                break
            if word == sqnce:
                count += 1
                index += len(sqnce)
            else:
                break
        if dna[sqnce] < count:
            dna[sqnce] = count
        strcpy = strcpy[index:]

with open(sys.argv[1]) as csvfile:
    reader = csv.DictReader(csvfile)
    for dict in reader:
        match = 1
        for key in dict:
            if key == 'name':
                name = dict[key]
                continue
            if int(dict[key]) != int(dna[key]):
                match = 0
                break
        if match == 1:
            break
if match == 1:
    print(name)
else:
    print("No match")