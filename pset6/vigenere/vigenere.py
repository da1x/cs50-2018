from cs50 import get_string
import sys


def main():

    letter = ''
    cipherletter = ''
    plainText = ''
    key = 0
    k = 0

    keyword = ''
    keyLen = 0

    if len(sys.argv) != 2 or sys.argv[1].isalpha == 1:
        print("Usage: ./vigenere k")
        sys.exit(1)
    else:
        keyword = sys.argv[1]
        keyLen = len(keyword)
        for i in range(keyLen):
            if keyword[i].isalpha() == False:
                print("Non-alphabetical characters are not allow")
                sys.exit(1)

        while plainText == "":
            plainText = get_string("plaintext: ")

    print("ciphertext: ", end="")
    for i in range(len(plainText)):

        key = ord(keyword[k % keyLen].lower()) - 97

        letter = plainText[i]

        if letter.isalpha():
            if letter.isupper():
                letter = (((ord(letter) - 65) + key) % 26) + 65
                cipherletter += chr(letter)
                k += 1

            elif letter.islower():
                letter = (((ord(letter) - 97) + key) % 26) + 97
                cipherletter += chr(letter)
                k += 1
        else:
            cipherletter += letter

        if len(cipherletter) == len(plainText):
            print(cipherletter)


if __name__ == '__main__':
    main()