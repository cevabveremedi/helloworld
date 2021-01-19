from googletrans import Translator
from sys import argv

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