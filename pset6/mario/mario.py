from cs50 import get_int

while True:
    # prompt user
    height = get_int("Height: ")

    # Make sure the number is more then 0 and less then 24
    if height < 24 and height >= 0:
        break;

# Print
for i in range(height):
    # First part
    for j in range(height - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")

    # Middle two spaces
    for l in range(2):
        print(" ", end="")

    # End part
    for m in range(i + 1):
        print("#", end="")

    print("\n", end="")