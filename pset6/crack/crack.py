import sys
from crypt import crypt
from string import ascii_letters

def main():

    letter = ''.join(str(e) for e in ascii_letters)
    key = ''
    salt = ''

    if len(sys.argv) != 2:
        print("Wrong input data")
        return 1
    else:
        hashVal = sys.argv[1]

    salt = hashVal[0]
    salt += hashVal[1]

    for i in range(52):
        key = letter[i]
        #keyStr = ''.join(str(e) for e in key)

        if crypt(key, salt) == hashVal:
            print(key)
            sys.exit()

    for i in range(52):
        for j in range(52):
            key = letter[i]
            key += letter[j]
            keyStr = ''.join(str(e) for e in key)

            if crypt(keyStr, salt) == hashVal:
                print(keyStr)
                sys.exit()

    for i in range(52):
        for j in range(52):
            for k in range(52):
                key = letter[i]
                key += letter[j]
                key += letter[k]
                keyStr = ''.join(str(e) for e in key)

                if crypt(keyStr, salt) == hashVal:
                    print(keyStr)
                    sys.exit()

    for i in range(52):
        for j in range(52):
            for k in range(52):
                for l in range(52):
                    key = letter[i]
                    key += letter[j]
                    key += letter[k]
                    key += letter[l]
                    keyStr = ''.join(str(e) for e in key)

                    if crypt(keyStr, salt) == hashVal:
                        print(keyStr)
                        sys.exit()


    print("No password match")
    return 0

if __name__ == '__main__':
    main()