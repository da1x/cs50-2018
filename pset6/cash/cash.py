from cs50 import get_float


def main():
    # Get the user change
    change = 0
    coin = 0

    while True:
        change = get_float("Change: ")
        change = round(change * 100)

        if change > 0:
            break

    while change > 0:

        # Wokr out the change
        if change >= 25:
            coin += 1
            change -= 25
        elif change >= 10:
            coin += 1
            change -= 10
        elif change >= 5:
            coin += 1
            change -= 5
        elif change >= 1:
            coin += 1
            change -= 1

        # Print the result
        if change <= 0:
            break

    print(coin)


if __name__ == '__main__':
    main()