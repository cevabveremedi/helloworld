import time
import copy
import numpy as np
import random
from os import system, name

boardGrid = 3

def main(player1, player2, show):
    board = [[' ' for i in range(boardGrid)] for j in range(boardGrid)]
    if show:
        display(board)
    while True:
        if gameStatus(board) == 'C':
            if player1 == 'H':
                humanPlayer(board, 'X')
            elif player1 == 'D':
                dumbAI(board, 'X')
            elif player1 == 'N':
                normalAI(board, 'X')
            else:
                strongAI(board, 'X')
            if show:
                display(board)
        else:
            break
        if gameStatus(board) == 'C':
            if player2 == 'H':
                humanPlayer(board, 'O')
            elif player2 == 'D':
                dumbAI(board, 'O')
            elif player2 == 'N':
                normalAI(board, 'O')
            else:
                strongAI(board, 'O')
            if show:
                display(board)
        else:
            break
    winner = checkWin(board)
    if show:
        if winner == 0:
            print("Tie")
        else:
            print("'{}' won!".format(winner))
    return winner

def checkPosition(board, position):
    j = (position-1) % boardGrid
    i = (position-1) // boardGrid
    return board[i][j] == ' '

def move(board, pos, val):
    j = (pos -1) % boardGrid
    i = (pos -1) // boardGrid
    board[i][j] = val

def humanPlayer(board, val):
    while True:
        pos = input("Pick {} position: ".format(val))
        try:
            pos = int(pos)
            if pos < 1 or pos > boardGrid**2:
                print("!\tInvalid position\t!")
            else:
                if checkPosition(board, pos):
                    move(board, pos, val)
                    break
                else:
                    print("!\tPosition is already occupied\t!")
        except ValueError:
            print("!\tInvalid Number\t!")

def dumbAI(board, val):
    moves = 0
    for i in range(boardGrid):
        for j in range(boardGrid):
            if board[i][j] == ' ':
                moves += 1
    if moves == 0:
        return
    while True:
        randomMove = random.randint(1,boardGrid**2)
        if checkPosition(board, randomMove) == False:
            continue
        move(board, randomMove, val)
        return

def normalAI(board, val):
    max = False
    if val == 'X':
        max = True
    moves = []
    num = 0
    for i in range(boardGrid):
        for j in range(boardGrid):
            num += 1
            if board[i][j] == ' ':
                moves.append(num)
    if len(moves) == 0:
        return
    if len(moves) == boardGrid**2:
        randomMove = random.randint(1,boardGrid**2)
        move(board, randomMove, val)
        return
    bestMove = minimax(board, moves, -10000, 10000, max, 5)
    move(board, bestMove['position'], val) 

def strongAI(board, val):
    max = False
    if val == 'X':
        max = True
    moves = []
    num = 0
    for i in range(boardGrid):
        for j in range(boardGrid):
            num += 1
            if board[i][j] == ' ':
                moves.append(num)
    if len(moves) == 0:
        return
    if len(moves) == boardGrid**2:
        randomMove = random.randint(1,boardGrid**2)
        move(board, randomMove, val)
        return
    bestMove = minimax(board, moves, -10000, 10000, max, 100)
    move(board, bestMove['position'], val)

def minimax(board, moves, alpha, beta, maximising, depth):
    status = gameStatus(board)
    if status != 'C' or depth == 0:
        if status == 'T':
            return {'position': 100, 'score': 0}
        moves = 0
        for i in range(boardGrid):
            for j in range(boardGrid):
                if board[i][j] == ' ':
                    moves += 1
        moves += 1
        if status == 'X':
            return {'position': 100, 'score': moves}
        else:
            return {'position': 100, 'score': -1*moves}
    elif maximising:
        best = {'position': 100, 'score': -10000}
        for pos in moves:
            newBoard = copy.deepcopy(board)
            newMoves = moves.copy()
            newMoves.remove(pos)
            move(newBoard, pos, 'X')
            index = minimax(newBoard, newMoves, alpha, beta, False, depth-1)
            index['position'] = pos
            if best['score'] < index['score']:
                best = index
            alpha = max(alpha, index['score'])
            if beta <= alpha:
                break
        return best
    else:
        best = {'position': 100, 'score': 10000}
        for pos in moves:
            newBoard = copy.deepcopy(board)
            newMoves = moves.copy()
            newMoves.remove(pos)
            move(newBoard, pos, 'O')
            index = minimax(newBoard, newMoves, alpha, beta, True, depth-1)
            index['position'] = pos
            if best['score'] > index['score']:
                best = index
            beta = min(beta, index['score'])
            if beta <= alpha:
                break
        return best

def display(board):
    clear()
    CEND = '\33[0m'
    CRED = '\33[31m'
    CVIOLET = '\33[35m'
    CBEIGE = '\33[36m'
    CBLACK = '\33[30m'
    num = 0
    for i in range(boardGrid):
        print(CBLACK + "-----"*boardGrid + CEND)
        for j in range(boardGrid):
            num += 1
            if board[i][j] == ' ':
                print(CVIOLET + "|%2d |" %num + CEND, end="")
            elif board[i][j] == 'X':
                print(CRED + "| X |" + CEND, end="")
            else:
                print(CBEIGE + "| O |" + CEND, end="")
        print()
    print(CBLACK + "-----"*boardGrid + CEND)

def gameStatus(board):
    winner = checkWin(board)
    if winner == 0:
        for i in range(boardGrid):
            for j in range(boardGrid):
                if board[i][j] == ' ':
                    return 'C'
        return 'T'
    if winner == ' ':
        return 'C'
    else:
        return winner

def checkRows(board):
    for row in board:
        if len(set(row)) == 1:
            return row[0]
    return 0

def checkDiagonals(board):
    if len(set([board[i][i] for i in range(boardGrid)])) == 1:
        return board[0][0]
    if len(set([board[i][boardGrid-i-1] for i in range(boardGrid)])) == 1:
        return board[0][boardGrid-1]
    return 0

def checkWin(board):
    #transposition to check rows, then columns
    for newBoard in [board, np.transpose(board)]:
        result = checkRows(newBoard)
        if result:
            return result
    return checkDiagonals(board)

def clear():
    _ = system('clear')


#main arguments:

def SAIvsSAI(total):
    ties = 0
    for i in range(total):
        if main("C", "C", False) == 0:
            ties += 1
    print(f"{ties}/{total} ties! {i}")

def DAIvsSAI(total):
    ties = 0
    for i in range(total):
        if main("C", "D", True) == 0:
            ties += 1
    print(f"{ties}/{total} ties! {i}")

def NAIvsSAI(total):
    ties = 0
    for i in range(total):
        if main("C", "D", True) == 0:
            ties += 1
    print(f"{ties}/{total} ties! {i}")

if __name__ == "__main__":
    main("C", "H", True)
    #main("H", "D", True)
    #DAIvsSAI(10)
    #NAIvsSAI(10)