from cs50 import get_string, get_int
import re
import operator

while True:
    cc = get_string("Number: ")
    length = len(cc)
    # check correct number of digits
    number = re.findall('[0-9]+', cc)
    # exit if number was found
    if number:
        break

number = str(number[0])
firstDigit = int(number[0])

digitsTimesTwo = []
for i in range(length - 2, -1, -2):
    temp = int(number[i]) * 2

    # if single digit, store in list as-is
    if temp < 10:
        digitsTimesTwo.append(temp)
    else:
        temp = str(temp)
        # split integer into its digits to store in list
        for j in range(len(temp)):
            temp2 = int(temp[j])
            digitsTimesTwo.append(temp2)

digits = []
for i in range(length - 1, -1, -2):
    temp = int(number[i])
    digits.append(temp)

finalSum = int(sum(digitsTimesTwo)) + int(sum(digits))
result = str(finalSum % 10)

if result[-1] == '0':
    if length == 15:
        print("AMEX")
    elif length == 16 and firstDigit != 4:
        print("MASTERCARD")
    elif length == 13 and firstDigit == 4:
        print("VISA")
    elif length == 16 and firstDigit == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")