# Now I can use google translate from the command line
# and save 10 seconds everytime I need to check some 
# word online thanks to this little program.

from googletrans import Translator
from sys import argv
from os import system, name 

_ = system('clear')

if len(argv) == 1:
    src = 'en'
    dest = 'tr'
elif len(argv) == 2:
    src = 'tr'
    dest = 'en'
else:
    exit(0)

trans = Translator()

word = input("Translate: ")
t = trans.translate(
    word, dest=dest, src=src
)

CCLR   = '\33[7m'
CEND = '\033[0m'

print(CCLR + f'({t.src})({t.dest})-> {t.text}' + CEND)

with open("translate_history.txt", "a") as myfile:
    myfile.write(f'{word}-> ({t.src})({t.dest})-> {t.text}' + '\n')