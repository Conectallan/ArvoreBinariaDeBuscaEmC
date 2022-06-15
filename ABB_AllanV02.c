#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

TLista lista;
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
        printf("\t+-------------------------------------------------+");
        printf("\t|   ERRO:                                         |");
        printf("\t|                                                 |");
        printf("\t|   OPCAO INVALIDA!!!                             |");
        printf("\t|                                                 |");
        printf("\t|   Tente outra vez.                              |");
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

    if (strcmp((*origem)->aluno->nome, no->aluno->nome) == -1)
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
    scanf(" %s", &aluno->nome);

    printf("Insira a matr?cula do aluno: ");
    scanf("%d", &aluno->matricula);

    printf("Insira o sexo do aluno: ");
    scanf("%d", &aluno->sexo);

    aluno->prox = NULL;

    TNo *no = (TNo *)malloc(sizeof(TNo));
    no->aluno = aluno;
    no->esq = NULL;
    no->dir = NULL;

    if (L->inicio != NULL)
    {
        L->fim->prox = aluno;
        L->fim = aluno;
        return no;
    }

    L->raiz = no;
    L->inicio = aluno;
    L->fim = aluno;
    return no;
}

TLista *criarListaAuxiliar(TLista *L)
{
    TLista *aux = (TLista *)malloc(sizeof(TLista));
    inicializa(aux);

    TAluno *atual = L->inicio;
    TAluno *copia = aux->inicio;
    while (atual != NULL)
    {
        copia->matricula = atual->matricula;
        strcpy(copia->nome, atual->nome);
        copia->sexo = atual->sexo;

        if (atual = L->fim)
            copia = aux->fim;

        copia->prox = NULL;
        copia = copia->prox;
        atual = atual->prox;
    }

    return aux;
}

void trocarValores(TAluno **a1, TAluno **a2)
{
    TAluno pivo;
    pivo.matricula = (*a1)->matricula;
    pivo.sexo = (*a1)->sexo;
    strcpy(pivo.nome, (*a1)->nome);

    (*a1)->matricula = (*a2)->matricula;
    (*a1)->sexo = (*a2)->sexo;
    strcpy((*a1)->nome, (*a2)->nome);

    (*a2)->matricula = pivo.matricula;
    (*a2)->sexo = pivo.sexo;
    strcpy((*a2)->nome, pivo.nome);
}

void listarAlunosPorMatriculaOrdemCrescente(TLista *L)
{
    TLista *copia = criarListaAuxiliar(L);

    TAluno *aux = copia->inicio;
    TAluno *pivo;

    if (aux == NULL)
    {
        printf("N?o h? elementos na lista.\n");
        system("PAUSE");
        return;
    }

    if (aux->prox == NULL)
    {
        printf("\t+-------------------------------------------------+");
        printf("\t|                                                 |");
        printf("\t|   ALUNO: %s                                     |", aux->nome);
        printf("\t|   MATRICULA: %d                                 |", aux->matricula);
        printf("\t|   SEXO: %c                                      |", aux->sexo);
        printf("\t|                                                 |");
        printf("\t+-------------------------------------------------+\n\n");
        return;
    }

    while (aux != NULL)
    {
        pivo = aux->prox;

        while (pivo != NULL)
        {
            if (aux->matricula > pivo->matricula)
                trocarValores(&aux, &pivo);

            pivo = pivo->prox;
        }

        aux = aux->prox;
    }

    aux = copia->inicio;

    while (aux != NULL)
    {
        printf("\t+-------------------------------------------------+");
        printf("\t|                                                 |");
        printf("\t|   ALUNO: %s                                     |", aux->nome);
        printf("\t|   MATRICULA: %d                                 |", aux->matricula);
        printf("\t|   SEXO: %c                                      |", aux->sexo);
        printf("\t|                                                 |");
        printf("\t+-------------------------------------------------+\n\n");

        aux = aux->prox;
    }
}

void listarAlunosPorNomeOrdemCrescente(TNo *no)
{
    if (no != NULL)
    {
        listarAlunosPorNomeOrdemCrescente(no->esq);
        printf("\n\n\n");
        printf("\t+-------------------------------------------------+");
        printf("\t|                                                 |");
        printf("\t|   ALUNO: %s                                     |", no->aluno->nome);
        printf("\t|   MATRICULA: %d                                 |", no->aluno->matricula);
        printf("\t|   SEXO: %c                                      |", no->aluno->sexo);
        printf("\t|                                                 |");
        printf("\t+-------------------------------------------------+\n\n");
        listarAlunosPorNomeOrdemCrescente(no->dir);
    }
}

int main()
{
    setlocale(LC_ALL, "");
    int op;
    TNo *novo;

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
            break;
        case 4:
            break;
        case 5:
            break;
        } //switch

    } while (op != 0);
}