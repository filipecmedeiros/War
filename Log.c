#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fila.h>

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

/*A funcao retira um aliado da lista, dado a lista e o nome a ser retirado*/
Aliados* f_retira_da_lista (Aliados* lista, char nome [12]){
    Aliados* aux, *copia;
    int alianca;

    alianca = 1;
    for (aux = lista; alianca != 0; ){ //localizar o nome na lista encadeada
        alianca = strcmp (aux->nome, nome);

        if (alianca != 0){ //so receber o proximo elemento caso nao tenha achado
            aux = aux->prox;
        }
    }

    for (copia = lista; copia->prox != aux; copia = copia->prox){ //copia aponta pro elemento anterior ao que sera retirado
    }

    copia->prox = aux->prox;//copia retira o elemento da lista

    free (aux); //libera o espaco

    return lista;
}

/*A funcao recebe uma lista de aliados e uma string e compara se são aliados. se for, retorna 0*/
int f_verifica_alianca (Aliados* lista, char* pais2)
{
    int alianca;

    while (lista != NULL){
        alianca = strcmp (lista->nome, pais2); //verifica se as strings sao iguais

        lista = lista->prox;

        if (alianca == 0){ //se tiver encontrado que é aliado, pare de procurar
            lista = NULL;
        }
    }

    return alianca;
}

/*A funcao retira um pais que foi destruido da lista encadeada*/
Pais* f_pais_destruido (Pais* morto, Pais* inicio)
{
    Pais* aux, *copia;
    int alianca;
    Aliados* lista;



    for (aux = inicio; aux->prox != morto; aux = aux->prox){ //aux aponta pro pais q sera retirado da lista
    }

    printf ("aux = %s\n", aux->nome);

    for (copia = inicio; copia->prox != aux; ){ //copia aponta pro pais anterior ao que sera retirado

        if (copia->prox != aux){
            copia = copia->prox;
        }
    }
    copia->prox = aux->prox;

    if (aux->qntdAliados > 0){//caso o pais tbm tenha aliados, deve ser retirado da lista

        copia = inicio;
        while (copia != NULL){

            alianca = f_verifica_alianca (copia->nomesAliados, aux->nome); //verifica se sao aliados
            if (alianca == 1){ //se for aliado, sera retirado da lista
                lista = copia->nomesAliados; //copia a lista de aliados
                copia->nomesAliados = f_retira_da_lista (lista, aux->nome); //retira da lista de aliados
            }

            copia = copia->prox; //verifica o proximo pais
        }
    }


    free (aux);
    return inicio;
}

/*A funcao recebe como parametros dois paises (o que ataca e o que defende) e debita o valor do ataque*/
Pais* f_ataque (Pais* ataque, Pais* defesa, Pais* inicio)
{
    Aliados* lista;
    int aceita;
    Pais* aux;

    if (ataque->qntdAliados > 0){ //se tiver aliado, verificar se esta atacando o aliado
            lista = ataque->nomesAliados;

            aceita = f_verifica_alianca (lista, defesa->nome); //se aceita for == 0, sao aliados
    }

    if (aceita != 0){ //caso os paises nao aliados

        if (ataque->armas == 1){ //verificar se e nuclear
            printf ("%s lancou um ICBM nuclear contra %s\n", ataque->nome, defesa->nome);
        }
        else{ //caso nao seja nuclear
            printf ("%s lancou um ICBM comum contra %s\n", ataque->nome, defesa->nome);
        }

        //sincronizar pra chegar junto com a imagem

        if (ataque->forca >0){ //verifica se ainda esta vivo

            if (ataque->armas == 1){ //debitar icbm nuclear
                defesa->forca = defesa->forca - 50;
                printf ("O ICBM atinge %s, forca militar reduzida para 50.\n", defesa->nome);
            }

            else{ //debitar icbm comum
                defesa->forca = defesa->forca - 10;
                printf ("O ICBM atinge %s, forca militar reduzida para 10.\n", defesa->nome);
            }

        }

        if (defesa->forca <= 0){
            defesa->forca = 0;
            printf ("%s foi destruido\n", defesa->nome);

            inicio = f_pais_destruido (defesa, inicio); //retira o pais da lista de paises e da lista de aliados
        }
    }






    else{ //caso o ataque seja para um aliado
        printf ("ataque nao foi possivel\n");
    }


    return inicio;
}

/*A funcao define o estopim e armazena na fila de ataques*/
Fila* f_estopim (Fila* fila)
{
    Pais* aux;
    int j;
    Pais* ataque, *defesa;

    printf ("\n\nEstopim:\n");

    for (aux = inicio, j = 1; aux != NULL; j++, aux = aux->prox){ //exibe um menu com todos os paises para atacar
        printf ("%d.%s Ataca\n", j, aux->nome);
    }
    scanf ("%d", &j); //pega o "código" do pais

    for (ataque = inicio; j>1; j--){
        ataque = ataque->prox;
    }

    for (aux = inicio, j = 1; aux != NULL; j++, aux = aux->prox){ //exibe um menu com todos os paises para receber o ataque
        printf ("%d.%s defende\n", j, aux->nome);
    }
    scanf ("%d", &j);//pega o "código" do pais

    for (defesa = inicio; j > 1; j--){//ponteiro pro pais que o usuario indicou
        defesa = defesa->prox;
    }


    fila_insere (fila, ataque, defesa);

    return fila;
}

/*A funcao recebe o ataque e a defesa, verifica se tem aliado e contra-ataca caso tenha, colocando na fila de ataques*/
Fila* f_contra_ataque (Fila* fila, char* ataque, char* defesa, Pais* inicio)
{
    Pais* aux, *novo;
    Aliados* alianca;
    int compara;

    novo = inicio;
    compara = 1;
    while (compara != 0){ //procura o pais atacado na lista
        compara = strcmp (novo->nome, defesa);

        if (compara != 0)
            novo = novo->prox;
    } //novo aponta pro pais que foi atacado

    if (novo->qntdAliados > 0){ //se o pais atacado tiver aliados
        alianca = novo->nomesAliados; //copia o nome dos aliados

        while (alianca != NULL){ //enquanto tiver aliados na lista

            aux = inicio;
            compara = 1;
            while (compara != 0){ //procura aliado na lista
                compara = strcmp (alianca->nome, aux->nome);

                if (compara != 0)
                    aux = aux->prox;
            }

            fila_insere (fila, aux->nome, ataque); //aliado contra-ataca

            alianca = alianca->prox;
        }

    }

    fila_insere (fila, defesa, ataque); //o pais atacado tambem contra-ataca

    return fila; //atualiza fila de ataques
}


int main()
{
    char strNome [12], str2 [12];
    int nPais, i;
    Pais* inicio;
    FILE* fp;

    inicio = NULL;


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











/*--------------------------*/
    Fila* fila;
    Lista aux;

    fila_cria (fila);


    fila = f_estopim (fila); //fila contem 2 strings (o ataque e a defesa)

    do{
    aux = fila_retira (fila); //aux retira o proximo elemento da fila

    inicio = f_ataque (aux->ataque, aux->defesa, inicio); //chamada de ataque
    fila = f_contra_ataque (fila, aux->ataque, aux->defesa, inicio); //chamada de contra-ataque


    printf ("\n\n");
    f_imprime_pais (inicio);

    } while (!fila_vazia (fila));



    return 0;
}
