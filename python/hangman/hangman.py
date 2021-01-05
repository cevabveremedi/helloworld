from dictwords import words
import random
from os import system, name 

def main():
    selectedWord = random.choice(words)
    wordsTried = []
    wordsFound = [' ', '-']
    lives = 10

    print("You have {} lives left".format(lives))
    display(selectedWord, wordsFound)

    while lives != 0:
        if completed(selectedWord, wordsFound) == True:
            print("Congratulations!")
            return;
        else:
            guess = input("\nPick a char: ".lower())
            if guess == '!':
                clear()
                display(selectedWord, wordsFound)
                print("\nYou have {} lives left!".format(lives), end="")
                continue
            if guess.isalpha() != True or len(guess) != 1:
                clear()
                print("Invalid character!")
                continue
            if guess in wordsTried:
                print("Letters you've already Tried:", end=" ")
                print(*wordsTried, sep=", ")
            elif guess in wordsFound:
                print("You've alreay Found that letter.")
                display(selectedWord, wordsFound)
            elif guess in selectedWord:
                wordsFound.append(guess)
                clear()
                print("  [{}]  ".format(guess))
                display(selectedWord, wordsFound)
            else:
                lives -= 1
                print(f"Nope. You have {lives} lives left!")
                wordsTried.append(guess)
    print("--> Failed! The word was {}".format(selectedWord))

def completed(selected, found):
    for item in selected:
        if item in found:
            continue
        else:
            return False
    return True

def display(selected, found):
    for letter in selected:
        if letter in found:
            print(letter, end=" ")
        else:
            print("_", end=" ")
    print()

def clear():
    _ = system('clear')

main()