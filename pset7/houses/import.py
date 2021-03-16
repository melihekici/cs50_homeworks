from cs50 import SQL
import sys
import csv

# if the user enters more than 1 argument or enters no argument then the program will yield an error and exits
if len(sys.argv) != 2:
    print("Please enter only one argument")
    sys.exit()

# Access students database and assign it to variable db
db = SQL("sqlite:///students.db")

# Initialize the iterator i to 1 that will be placed to the table as index
i = 1

# Open csv file that contains list of students as file and read the file as reader
with open(sys.argv[1]) as file:
    reader = csv.reader(file)
    
    # For each row in the file, check if the student has a middle name and then split full name into first, middle and last name
    for row in reader:
        name = None
        if len(row[0].split(" ")) == 3:
            name = row[0].split(" ")[0]
            middle = row[0].split(" ")[1]
            surname = row[0].split(" ")[2]
            house = row[1]
            birth = row[2]
            db.execute(
                f"INSERT INTO students (id, first, middle, last, house, birth) VALUES ({i}, \"{name}\", \"{middle}\" , \"{surname}\", \"{house}\", \"{birth}\");")
            i += 1
        elif len(row[0].split(" ")) == 2:
            name = row[0].split(" ")[0]
            surname = row[0].split(" ")[1]
            house = row[1]
            birth = row[2]
            db.execute(
                f"INSERT INTO students (id, first, last, house, birth) VALUES ({i}, \"{name}\", \"{surname}\", \"{house}\", \"{birth}\");")
            i += 1