from cs50 import get_string
import re
from statistics import mean

# get user input
text = get_string("Text: ")

sentences = 0
words = 0
letters = 0

for i in range(len(text)):
    if text[i] in [".", "?", "!"]:
        sentences += 1

words = len(re.findall('[\s+]', text)) + 1  # +1 to account for the very last word
letters = len(re.findall('[\w+]', text))

# Coleman-Liau index
#L = mean(letters / (words % 100))
#S = mean(sentences / (words % 100))
L = (letters / words) * 100
S = (sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade: {index}")
    