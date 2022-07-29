#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef char string[20];

typedef struct tipoAluno
{
    int matricula;
    string nome;
    char sexo;
    struct tipoAluno *prox;
} TAluno;

typedef struct tipoNo
{
    TAluno *aluno;
    struct tipoNo *origem, *esq, *dir;
} TNo;

typedef struct tipoLista
{
    TNo *raiz;
    TAluno *inicio;
    TAluno *fim;
} TLista;

TLista lista, *copiaLista;
TNo *raiz;

void inicializa(TLista *L)
{
    L->inicio = NULL;
    L->fim = NULL;
}

int menu()
{
    int opcao;
    system("CLS"); //Limpa a Tela e posiciona o
                   //CURSOR no canto esquerdo superior da mesma
    printf("\n\n\n\t     =====| MENU |=====\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
    printf("1 - Inserir Aluno.\n");
    printf("2 - Listar Alunos por ordem crescente de matr?cula.\n");
    printf("3 - Listar Alunos por nome em ordem alfab?tica.\n");
    printf("4 - Buscar Aluno por nome.\n");
    printf("5 - Remover Aluno.\n");
    printf("\tInforme OPCAO desejada: ");

    scanf(" %d", &opcao);

    if ((opcao > 5) || (opcao < 0))
    {
        printf("\n\n\n");
        printf("\t+-------------------------------------------------+\n");
        printf("\t|   ERRO:                                         |\n");
        printf("\t|                                                 |\n");
        printf("\t|   OPCAO INVALIDA!!!                             |\n");
        printf("\t|                                                 |\n");
        printf("\t|   Tente outra vez.                              |\n");
        printf("\t+-------------------------------------------------+\n\n");
        system("PAUSE");
    }
    return opcao;
}

TNo *inserirNo(TNo **origem, TNo *no)
{
    if ((*origem) == NULL)
    {
        (*origem) = no;
        return (*origem);
    }

    if (strcmp((*origem)->aluno->nome, no->aluno->nome) == 1)
    {
        (*origem)->esq = inserirNo(&(*origem)->esq, no);
        return (*origem);
    }

    (*origem)->dir = inserirNo(&(*origem)->dir, no);
    return (*origem);
}

TNo *inserirAluno(TLista *L)
{
    TAluno *aluno = (TAluno *)malloc(sizeof(TAluno));

    printf("Insira o nome do aluno: ");
    scanf(" %s", aluno->nome);

    printf("Insira a matrícula do aluno: ");
    scanf("%d", &aluno->matricula);

    printf("Insira o sexo do aluno: ");
    scanf("%s", &aluno->sexo);

    aluno->prox = NULL;

    TNo *no = (TNo *)malloc(sizeof(TNo));
    no->aluno = aluno;
    no->esq = NULL;
    no->dir = NULL;

    TAluno *atual = L->inicio;

    if (atual == NULL)
    {
        L->raiz = no;
        L->inicio = aluno;
        L->fim = aluno;
        return no;
    }

    if (aluno->matricula < atual->matricula)
    {
        L->inicio = aluno;
        aluno->prox = atual;
        return no;
    }

    TAluno *pivo = atual->prox;

    while (pivo != NULL)
    {
        if (aluno->matricula < pivo->matricula)
        {
            atual->prox = aluno;
            aluno->prox = pivo;
            return no;
        }

        pivo = pivo->prox;
    }

    L->fim->prox = aluno;
    L->fim = aluno;
    return no;
}

void listarAlunosPorMatriculaOrdemCrescente(TLista *L)
{
    TAluno *atual = L->inicio;

    while (atual != NULL)
    {
        printf("\n");
        printf("\t+-------------------------------------------------+\n");
        printf("\t|                                                 |\n");
        printf("\t|   ALUNO: %s                                     |\n", atual->nome);
        printf("\t|   MATRICULA: %d                                 |\n", atual->matricula);
        printf("\t|   SEXO: %c                                      |\n", atual->sexo);
        printf("\t|                                                 |\n");
        printf("\t+-------------------------------------------------+\n\n");
        atual = atual->prox;
    }
    printf("\tFim dos elementos.\n\n");
    system("PAUSE");
}

void listarAlunosPorNomeOrdemCrescente(TNo *no)
{
    if (no != NULL)
    {
        listarAlunosPorNomeOrdemCrescente(no->esq);
        printf("\n");
        printf("\t+-------------------------------------------------+\n");
        printf("\t|                                                 |\n");
        printf("\t|   ALUNO: %s                                     |\n", no->aluno->nome);
        printf("\t|   MATRICULA: %d                                 |\n", no->aluno->matricula);
        printf("\t|   SEXO: %c                                      |\n", no->aluno->sexo);
        printf("\t|                                                 |\n");
        printf("\t+-------------------------------------------------+\n\n");
        listarAlunosPorNomeOrdemCrescente(no->dir);
    }
}

void pesquisarAlunoPorNome(TNo *no, string n)
{
    if (no == NULL)
    {
        printf("\n");
        printf("\t+-------------------------------------------------+\n");
        printf("\t|                                                 |\n");
        printf("\t|   ALUNO NÃO ENCONTRADO!                         |\n");
        printf("\t|                                                 |\n");
        printf("\t+-------------------------------------------------+\n\n");
        system("PAUSE");
        return;
    }

    if (strcmp(no->aluno->nome, n) == 0)
    {
        printf("\n");
        printf("\t+-------------------------------------------------+\n");
        printf("\t|                                                 |\n");
        printf("\t|   ALUNO ENCONTRADO! %s                          |\n", no->aluno->nome);
        printf("\t|   MATRICULA: %d                                 |\n", no->aluno->matricula);
        printf("\t|   SEXO: %c                                      |\n", no->aluno->sexo);
        printf("\t|                                                 |\n");
        printf("\t+-------------------------------------------------+\n\n");
        system("PAUSE");
        return;
    }

    if (strcmp(no->aluno->nome, n) == 1)
    {
        pesquisarAlunoPorNome(no->esq, n);
        return;
    }

    pesquisarAlunoPorNome(no->dir, n);
}

TNo *removerNo(TNo *no, string nome)
{
    if (no == NULL)
    {
        return NULL;
    }

    if (strcmp(no->aluno->nome, nome) == 1)
    {
        no->esq = removerNo(no->esq, nome);
        return no;
    }

    if (strcmp(no->aluno->nome, nome) == -1)
    {
        no->dir = removerNo(no->dir, nome);
        return no;
    }

    if (no->dir == NULL && no->esq == NULL)
    {
        free(no);
        no = NULL;
        return no;
    }

    if (no->esq == NULL)
    {
        TNo *aux = no;
        no = no->dir;
        free(aux);
        aux = NULL;
        return no;
    }

    if (no->dir == NULL)
    {
        TNo *aux2 = no;
        no = no->esq;
        free(aux2);
        aux2 = NULL;
        return no;
    }

    TNo *aux3 = no->esq;
    while (aux3->dir != NULL)
    {
        aux3 = aux3->dir;
    }

    strcpy(no->aluno->nome, aux3->aluno->nome);
    strcpy(aux3->aluno->nome, nome);

    no->esq = removerNo(no->esq, nome);

    return no;
}

void removerAluno(TLista *L, string *nome)
{
    TAluno *atual = L->inicio;
    TAluno *prox = atual->prox;

    if (strcmp(atual->nome, nome) == 0)
    {
        L->inicio = atual->prox;
        free(atual);
        return;
    }

    if (prox == NULL)
    {
        printf("\tAluno não encontrado.\n");
        system("PAUSE");
        return;
    }

    while (prox != NULL && strcmp(nome, prox->nome) != 0)
    {
        prox = prox->prox;
        atual = atual->prox;
    }

    if (prox == NULL)
    {
        printf("\tAluno não encontrado.\n");
        system("PAUSE");
        return;
    }

    if (prox == L->fim)
    {
        L->fim = atual;
        free(prox);
        prox = NULL;
        return;
    }

    atual->prox = prox->prox;
    free(prox);
    prox = NULL;
}

int main()
{
    setlocale(LC_ALL, "");
    int op;
    TNo *novo;
    string nome;
    //sint *marcador = 1;

    inicializa(&lista);
    raiz = NULL;

    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            novo = inserirAluno(&lista);
            inserirNo(&raiz, novo);
            break;
        case 2:
            listarAlunosPorMatriculaOrdemCrescente(&lista);
            break;
        case 3:
            listarAlunosPorNomeOrdemCrescente(raiz);
            printf("\tFim dos elementos.\n");
            system("PAUSE");
            break;
        case 4:
            printf("\t Insira o nome a pesquisar: ");
            scanf(" %s", &nome);
            printf("\n");
            pesquisarAlunoPorNome(raiz, nome);
            break;
        case 5:
            printf("\t Insira o nome a excluir: ");
            scanf(" %s", &nome);
            raiz = removerNo(raiz, nome);
            removerAluno(&lista, nome);
            break;
        } //switch

    } while (op != 0);
}
