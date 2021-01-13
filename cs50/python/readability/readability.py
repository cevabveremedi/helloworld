text = input("text: ")
letters = 0
sentences = 0
words = 0
afterword = 0
for char in text:
    if char.isalpha():
        afterword = 1
        letters += 1
    elif char == ' ' and afterword:
        words += 1
    elif char in ['.', '!', '?']:
        afterword = 0
        sentences += 1
        words += 1

index = 0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8

#print(f"letters: {letters}, sentences: {sentences}, words: {words}")
index = round(index)
if index < 1:
    print("Grade before 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade: {index}")