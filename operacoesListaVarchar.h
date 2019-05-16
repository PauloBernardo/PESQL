#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void 
insereVarchar (Varchar p, char *x)
{
   Varchar nova, aux;
   char *aux1;
   aux1 = malloc ((strlen(x) +1) * sizeof(char));
   strcpy(aux1, x);
   aux = p;
   while (aux->proximo != NULL) aux = aux->proximo;
   nova = malloc (sizeof (struct caracter));
   nova->size = aux->size;
   nova->id = aux->id + 1;
   nova->valor = malloc((nova->size + 2) * sizeof(char));
   if (strlen(aux1) > nova->size) aux1[nova->size-1] = '\0';
   strcpy (nova->valor, aux1);
   nova->proximo = aux->proximo;
   aux->proximo = nova;
}
void printListVarchar(Varchar lista){
    Varchar aux;
    aux = lista;
    while (aux != NULL) {
        printf("%d %s\n",aux->id, aux->valor);
        aux = aux->proximo;
    }
}
int * listarIdOfCollumnVarchar (Varchar lista,   int *ids) {
   Varchar aux;
    aux = lista;
    int i = 0;
    while (aux != NULL) {
       ids[i++] = aux->id;
        aux = aux->proximo;
    }
    return ids;
}
int getTamanhoListaVarchar (Varchar lista) {
   Varchar aux = lista;
   int qnt = 0;
   while (aux != NULL) {
       qnt++;
        aux = aux->proximo;
    }
    return qnt;
}
Varchar
buscaVarcharByValor (char *x, Varchar le)
{
    Varchar p;
   p = le;
   while (p != NULL && strcmp (p->valor, x) != 0)
      p = p->proximo; 
   return p;
}
Varchar
buscaVarcharById (unsigned int x, Varchar le)
{
    Varchar p;
   p = le;
   while (p != NULL && p->id != x) 
      p = p->proximo; 
   return p;
}
void 
removeVarcharById (Varchar p, unsigned int x)
{
   Varchar lixo, aux;
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
removeVarcharByValor (Varchar p, char *x)
{
   Varchar lixo, aux;
   aux = p;
   lixo = p->proximo;
   while (lixo != NULL && strcmp(lixo->valor, x) != 0) {
       aux = lixo;
       lixo = lixo->proximo;
   }
   if (lixo == NULL)
        return;
   aux->proximo = lixo->proximo;
   free (lixo);
}
