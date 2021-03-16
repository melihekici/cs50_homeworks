from cs50 import get_string


def main():
    
    # Gettin the reading text as input from the user
    txt = get_string("Text: ")
    
    # L is the number of letters and S is the number of sentences per 100 words
    L = (float(num_letters(txt)) / float(num_words(txt))) * 100
    S = (float(num_sentences(txt)) / float(num_words(txt))) * 100
    
    # Formula to be used to determine grade level of the text
    index = 0.0588 * L - 0.296 * S - 15.8
    
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(index + 0.5)}")


def num_letters(txt):  # Returns the number of alphabetic characters in the text
    counter = 0
    for i in range(len(txt)):
        if txt[i].lower() <= 'z' and txt[i].lower() >= 'a':
            counter += 1
    return counter
    
    
def num_sentences(txt):  # Returns the number of sentences in the text
    counter = 0
    for i in range(len(txt)):
        if txt[i] in ['.', '!', '?']:
            counter += 1
    return counter

    
def num_words(txt):  # Returns the number of words in the text
    counter = 1
    for i in range(len(txt)):
        if txt[i] == " ":
            counter += 1
    return counter

    
main()