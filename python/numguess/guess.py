from random import randint

def main():
    number = randint(1, 1000)
    tryleft = 10
    print("You have 10 attempts to guess the number (1-1000)!")
    print("What's your guess: ")
    while tryleft > 0:
        guess = input()
        if isnumber(guess) == False:
            print("This is not an int!")
            continue
        else:
            guess = int(guess)
        tryleft -= 1
        if number < guess:
            print(f"Too big! {tryleft}...")
        elif number > guess:
            print(f"Too small! {tryleft}...")
        else:
            print("Congratulations! The number is {}".format(number))
            exit(0)
    print(f"Failed! The number was {number}")

def isnumber(x):
    for i in range(len(x)):
        if x[i].isdigit() != True:
            return False
    return True

main()