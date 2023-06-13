#include <stdio.h>
#include <stdlib.h>

typedef struct pizza {
    int s, t, r;
} pizza;

// codigo para ordenar o vetor
void merge(pizza *pizzas, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Cria vetores temporários
    pizza L[n1], R[n2];

    // Copia os dados para os vetores temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = pizzas[left + i];
    for (j = 0; j < n2; j++)
        R[j] = pizzas[mid + 1 + j];

    // Junta os vetores temporários de volta em pizzas[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        //printf("%lf e %lf\n",(double)L[i].t/L[i].r , (double)R[j].t/R[j].r);
        if ((double)L[i].t/L[i].r > (double)R[j].t/R[j].r) {
            pizzas[k] = L[i];
            i++;
        } else{
            pizzas[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver algum
    while (i < n1) {
        pizzas[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while (j < n2) {
        pizzas[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(pizza *pizzas, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a metade esquerda
        mergeSort(pizzas, left, mid);

        // Ordena a metade direita
        mergeSort(pizzas, mid + 1, right);

        // Une as duas metades ordenadas
        merge(pizzas, left, mid, right);
    }
}

void ordenar(pizza *pizzas, int N) {
    mergeSort(pizzas, 0, N - 1);
}
// fim do codigo para ordenar o vetor

int max(int a, int b)
{
    if(b>a)
        return b;
    return a;
}

int solveRecu(pizza *pizzas, int N, int T, int tempoDecorrido, int **memoizados)
{
    if(N<=0 || tempoDecorrido > T)
        return 0;

    if(memoizados[N-1][tempoDecorrido] > -1)
    {
        return memoizados[N-1][tempoDecorrido];  // retornar resultado memoizado

    }
    int soluCom, soluSem;   // dois cenario possiveis, com ou sem a ultima pizza
    int tempoCom = tempoDecorrido + pizzas[N-1].t; // tempo decorrido considerando que sera feita a ultima pizza
    if(tempoCom > T)    // se fazer a pizza extoura o tempo
        soluCom = 0;    // nao fazer a pizza
    else
    {

        soluCom = solveRecu(pizzas, N-1, T, tempoCom, memoizados) + (pizzas[N-1].s - (tempoCom*pizzas[N-1].r));  // fazer a pizza
    }
    soluSem = solveRecu(pizzas, N-1, T, tempoDecorrido, memoizados);    // valor sem fazer a pizza

    // guarda os resultados obtidos na tabela de memoizacao
    memoizados[N-1][tempoDecorrido] = max(soluSem,soluCom);

    return max(soluCom, soluSem);
}

int solve(pizza *pizzas, int N, int T)
{
    // Aloca a matriz dinamicamente
    int **memoizados = (int **)malloc((N+1) * sizeof(int *)); //N+1 de borda
    if (memoizados == NULL) {
        printf("Erro ao alocar memória para a matriz!\n");
        return -1;
    }
    for(int n = 0; n<=N;n++)    // produzir borda
    {
        memoizados[n] = (int *)malloc((T+1) * sizeof(int)); // t+1 por borda
        for(int t = 0; t<T+1; t++)    // menor igual para garantir a borda
            memoizados[n][t] = -1;
    }




    mergeSort(pizzas, 0, N - 1);    // ordena as pizzas de forma decrescente de t/r atraves do mergesort
    
    //for(int i =0 ; i<N; ++i)
      //  printf("pizza: %d %d %d\n",pizzas[i].s,pizzas[i].t,pizzas[i].r);
    
    // dada uma solucao contendo o conjunto ACB, se r(B) >= r(C) entao ABC >= ACB, justificando a escolha gulosa

    int resultado = solveRecu(pizzas, N, T, 0, memoizados);
    
    //liberar memoria

    for(int n = 0; n<=N;n++)
    {
        free(memoizados[n]);
    }
    free(memoizados);

    return resultado;

}

int main()
{

    int N, T;   // N numero de pizzas, T tempo maximo
    scanf("%d %d", &N, &T); //recebe os valores para n e t da primeira linha

    pizza pizzas[N];    // cria um vetor de pizzas
    for(int i = 0; i < N; i++)  // le todas as pizzas
        scanf("%d %d %d", &pizzas[i].s, &pizzas[i].t, &pizzas[i].r);

    printf("%d\n", solve(pizzas, N, T));
    return 0;
}



/*
compilando 
gcc t2.c -std=c99 -pedantic -Wall -lm -o t2 ; ./t2

entrada:

3 60
80 25 1
70 20 2
60 15 3


saida: 65


testes para bordas

2 20
120 10 3
120 10 2

: 170

2 21
120 10 2
120 10 3

: 170

2 19
120 10 2
120 10 3

: 100

teste com mais de 3 e r 0

5 180
170 50 3
60 15 3
70 20 2
90 12 1
80 25 1

: 121

teste com numeros negativos

4 2
40 1 50
30 2 1
80 1 1
1 1 3

: 79

teste para grandes instancias

8 1000
60 58 1
700 30 3
10000 89 5
10000 90 5
890 2 90
800 100 3
7000 400 2
655 800 1

:25432

testes para valores de sabores finais nulos ou menores que 0
3 2
10 1 10
30 1 40
10 1 1
: 9

teste para valores que nao se deve ordenar por r

2 1000
700 30 3
10000 89 5

:10015

*/