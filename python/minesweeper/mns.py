import random
from os import system, name 

def main(grid, bombs):
    board = Board(grid, bombs)
    board.display()
    while board.freeSpaces() > 0:
        try:
            col, row = [int(x) for x in input("Enter row col: ").split()]
        except ValueError:
            print("Invalid input. Try: num1 num2")
            continue
        if col < 0 or row < 0 or col >= grid or row >= grid:
            print("Invalid position.", end=" ")
            print(f"Numbers must be greater than -1 and less than {grid}!")
            continue
        if not board.check(row, col):
            print(f"This is already uncovered! {col} {row}")
            continue
        if board.digHere(row, col) == False:
            board.afterGame()
            print("You Died!")
            exit(0)
        else:
            board.display()
    print("You won!")


class Board:
    def __init__(self, grid, bomb):
        self.grid = grid
        self.bomb = bomb
        self.board = self.create()
        self.values()

    def check(self, row, col):
        return self.board[row][col][1] == 0

    def create(self):
        newBoard = [
            [[0,0] for _ in range(self.grid)] for _ in range(self.grid)
        ]
        numBomb = 0
        while numBomb < self.bomb:
            position = random.randint(0, (self.grid**2)-1)
            col = position % self.grid
            row = position // self.grid
            if newBoard[row][col][0] == -1:
                continue
            newBoard[row][col][0] = -1
            numBomb += 1
        return newBoard

    def neighbours(self, row, col):
        totalBomb = 0
        for r in range(row-1, (row+1)+1):
            for c in range(col-1, (col+1)+1):
                if r < 0 or c < 0 or r == self.grid or c == self.grid:
                    continue
                if r == row and c == col:
                    continue
                if self.board[r][c][0] == -1:
                    totalBomb += 1
        return totalBomb

    def values(self):
        for r in range(self.grid):
            for c in range(self.grid):
                if self.board[r][c][0] == -1:
                    continue
                self.board[r][c][0] = int(self.neighbours(r, c))

    def display(self):
        clear()
        CBEIGE = '\33[44m'
        CRED = '\33[41m'
        CEND = '\33[0m'
        print("   |", end="")
        for i in range(self.grid):
            if i//10 == 0:
                print(f"  {i} |", end="")
            else:
                print(f"  {i}|", end="")
        print()
        for r in range(self.grid):
            if r//10 == 0:
                print(f" {r} |", end="")
            else:
                print(f" {r}|", end="")
            for c in range(self.grid):
                if self.board[r][c][1] == 0:
                    print("| ? |",end="")
                else:
                    if self.board[r][c][0] == "*":
                        print(CRED + f"| {self.board[r][c][0]} |" + CEND,end="")
                    else:
                        print(CBEIGE + f"| {self.board[r][c][0]} |" + CEND,end="")
            print("\n")

    def digHere(self, row, col):
        if self.board[row][col][0] == -1:
            return False
        elif self.board[row][col][0] > 0:
            self.board[row][col][1] = 1
            return True
        else:
            self.board[row][col][1] = 1
            for r in range(row-1, (row+1)+1):
                for c in range(col-1, (col+1)+1):
                    if r < 0 or c < 0 or r == self.grid or c == self.grid:
                        continue
                    if self.board[r][c][1] == 1:
                        continue
                    else:
                        self.digHere(r, c)
            return True

    def afterGame(self):
        for i in range(self.grid):
            for j in range(self.grid):
                self.board[i][j][1] = 1
                if self.board[i][j][0] == -1:
                    self.board[i][j][0] = "*"
        self.display()

    def freeSpaces(self):
        total = 0
        for i in range(self.grid):
            for j in range(self.grid):
                if self.board[i][j][1] == 0:
                    total += 1
        return total - self.bomb

def clear():
    _ = system('clear')

if __name__ == "__main__":
    grids = 10 # grid * grid board.
    bombs = 15
    main(grids, bombs)