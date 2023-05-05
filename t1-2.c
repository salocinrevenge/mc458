#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int has_edge(int i, int j)
{
    if(i==j)
        return 0;
    srand(i+j);
    if(i<j)
        return (rand()%2);
    else
        return !(rand()%2);
}

void mostrarVetor(int *vetor, int n)
{
    for(int i = 0; i< n;i++)
        printf("%d ", vetor[i]+1);
    printf("\n");

}

void checador(int *vetor, int n)
{
    for(int i = 0; i< n-1;i++)
    {
        if(!(has_edge(vetor[i]+1,vetor[i+1])+1))
        {
            printf("Errado!");
            return;
        }
    }
    printf("Correto!");
    return;


}


int* resolveMerge(int inicio, int tamanho)
{
    /*
    Retorna um caminho hamiltoniano no vetor que comeca em inicio e tem tamanho: "tamanho" 
    Funcao recursiva obtida por uma inducao forte.

    divide o vetor na metade e chama recursivamente cada uma das partes.
    cada parte retorna um vetor maximo
    para mesclar os vetores, comece escolhendo o vertice inicial do circuito que
    aponta para o inicio do outro circuito.
    a partir daí, escolha sempre o vértice (próximo do seu vetor ou do outro) que
    aponta para seu oposto, exemplo. Estando no vértice A que pode ir para B ou 1,
    se 1 aponta para B, insira 1, se B aponta para 1, insira B. E siga assim até
    esgotar um dos vetores e entao apenas copie o vetor restante.
    
    */

    // printf("inicio: %d, tamanho: %d\n", inicio, tamanho);
    int* vetorResposta = (int *) malloc((tamanho)*sizeof(int));
    if(tamanho == 1)
    {
        vetorResposta[0]= inicio;
        return vetorResposta;

    }

    int *vetorA = resolveMerge(inicio, tamanho/2); // resolve a primeira parte com a metade do tamanho
    // printf("mostrando vetor A:\n");
    // mostrarVetor(vetorA,tamanho/2);
    int *vetorB = resolveMerge( inicio + tamanho/2, tamanho-(tamanho/2)); // resolve o restante
    // printf("mostrando vetor B:\n");
    // mostrarVetor(vetorB, tamanho-(tamanho/2));
    int a = 0;
    int b = 0;

    int posResposta = 0;

    // printf("vo mesclar\n");
    

    int fimA =tamanho/2; // fim do A
    int fimB =tamanho-(tamanho/2); // fim do B

    // printf("fim de A: %d; fim de B: %d\n",fimA,fimB);
    while(a<fimA && b < fimB)
    {
        // printf("a: %d, b: %d, posResposta: %d\n",a,b,posResposta);
        //mescla os vetores a e b
        if(has_edge(vetorA[a]+1, vetorB[b]+1))
        {
            vetorResposta[posResposta]=vetorA[a];
            a++;
        }
        else
        {
            vetorResposta[posResposta]=vetorB[b];
            b++;

        }
        posResposta++;
    }
    // printf("ja mesclei: a: %d, b: %d, posResposta: %d\n",a,b,posResposta);
    // printf("fimA: %d, fimB: %d", fimA, fimB);
    // passe o resto do vetor restante para o vetor resposta
    while(a<fimA)
    {
        vetorResposta[posResposta]=vetorA[a];
        a++;
        posResposta++;
    }
    while(b<fimB)
    {
        vetorResposta[posResposta]=vetorB[b];
        b++;
        posResposta++;
    }

    free(vetorA);
    free(vetorB);
    // printf("retornando\n");
    return vetorResposta;
}

int main()
{
    int n;  // Numero de picos no parque exotico nacional dos picos
    scanf("%d", &n);
    
    //DEGUB: mostrar a matriz de adjacencia
    // for(int i = 0;i<n;i++,printf("\n"))
    // {
    //     for(int j = 0;j<n;j++)
    //     {
    //         printf("%d ", has_edge(i+1,j+1));
    //     }
    // }
    int *vetor = resolveMerge(0,n);
    mostrarVetor(vetor,n);
    checador(vetor,n);
    free(vetor);

}

/*
Para compilar:
gcc t1-2.c -std=c99 -pedantic -Wall -lm -o t1-2

Executar:
./t1-2.exe

Compilar e executar (caso o primeiro falhe a cadeia continua):
gcc t1-2.c -std=c99 -pedantic -Wall -lm -o t1-2 ; ./t1-2.exe

*/