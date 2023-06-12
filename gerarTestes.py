import itertools

def permutations(N):
    nums = list(range(0, N))
    return list(itertools.permutations(nums))

def pontuacao(pizzas, permutacao, T):
    percorrido = 0
    sabor = 0
    for indice in permutacao:
        percorrido += pizzas[indice]['t']
        if percorrido > T:
            return sabor
        else:
            sabor = max(sabor, sabor+ (pizzas[indice]['s'] - (pizzas[indice]['r'] * percorrido)))
            
    return sabor

def solve(pizzas, T):
    maximo = 0
    for permutacao in permutations(len(pizzas)):
        maximo = max(pontuacao(pizzas, permutacao, T), maximo)
    return maximo


def main():
    N,T = map(int, input().split())
    pizzas = []
    for _ in range(N):
        linha = tuple(map(int,input().split()))
        pizzas.append({"s": linha[0], "t": linha[1], "r": linha[2]})
    print(solve(pizzas, T))

main()

'''
compilando gcc t2.c -std=c99 -pedantic -Wall -lm -o t2 ; ./t2.exe

entrada:

3 60
80 25 1
70 20 2
60 15 3


saida: 65


2 20
120 10 2
120 10 3

: 170

2 21
120 10 2
120 10 3

: 170

2 19
120 10 2
120 10 3

: 100



5 180
80 25 1
70 20 2
60 15 3
170 50 3
90 12 0

: 155

4 2
40 0 50
30 2 0
80 0 0
-1 0 3

: 150

8 1000
60 58 1
700 30 3
10000 89 5
10000 90 5
890 2 90
800 100 3
7000 400 2
655 800 0

:25432

3 2
10 1 10
30 1 40
-10 0 0
: 0

'''