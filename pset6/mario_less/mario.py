from cs50 import get_int

# Creating an infinite loop here and if the user gives a proper input the loop will break
while True:
    n = get_int("Height: ")
    if n > 0 and n <= 8:
        break
    print("Please enter a positive integer between 1 and 8.")

# Creating blocks
if n > 0:
    for i in range(n):
        print(" " * (n - i - 1), end="")
        print("#" * (i + 1))