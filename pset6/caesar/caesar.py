from cs50 import get_string
import sys


def main():

    letter = ''
    cipherletter = ''
    plainText = ''
    key = 0

    if len(sys.argv) == 2 and sys.argv[1] != "":
        key = int(sys.argv[1])

        while plainText == "":
            plainText = get_string("plaintext: ")

    else:
        sys.exit(1)


    print("ciphertext: ", end = "")
    for i in range(len(plainText)):

        letter = plainText[i]

        if letter.isalpha():
            if letter.isupper():
                letter = (((ord(letter) - 65) + key) % 26) + 65
                cipherletter += chr(letter)

            elif letter.islower():
                letter = (((ord(letter) - 97) + key) % 26) + 97
                cipherletter += chr(letter)
        else:
            cipherletter += letter

        if len(cipherletter) == len(plainText):
            print(cipherletter)

if __name__ == '__main__':
    main()