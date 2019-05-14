#include <stdio.h>
#include <stdlib.h>
#include <string.h>
DataBase addDataBase (DataBase db, DataBase novo) { 
    if (db == NULL) return novo;
    if (strcmp(db->name, novo->name) > 0) 
       db->esquerda = addDataBase (db->esquerda, novo);
    else if (strcmp(db->name, novo->name) < 0)
       db->direita = addDataBase (db->direita, novo);
    else
        printf("Erro, banco já existe");
    return db;
}
void printDataBases (DataBase raiz) {
   if (raiz != NULL) {
      if (strcmp(raiz->name, "NNNNNNNNNNNNNNNNNN"))
         printf ("%s\n", raiz->name);
      printDataBases (raiz->esquerda);
      printDataBases(raiz->direita);
   }
}
void printTables (Table raiz) {
   if (raiz != NULL) {
      if (strcmp(raiz->name, "NNNNNNNNNNNNNNNNNN"))
         printf ("%s\n", raiz->name);
      printTables (raiz->esquerda);
      printTables(raiz->direita);
   }
}
Table addTable (Table db, Table novo) { 
    if (db == NULL) return novo;
    if (strcmp(db->name, novo->name) > 0) 
       db->esquerda = addTable (db->esquerda, novo);
    else if (strcmp(db->name, novo->name) < 0)
       db->direita = addTable (db->direita, novo);
    else
        printf("Erro, table já existe");
    return db;
}
Collumn addCollumn (Collumn db, Collumn novo) { 
   //printf("Adicionando collumn\n");
    if (db == NULL) return novo;
    if (strcmp(db->name, novo->name) > 0) 
       db->esquerda = addCollumn (db->esquerda, novo);
    else if (strcmp(db->name, novo->name) < 0)
       db->direita = addCollumn (db->direita, novo);
    else
        printf("Erro, coluna já existe");;
    return db;
}
 DataBase removeraizDatabase (DataBase r) {  
    struct database *p, *q;
    if (r->esquerda == NULL) {
       q = r->direita;
       free (r);
       return q;
    }
    p = r; q = r->esquerda;
    while (q->direita != NULL) {
       p = q; q = q->direita;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->direita = q->esquerda;
       q->esquerda = r->esquerda;
    }
    q->direita = r->direita;
    free (r);
    return q;
}
Table removeraizTable (Table r) {  
    struct table *p, *q;
    if (r->esquerda == NULL) {
       q = r->direita;
       free (r);
       return q;
    }
    p = r; q = r->esquerda;
    while (q->direita != NULL) {
       p = q; q = q->direita;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->direita = q->esquerda;
       q->esquerda = r->esquerda;
    }
    q->direita = r->direita;
    free (r);
    return q;
}
Collumn removeraizCollumn (Collumn r) {  
    Collumn p, q;
    if (r->esquerda == NULL) {
       q = r->direita;
       free (r);
       return q;
    }
    p = r; q = r->esquerda;
    while (q->direita != NULL) {
       p = q; q = q->direita;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->direita = q->esquerda;
       q->esquerda = r->esquerda;
    }
    q->direita = r->direita;
    free (r);
    return q;
}
DataBase buscaDataBase (DataBase r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
       return r;
    if (strcmp (r->name, k) > 0)
       return  buscaDataBase (r->esquerda, k);
    else
       return buscaDataBase (r->direita, k);
}
Table buscaTable (Table r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
       return r;
    if (strcmp (r->name, k) > 0)
       return  buscaTable (r->esquerda, k);
    else
       return buscaTable (r->direita, k);
}
Collumn buscaCollumn (Collumn r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
       return r;
    if (strcmp (r->name, k) > 0)
       return  buscaCollumn (r->esquerda, k);
    else
       return buscaCollumn (r->direita, k);
}
DataBase removeDatabase (DataBase r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
        return removeraizDatabase(r);
    if (strcmp (r->name, k) > 0)
       r->esquerda =  removeDatabase (r->esquerda, k);
    else
       r->direita = removeDatabase (r->direita, k);
}
Table removeTable (Table r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
        return removeraizTable(r);
    if (strcmp (r->name, k) > 0)
       r->esquerda =  removeTable (r->esquerda, k);
    else
       r->direita = removeTable (r->direita, k);
}
Collumn removeCollumn (Collumn r, char *k) {
    if (r == NULL || strcmp(r->name,k) == 0)
        return removeraizCollumn(r);
    if (strcmp (r->name, k) > 0)
       r->esquerda =  removeCollumn (r->esquerda, k);
    else
       r->direita = removeCollumn (r->direita, k);
}
/* Lista encadeada */
/* Boolean */
void 
insereBoolean (Booleano p, bool x)
{
   Booleano nova, aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   nova = malloc (sizeof (struct boolean));
   nova->valor = x;
   nova->id = aux->id + 1;
   nova->proximo = aux->proximo;
   aux->proximo = nova;
}
void printListBooleano(Booleano lista){
    Booleano aux;
    aux = lista;
    while (aux != NULL) {
        printf("%d %d\n",aux->id, aux->valor);
        aux = aux->proximo;
    }
}
Booleano
buscaBooleanoByValor (int x, Booleano le)
{
    Booleano p;
   p = le;
   while (p != NULL && p->valor != x) 
      p = p->proximo; 
   return p;
}
Booleano
buscaBooleanById (int x, Booleano le)
{
    Booleano p;
   p = le;
   while (p != NULL && p->id != x) 
      p = p->proximo; 
   return p;
}
void 
removeBooleanById (Booleano p, unsigned int x)
{
   Booleano lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->id != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}
void 
removeBooleanByValor (Booleano p, int x)
{
   Booleano lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->valor != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}

/* Integer */
void 
insereInteger (Integer p, int x)
{
   Integer nova, aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   nova = malloc (sizeof (struct integer));
   nova->valor = x;
   nova->id = aux->id + 1;
   nova->proximo = aux->proximo;
   aux->proximo = nova;
}
void printList(Integer lista){
    Integer aux;
    aux = lista;
    while (aux != NULL) {
        printf("%d %d\n",aux->id, aux->valor);
        aux = aux->proximo;
    }
}
Integer
buscaIntegerByValor (int x, Integer le)
{
    Integer p;
   p = le;
   while (p != NULL && p->valor != x) 
      p = p->proximo; 
   return p;
}
Integer
buscaIntegerById (int x, Integer le)
{
    Integer p;
   p = le;
   while (p != NULL && p->id != x) 
      p = p->proximo; 
   return p;
}
void 
removeIntegerById (Integer p, unsigned int x)
{
   Integer lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->id != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}
void 
removeIntegerByValor (Integer p, int x)
{
   Integer lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && lixo->valor != x) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}

