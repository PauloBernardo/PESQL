#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void 
insereChar (Char p, char x)
{
   Char nova, aux;
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   nova = malloc (sizeof (struct caracter));
   nova->valor = x;
   nova->id = aux->id + 1;
   nova->proximo = aux->proximo;
   aux->proximo = nova;
}
void printListChar(Char lista){
    Char aux;
    aux = lista;
    while (aux != NULL) {
        printf("%d %d\n",aux->id, aux->valor);
        aux = aux->proximo;
    }
}
int * listarIdOfCollumnChar (Char lista,   int *ids) {
   Char aux;
    aux = lista;
    int i = 0;
    while (aux != NULL) {
       ids[i++] = aux->id;
        aux = aux->proximo;
    }
    return ids;
}
int * listarIdOfCollumnCharByValor (Char lista, int *ids, char valor, char op) {
   Char aux;
    aux = lista;
    int i = 0;
    while (aux != NULL) {
        if (op == '='){
            if (valor ==  aux->valor) ids[i++] = aux->id;
        }
        else if (op == '>') {
            if (valor <  aux->valor) ids[i++] = aux->id;   
        }
        else if (op == '<') {
            if (valor >  aux->valor) ids[i++] = aux->id;   
        }
        aux = aux->proximo;
    }
    return ids;
}
int getTamanhoListaChar (Char lista) {
   Char aux = lista;
   int qnt = 0;
   while (aux != NULL) {
       qnt++;
        aux = aux->proximo;
    }
    return qnt;
}
Char
buscaCharByValor (char x, Char le)
{
    Char p;
   p = le;
   while (p != NULL && p->valor != x) 
      p = p->proximo; 
   return p;
}
Char
buscaCharById (unsigned int x, Char le)
{
    Char p;
   p = le;
   while (p != NULL && p->id != x) 
      p = p->proximo; 
   return p;
}
void 
removeCharById (Char p, unsigned int x)
{
   Char lixo, aux;
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
removeCharByValor (Char p, char x)
{
   Char lixo, aux;
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
