from cs50 import SQL
import sys
import csv

# if the user enters more than 1 argument or enters no argument then the program will yield an error and exits
if len(sys.argv) != 2:
    print("Please enter only one argument")
    sys.exit()
    
# Access students database and assign it to variable db 
db = SQL("sqlite:///students.db")

# Execute sql command to get the list of students from specified house then assign it to a table
stud_table = db.execute(
    f"SELECT * FROM (SELECT first, middle, last, house, birth FROM students WHERE house = \"{sys.argv[1]}\" ORDER BY first) ORDER BY last")

# Print the results in required format
for student in stud_table:
    print(student['first'], end=" ")
    if student['middle'] != None:
        print(student['middle'], end=" ")
    print(student['last'], end=", ")
    print(f"born {student['birth']}")