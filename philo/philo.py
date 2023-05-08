import os
import re
import sys

must_eat = int(sys.argv[1]) if len(sys.argv) >= 2 else 5
n_philo = int(sys.argv[2]) if len(sys.argv) >= 3 else 5
make = 'make'


def print_red(str, nl=True):
    print("\033[91m {}\033[00m" .format(str), end='\n' if nl else '')


def print_green(str, nl=True):
    print("\033[92m {}\033[00m" .format(str), end='\n' if nl else '')


os.popen(make).read()
out = os.popen(f'./philo {n_philo} 800 200 200 {must_eat}').read()


n_philo = list(range(1, n_philo + 1))

for n in n_philo:
    eating = re.findall(f'{n} is eating', out)
    if not eating:
        eating = 0
    else:
        eating = len(eating)
    if eating >= must_eat:
        print_green('OK', False)
        print(f' Philo {n} eat {eating} time')
    else:
        print_red('KO', False)
        print(f' Philo {n} eat {eating} time')

die = re.findall('\d die', out)
if die:
    print_red(f'\nKO Philo {die[0]}')