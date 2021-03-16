import csv
import sys

# Initializing csv_table and STR_list as empty tables.
csv_table = []
STR_list = []

# Opening csv file given by the imput and import data from csv to variable csv_table
with open(f"./{sys.argv[1]}", "r") as file:
    reader = csv.reader(file, delimiter=",")
    for row in reader:
        csv_table.append(row)

# Opening text file given by the input and import dna sequence from txt file to variable dna
dna_txt = open(f"./{sys.argv[2]}", "r")
dna = dna_txt.read()

# The column headers of the csv_table contains STR list. Extract all STR's from the table and put it into STR_list variable
STR_list = [csv_table[0][1::]]

# Initialize an empty list that will show how many consecutive times STR existed in the dna for each STR in the columns
STR_counts = []

# Calcutaling STR_counts for each STR type for given dna sequence
for STR in STR_list[0]:
    count = 0
    max = 0
    i = 0
    while i < len(dna)-len(STR) + 1:
        if count > max:
            max = count
        if dna[i:i+len(STR)] == STR:
            count += 1
            i = i + len(STR) - 1
        else:
            count = 0
        i += 1
    STR_counts.append(max)

# Place STR_counts numbers to STR_list which will now show from which STR how many consecutive times it has repeated
STR_list.append(STR_counts)

# Closing the txt file
dna_txt.close()

# Converting the numbers in the STR_list from integer to string for consistency
STR_list[1] = [str(i) for i in STR_list[1]]

# Checking if there are any persons with the same STR_counts and print the result
for row in csv_table:
    if row[1::] == STR_list[1]:
        print(row[0])
        sys.exit()
print("No match")
