from cs50 import get_int
import sys

def main():
    sumForEven = 0
    sumForOdd = 0
    num1 = 0
    num2 = 0
    totalSum = 0
    beforeTotalSum = 0
    tempCounter = 0

    CardNum = get_int("Number: ")
    counter = len(str(CardNum))
    tempCounter = counter

    while CardNum > 0:
        num2 = num1
        num1 = CardNum % 10

        if tempCounter % 2 == 1:
            sumForEven += num1
        else:
            beforeTotalSum = num1 * 2
            sumForOdd += (beforeTotalSum % 10) + (beforeTotalSum // 10);

        CardNum //= 10
        tempCounter -= 1
        if tempCounter == 0:
            totalSum = sumForEven + sumForOdd
            firstTwoNum = (num1 * 10) + num2

    if counter == 15 and firstTwoNum == 34 or firstTwoNum == 37:
        print("AMEX")
    elif counter == 16 and firstTwoNum >= 51 and firstTwoNum <= 55:
        print("MASTERCARD")
    elif (counter == 13 or counter == 16) and num1 == 4:
        print("VISA")
    else:
        print("INVALID")

if __name__ == '__main__':
    main()