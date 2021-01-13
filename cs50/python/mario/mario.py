while True:
    size = input("Enter the height of the pyramid: ")
    try:
        size = int(size)
        if size < 1 or size > 8:
            print("The height must between 1 and 8, inclusive.")
            continue
        else:
            break
    except ValueError:
        print("Please enter an integer!")

for i in range(1, size+1):
    print(" "*(size-i),end="")
    print("#"*i,end="  ")
    print("#"*i)