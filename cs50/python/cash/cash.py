while True:
    try:
        cash = float(input("Change owed: "))
        if cash < 0:
            print("Invalid input. Number must be greater than 0!")
            continue
    except ValueError:
        print("Please enter an integer!")
        continue
    break

total = 0
cash *= 100
while cash > 0:
    if cash >= 25:
        cash -= 25
        total += 1
    elif cash >= 10:
        cash -= 10
        total += 1
    elif cash >= 5:
        cash -= 5
        total += 1
    else:
        total += cash
        break
print(int(total))