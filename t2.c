#include <stdio.h>
#include <stdlib.h>

typedef struct pizza {
    int s, t, r;
} pizza;

void pause()
{

   printf("Pressione qualquer tecla para continuar");

  getchar();
  getchar();

}

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
        if (L[i].r <= R[j].r) {
            pizzas[k] = L[i];
            i++;
        } else {
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
        printf("utilizando memoizacao (n: %d t: %d valor: %d)\n", N-1, tempoDecorrido, memoizados[N-1][tempoDecorrido]);
        return memoizados[N-1][tempoDecorrido];  // retornar resultado memoizado

    }
    printf("resolvendo %d em %d (r = %d)\n", N, tempoDecorrido, pizzas[N-1].r);
    //pause();
    int soluCom, soluSem;   // dois cenario possiveis, com ou sem a ultima pizza
    int tempoCom = tempoDecorrido + pizzas[N-1].t; // tempo decorrido considerando que sera feita a ultima pizza
    printf("tempo com: %d (maximo %d) \n", tempoCom, T);
    if(tempoCom > T)    // se fazer a pizza extoura o tempo
        soluCom = 0;    // nao fazer a pizza
    else
    {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= 19; j++) {
                printf("%d ", memoizados[i][j]);
            }
            printf("\n");
        }

        soluCom = solveRecu(pizzas, N-1, T, tempoCom, memoizados) + (pizzas[N-1].s - (tempoCom*pizzas[N-1].r));  // fazer a pizza
    }
    soluSem = solveRecu(pizzas, N-1, T, tempoDecorrido, memoizados);    // valor sem fazer a pizza

    printf("soluCom %d\n",soluCom);
    printf("soluSem %d\n",soluSem);
    // guarda os resultados obtidos na tabela de memoizacao
    memoizados[N-1][tempoDecorrido] = max(soluSem,soluCom);


    printf("alterei a memoizacao \n");

            for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= 19; j++) {
                printf("%d ", memoizados[i][j]);
            }
            printf("\n");
        }
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

    for (int i = 0; i <= N; i++) {  //produzir borda
        for (int j = 0; j < T+1; j++) {
            printf("%d ", memoizados[i][j]);
        }
        printf("\n");
    }




    mergeSort(pizzas, 0, N - 1);    // ordena as pizzas de forma crescente de r atraves do mergesort
    // dada uma solucao contendo o conjunto ACB, se r(B) >= r(C) entao ABC >= ACB, justificando a escolha gulosa

    int resultado = solveRecu(pizzas, N, T, 0, memoizados);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= T; j++) {
            printf("%d ", memoizados[i][j]);
        }
        printf("\n");
    }
    
    //TODO: liberar memoria

    for(int n = 0; n<=N;n++)
    {
        //printf("liberado %lu ", (unsigned long) memoizados[n]);
        free(memoizados[n]);
    }
    //printf("liberado %lu ",(unsigned long) memoizados);
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
*/