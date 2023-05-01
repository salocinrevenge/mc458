#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int** geraMatrix(int n)
{
/*
Cria uma matriz de adjacencias aleatoria de dimensão nxn
Percorre a diagonal principal 0 os termos
Percorre a matriz triangular inferior corrigindo a triangular superior com seu oposto
Devolve a matriz

parametros:
int n: um inteiro que significa o tamanho da matriz quadrada

retorno:
ponteiro para matriz criada
*/

    // Passo 1: criar uma matriz de adjacencias aleatoria nxn
    int** matrix = (int**) malloc(n * sizeof(int*)); // aloca espaço para n ponteiros para linhas

    //srand(time(NULL)); // inicializa o gerador de números aleatórios com o tempo atual
    srand(42);

    for(int i = 0; i < n; i++)
    {
        matrix[i] = (int*) malloc(n * sizeof(int)); // aloca espaço para n booleanos na linha i
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 2; // atribui um valor booleano aleatório (0 ou 1) à posição (i,j) da matriz
        }
    }

    // Passo 2: percorrer a diagonal principal zerando os termos

    for(int i = 0; i < n; i++)
    {
        matrix[i][i] = 0;
    }

    // Passo 3: percorre a matriz triangular inferior corrigindo a triangular superior com seu oposto

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            matrix[j][i] = !matrix[i][j];
        }
    }

    // Passo 4: devolve a matrix

    return matrix;


}

int has_edge(int i, int j, int** matrix)
{
    return matrix[i-1][j-1];
}

void destroi(int **matrix, int n)
{
/*
Libera toda a memoria alocada na matrix de ordem nxn
*/

    for(int i = 0; i < n; i++) {
    free(matrix[i]); // libera a memória alocada para a linha i
    }
    free(matrix); // libera a memória alocada para os ponteiros para as linhas
    return;

}

void mostrar(int **matrix, int n)
{
    // Apenas para desenvolvimento, mostra a matrix
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

}

int* inserirEmPos(int n, int pos, int *vetor)
{
/*
n é elemento e tambem maximo do vetor
*/
    int tmp = vetor[pos];
    vetor[pos] = n;
    int tempnovo;
    for(int i = pos+1; i<n-1;i++)
    {
        tempnovo = vetor[i];
        vetor[i] = tmp;
        tmp = tempnovo;
    }
    vetor[n-1] = tmp;
    return vetor;

}

void mostrarVetor(int *vetor, int n)
{
    for(int i = 0; i< n;i++)
        printf("%d ", vetor[i]);
    printf("\n");

}

int* resolve(int **matrix, int n, int *vetor)
{
/*
Encontra um caminho que percorre todos os vertices do grafo e retorna a lista contendo esses vértices.

Parametros:
int** matrix: Matrix de adjacencias do grafo
int n: Tamanho da matrix atual
int* vetor: vetor contendo o caminho completo
int nv: tamanho atual do vetor de resposta
Retorno:
ponteiro para vetor de inteiros de tamanho n contendo a resposta

Funcão recursiva
Caso de parada (base): Se n = 1, entao adiciona o proprio vertice

Passo:
Se o vertice n aponta para 1, ele eh o novo comeco do caminho, adiciona no comeco do vetor
Se nao, ele deve ser inserido antes do primeiro vertice que ele aponta
Se ele nao aponta para nenhum vertice, ele deve ser o fim do caminho, adiciona no fim do vetor

*/
    if(n <= 0)
    {
        // Error, valor inválido
        printf("Valor invalido");
        return NULL;
    }
    
    if(n == 1)
    {
        vetor[n-1] = n;
        //printf("Caso base\n");
        //mostrarVetor(vetor, n);
        return vetor;
    }

    // Calcula o vetor de saida sem o ultimo termo
    vetor = resolve(matrix, n-1, vetor);

    for(int i = 0; i < n-1; i++)
    {
        if(has_edge(n,vetor[i],matrix))
        {
            vetor = inserirEmPos(n,i,vetor);  // insere o numero n antes do valor i no vetor de saida e retorna
            //mostrarVetor(vetor, n);
            return vetor;
        }
    }
    // Se ele nao aponta para ninguem

    vetor[n-1] = n;
    //printf("Caso Final\n");
    //mostrarVetor(vetor, n);
    return vetor;




}

int main()
{
/*
Resolve o problema dado no trabalho 1 disponível nesse git

Passo 1: cria a matrix aleatoria com base na leitura do teclado

Passo 2: resolve o problema

Passo 3: destroi a matrix

*/

// Passo 1: cria a matrix aleatoria com base na leitura do teclado
int n;
scanf("%d", &n);
int** matrix = geraMatrix(n);

// Mostrar matriz por questoes de debug
//mostrar(matrix, n);

//printf("\n");

// Cria o vetor de respostas
int* vetor = (int*) malloc(n*sizeof(int));
for(int i = 0; i< n;i++)
        vetor[i]=0;

printf("Criei, agora vou resolver\n");

clock_t inicio = clock();
resolve(matrix, n, vetor);

//mostrarVetor(vetor, n);
clock_t fim = clock();
printf("Resolvi em %lf\n", (double) (fim-inicio)/CLOCKS_PER_SEC);

// Passo 3: destroi a matrix
destroi(matrix, n);

free(vetor);


}

/*
Para compilar:
gcc t1.c -std=c99 -pedantic -Wall -lm -o t1

Executar:
./t1.exe

Compilar e executar (caso o primeiro falhe a cadeia continua):
gcc t1.c -std=c99 -pedantic -Wall -lm -o t1 ; ./t1.exe



*/