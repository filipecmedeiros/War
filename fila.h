#ifndef fila.h
#define fila.h

typedef struct lista{
    char ataque [12];
    char defesa [12];
    struct lista *prox;
}Lista;

typedef struct fila {
    Lista *ini;
    Lista *fim
}Fila;

/*Cria uma fila*/
Fila* fila_cria ( ) {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

/*insere um elemento no final da fila*/
void fila_insere (Fila* f, char* ataque, char* defesa) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    strcpy (novo->ataque, ataque);
    strcpy (novo->defesa, defesa);
    novo->prox = NULL; /* novo nó passa a ser o último */

    if (!fila_vazia(f)) /* verifica se a fila não estava vazia */
        f->fim->prox = novo;
    else
        f->ini = novo;

    f->fim = novo;
}


/*Retira o primeiro elemento da fila | OBS: a funcao nao retorna o elemento retirado*/
Lista fila_retira (Fila* f) {
    Lista* t;
    Lista v;

    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
    }

    t = f->ini;
    strcpy (v->ataque, t->ataque);
    strcpy (v->defesa, t->defesa);
    f->ini = t->prox;

    if (f->ini == NULL)
        f->fim = NULL;

    free(t);

    return v;
}

/*diz se a fila esta vazia*/
int fila_vazia (Fila* f) {
    return (f->ini == NULL);
}

/*libera a fila*/
void fila_libera (Fila* f) {
    Lista* q = f->ini;
    while (q!=NULL) {
        Lista* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}


/* Função que informa o primeiro elemento da fila*/
char* fila_primeiro (Fila* f) {
    return (f->ini->ataque);
}

/* Função que imprime os elementos da fila*/
void fila_imprime (Fila* f) {
    Lista* q;
    for (q=f->ini; q!=NULL; q =q->prox)
        printf("%s ataca %s\n", q->ataque, q->defesa);
}


#endif // fila.h
