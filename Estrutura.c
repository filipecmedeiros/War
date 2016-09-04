#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aliados{
    char nome [12];
    struct aliados* prox;
}Aliados;

typedef struct pais {
    char nome [12];
    int armas;
    int forca;
    float coordX;
    float coordY;
    int qntdAliados;
    Aliados* nomesAliados;
    struct pais* prox;
}Pais;


/*A funcao cria uma variavel "pais" e inicializa com o nome (previamente extraido do arquivo) e coloca ao final da lista encadeada*/
Pais* f_cria_pais (char* strNome, Pais* inicio)
{
    Pais* novo, *aux;

    novo = (Pais*) malloc (sizeof (Pais));//permanecer pais apos o termino da funcao

    strcpy (novo->nome, strNome); //inicializar nome
    novo->prox = NULL;


    if (inicio == NULL){ //caso seja o primeiro elemento da lista encadeada
        inicio = novo;
    }
    else{
        aux = inicio;

        while (aux->prox != NULL){ //localizar o final da lista encadeada
            aux = aux->prox;
        }
        aux->prox = novo; //inserir ao final da lista
    }

    return inicio;
}

/*A funcao cria uma lista encadeada com os nomes dos aliados de um pais*/
Aliados* f_cria_alianca (char* strNome, Aliados* inicioAliados)
{
    Aliados* novo, *aux;

    novo = (Aliados*) malloc (sizeof (Aliados)); //permanecer o nome na struct


    strcpy (novo->nome, strNome); //nome do aliado
    novo->prox = NULL;


    if (inicioAliados == NULL){ //caso seja o primeiro aliado
        inicioAliados = novo;
    }
    else{
        aux = inicioAliados;

        while (aux->prox != NULL){ //localizar o fim da lista encadeada
            aux = aux->prox;
        }
        aux->prox = novo; //inserir ao fim da lista encadeada
    }

    return inicioAliados;
}


/*A funcao inicializa a variavel "pais", retirando os dados do arquivo*/
Pais* f_inicializa_pais (FILE* fp, Pais* inicio)
{
    Aliados* inicioAliados; //inicio da lista encadeada com os nomes dos aliados
    Pais* aux;
    char strNome [12];
    int i;

    inicioAliados = NULL; //inicia sem aliados

    for (aux=inicio; aux != NULL; aux = aux->prox){ //coleta todas as informacoes do pais
        fscanf(fp, "%d", &aux->armas);
        fscanf(fp, "%d", &aux->forca);
        fscanf(fp, "%f", &aux->coordX);
        fscanf(fp, "%f", &aux->coordY);
        fscanf(fp, "%d", &aux->qntdAliados);

        for (i=0; i < aux->qntdAliados; i++){ //se tiver aliados, coletar o nome
            fscanf (fp, "%s", strNome);
            inicioAliados = f_cria_alianca (strNome, inicioAliados); //coloca o nome do aliado no final da lista encadeada
        }
        aux->nomesAliados = inicioAliados; //arazena a lista encadeada nas informacoes do pais



    }

    return inicio;
}

/*A funcao imprime todos os paises da lista encadeada*/
void f_imprime_pais (Pais* inicio)
{
    Pais* aux; //variavel auxiliar
    Aliados* n; //variavel auxiliar

    for(aux = inicio; aux != NULL; aux = aux->prox){
        printf ("Nome: %s\n", aux->nome);
        printf ("Armas Nucleares:%d\n", aux->armas);
        printf ("Forca:%d\n", aux->forca);
        printf ("Coordenada X:%.2f\n", aux->coordX);
        printf ("Coordenada Y:%.2f\n", aux->coordY);
        printf ("Aliados:%d\n", aux->qntdAliados);

        if (aux->qntdAliados > 0){
            printf ("Nome dos Aliados:");
            for (n = aux->nomesAliados; n != NULL; n = n->prox){
                if (strcmp (n->nome, aux->nome) != 0){
                    printf ("%s\n", n->nome);
                }
            }
        }
        printf ("\n\n");
    }
}


int main()
{

    char strNome [12], str2 [12];
    int nPais, i;
    Pais* inicio;
    FILE* fp;

    inicio = NULL; //inicializar inicio

    fp = fopen ("criptografia.txt", "r"); //abrir o arquivo de moodo leitura

    if (fp == NULL){
        printf ("Erro ao abrir o arquivo\n");
        exit (1);
    }

    fscanf (fp, "%d", &nPais); //coleta o numero de paises no arquivo


    for (i=0; i<nPais; i++){
        fscanf (fp, " %s", strNome); //coleta o nome do pais

        if (strcmp (strNome, "Reino") == 0){
            fscanf (fp, "%s", str2);
            strcat (strNome, " ");
            strcat (strNome, str2);
        }
        inicio = f_cria_pais (strNome, inicio);
    }

    inicio = f_inicializa_pais(fp, inicio);

    f_imprime_pais (inicio);

    fclose (fp);

    return 0;
}
