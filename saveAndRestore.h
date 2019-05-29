#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void writeDB (FILE *file, DataBase db);
void writeTable (FILE *file, Table db);
void writeCollumn (FILE *file, Collumn db);
void writeInteiros (FILE *file, Integer valor);
void writeBoolean (FILE *file, Booleano valor);
void writeVarchars (FILE *file, Varchar valor);
void writeChars (FILE *file, Char valor);

void save (char *nomeArquivo, DataBase db) {
    //printf("Salvando..\n");
    FILE *file;
    file = fopen(nomeArquivo, "w");
    writeDB(file, db);
    fclose(file);
}

void writeDB (FILE *file, DataBase db) {
    //printf("Escrevendo DataBase..\n");
    if (db == NULL) return;
    fprintf(file, "0,%s\n", db->name);
    writeTable (file, db->tables);
    writeDB(file, db->direita);
    writeDB(file, db->esquerda);
}

void writeTable (FILE *file, Table db) {
    //printf("Escrevendo Table..\n");
    if (db == NULL) return;
    fprintf(file, "1,%s\n", db->name);
    writeCollumn (file, db->columns);
    writeTable(file, db->direita);
    writeTable(file, db->esquerda);
}


void writeCollumn (FILE *file, Collumn db) {
    //printf("Escrevendo Collumn..\n");
    if (db == NULL) return;
    fprintf(file, "2,%s,%s\n", db->name, db->tipo);
    
    switch (getType(db->tipo))
    {
    case 1:
        writeInteiros(file, db->integers);
        break;
    case 2:
        writeBoolean(file, db->booleans);
        break;
    case 3:
        writeVarchars(file, db->varchars);
        break;
    case 4:
        writeChars(file, db->chars);
        break;
    default:
        break;
    }
    writeCollumn(file, db->direita);
    writeCollumn(file, db->esquerda);
}

void writeInteiros (FILE *file, Integer valor) {
    //printf ("Escrevendo inteiros\n");
    if (valor == NULL) return;
    fprintf(file, "3,%d,%d\n", valor->id, valor->valor);
    writeInteiros(file, valor->proximo);
}
void writeBoolean (FILE *file, Booleano valor) {
    if (valor == NULL) return;
    fprintf(file, "3,%d,%d\n", valor->id, valor->valor);
    writeBoolean(file, valor->proximo);
}
void writeVarchars (FILE *file, Varchar valor) {
    if (valor == NULL) return;
    fprintf(file, "3,%d,%s\n", valor->id, valor->valor);
    writeVarchars(file, valor->proximo);
}
void writeChars (FILE *file, Char valor) {
    if (valor == NULL) return;
    fprintf(file, "3,%d,%c\n", valor->id, valor->valor);
    writeChars(file, valor->proximo);
}

DataBase createTableRestore (DataBase db, FILE *file, char *nomeTable) {
    Table novo;
    novo = malloc (sizeof(struct table));
    novo->name = malloc (255 * sizeof(char));
    //printf("%s\n", processado[2]);
    strcpy (novo->name, splitByChars(nomeTable, ",")[1]);
    //printf("%s\n", novo->name);
    if (db->tables == NULL) {
        Table raiz;
        raiz = malloc (sizeof(struct table));
        raiz->name = malloc (255 * sizeof(char));
        //printf("%s\n", processado[2]);
        strcpy (raiz->name, "NNNNNNNNNNNNNNNNNN");
        db->tables = raiz;
    }
    db->tables = addTable(db->tables, novo);
    return db;
}

DataBase criaNovoDataBase (DataBase raiz, FILE *file, char *dataBaseName) {
       // printf("oi");
        DataBase novo;
        novo = malloc (sizeof(struct database));
        novo->name = malloc (255 * sizeof(char));
        char **processado = splitByChars (dataBaseName, ",");
        processado[1][strlen(processado[1])-1] = '\0';
        //printf("%s\n", processado[2]);
        strcpy (novo->name, processado[1]);
        //printf("%s\n", novo->name);
        while (fgets(dataBaseName, 255, file)) {
            if (dataBaseName[0] == '1') {
                novo = createTableRestore (novo, file, dataBaseName);
            }
        }
        return addDataBase(raiz, novo);
}

DataBase restore (char *nomeArquivo) {
    FILE *file;
    DataBase raiz;
    raiz = malloc(sizeof(struct database));
    raiz->name = malloc (255* sizeof(char));
    strcpy (raiz->name, "NNNNNNNNNNNNNNNNNN");
    char *aux, *repetido;
    aux = malloc(255 * sizeof(char));
    repetido = malloc(255 * sizeof(char));
    strcpy(repetido, "lixo");
    file = fopen(nomeArquivo, "r");
    while (fgets(aux, 255, file)) {
        if (aux[0] == '0') {
           raiz = criaNovoDataBase (raiz, file, aux);
        }
        printf ("%s", aux);
    }
    return raiz;
}