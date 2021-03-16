from cs50 import get_int

while True:
    ccn = get_int("Number: ")
    if ccn > 0:
        break


# Main function
def main():
    # Initializing the variables
    counter = len(str(ccn))
    odds = 0
    evens = 0
    even_digit_total = 0

    for i in range(0, counter, 2):
        odds += getdigit(ccn, i)

    # Calculate sum of digits in the even numbered places
    for i in range(1, counter, 2):
        evens = getdigit(ccn, i)
        evens *= 2
        counter2 = number_length(evens)
        for k in range(1, counter2 + 1):
            even_digit_total += getdigit(evens, counter2 - k)

    last_digit = getdigit(even_digit_total + odds, 0)
    check_card(ccn, last_digit)


# Does logical checks to understand the type of the credit card
def check_card(ccn, last_digit):
    if last_digit != 0:
        print("1")
        print("INVALID")
    elif (getdigit(ccn, number_length(ccn) - 1) == 3) and (getdigit(ccn, number_length(ccn) - 2) == 4) or ((getdigit(ccn, number_length(ccn) - 2) == 7) and (number_length(ccn) == 15)):
        print("AMEX")
    elif (getdigit(ccn, number_length(ccn) - 1) == 4) and ((number_length(ccn) == 13) or (number_length(ccn) == 16)):
        print("VISA")
    elif (getdigit(ccn, number_length(ccn) - 1) == 5) and ((getdigit(ccn, number_length(ccn) - 2) >= 1) and (getdigit(ccn, number_length(ccn) - 2) <= 5)) and (number_length(ccn) == 16):
        print("MASTERCARD")
    else:
        print(2)
        print("INVALID")


def getdigit(ccn, n):  # Returns the nth digit of given number from the end
    return int(str(ccn)[len(str(ccn)) - n - 1])


def number_length(number):  # This function returns the length of a given number
    return len(str(number))


# Calling main function at the end because there is no prototyping in python
main()