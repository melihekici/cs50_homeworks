from cs50 import get_float

while True:
    dollars = get_float("Change owed:")
    if dollars > 0:
        break

# Convert dollars to cent    
cent = int(dollars * 100)

# Calculate how many 25 cents in the given money and calculate remaining cents after 25 cents are removed
c_25 = int(cent / 25)
cent = cent - c_25 * 25

# Calculate how many 10 cents in the given money and calculate remaining cents after 10 cents are removed
c_10 = int(cent / 10)
cent = cent - c_10 * 10

# Calculate how many 5 cents in the given money and calculate remaining cents after 5 cents are removed
c_5 = int(cent / 5)
cent = cent - c_5 * 5

# The remaning are 1 cents
c_1 = int(cent)

# Print the total number of metals
print(c_25 + c_10 + c_5 + c_1)