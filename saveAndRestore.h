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
DataBase criaCollumnRestore (DataBase raiz, DataBase db, Table selectedTable, char **processado, FILE *file);
DataBase createTableRestore (DataBase raiz, DataBase db, FILE *file, char *nomeTable);
DataBase criaNovoDataBase (DataBase raiz, FILE *file, char *dataBaseName);

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
    fprintf(file, "3,%d,%s,%d\n", valor->id, valor->valor, valor->size);
    writeVarchars(file, valor->proximo);
}
void writeChars (FILE *file, Char valor) {
    if (valor == NULL) return;
    fprintf(file, "3,%d,%c\n", valor->id, valor->valor);
    writeChars(file, valor->proximo);
}
Collumn addValueRestore (DataBase raiz, DataBase db, Table selectedTable, Collumn collumn, char **processado,FILE *file) { 
    Integer novo;
    Booleano novo1;
    Varchar novo2;
    Char novo3;
    if (atoi(processado[1]) == 0) {
        return collumn;
    }
    switch (getType(collumn->tipo))
    {
    case 1:
        novo = malloc(sizeof(struct integer));
        novo->id = atoi(processado[1]);
        novo->valor = atoi(processado[2]);
        restoreInteger(collumn->integers, novo);
        break;
    case 2:
        
        novo1 = malloc(sizeof(struct boolean));
        novo1->id = atoi(processado[1]);
        novo1->valor = atoi(processado[2]);
        restoreBoolean(collumn->booleans, novo1);
        break;
    case 3:
        
        novo2 = malloc(sizeof(struct varchar));
        novo2->id = atoi(processado[1]);
        novo2->size = atoi(processado[3]);
        novo2->valor = malloc ((novo2->size+1) * sizeof(char));
        if (processado[2][strlen(processado[2])-1] == '\n')
            processado[2][strlen(processado[2])-1] = '\0';
        strcpy (novo2->valor, processado[2]);
        restoreVarchar(collumn->varchars, novo2);
        break;
    case 4:
       
        novo3 = malloc(sizeof(struct caracter));
        novo3->id = atoi(processado[1]);
        novo3->valor = processado[2][0];
        restoreChar(collumn->chars, novo3);
        break;
    default:
        break;
    }
    char *aux;
    aux = malloc(255*sizeof(char));
    while (fgets(aux, 255, file)) {
        if (aux[0] == '1') {
            db = createTableRestore (raiz, db, file, aux);
        }
        if (aux[0] == '0') raiz = criaNovoDataBase(raiz, file, aux);
        if (aux[0] == '2') db = criaCollumnRestore (raiz, db, selectedTable, splitByChars(aux, ","), file);
        if (aux[0] == '3') collumn = addValueRestore (raiz, db, selectedTable, collumn, splitByChars(aux, ","), file);
    }
    return collumn;
}
DataBase criaCollumnRestore (DataBase raiz, DataBase db, Table selectedTable, char **processado, FILE *file) {
    //printf("%s\n", processado[2]);
    if (processado[2][strlen(processado[2]) -1] == '\n') {
        processado[2][strlen(processado[2]) -1] = '\0';
    } else {
        processado[3][strlen(processado[3]) -1] = '\0';
    }
    if (selectedTable->columns == NULL) {
        Collumn inicial;
        inicial = malloc (sizeof(struct collumn));
        inicial->name = malloc (255 * sizeof(char));
        //printf("%s\n", processado[2]);
        strcpy (inicial->name, "NNNNNNNNNNNNNNNNNN");
        selectedTable->columns = inicial;
    }
    Collumn novo;
    novo = malloc (sizeof(struct collumn));
    novo->name = malloc (255 * sizeof(char));
    novo->tipo = malloc (20 * sizeof(char));
    strcpy (novo->name, processado[1]);

    //printf ("%d\n", tamanhoLista);
    switch (getType(processado[2]))
    {
    case 1:
        strcpy (novo->tipo,"INTEGER");
        Integer init;
        init = malloc(sizeof (struct integer));
        init->id = 0;
        init->valor = 0;
        novo->integers =  init;
        break;
    case 2:
        strcpy(novo->tipo,"BOOLEAN");
        Booleano init1;
        init1 = malloc(sizeof (struct boolean));
        init1->id = 0;
        init1->valor = false;
        novo->booleans =  init1;
        break;
    case 3:
        strcpy (novo->tipo,"VARCHAR");
        int size = 255;
        //printf ("%d\n", size);
        Varchar inicio;
        inicio = malloc(sizeof (struct varchar));
        inicio->id = 0;
        inicio->size = size;
        inicio->valor = malloc((inicio->size +1) *sizeof(char));
        strcmp (inicio->valor , " ");
        novo->varchars =  inicio;
        break;
    case 4:
        strcpy (novo->tipo,"CHAR");
        Char init2;
        init2 = malloc(sizeof (struct caracter));
        init2->id = 0;
        init2->valor = 0;
        novo->chars =  init2;
        break;
    default:
       // printf ("Erro, tipo da coluna não suportado.\n");
        return db;
        break;
    }
    selectedTable->columns = addCollumn (selectedTable->columns, novo);
    char *aux;
    aux = malloc(255*sizeof(char));
    while (fgets(aux, 255, file)) {
        if (aux[0] == '1') {
            db = createTableRestore (raiz, db, file, aux);
        }
        if (aux[0] == '0') raiz = criaNovoDataBase(raiz, file, aux);
        if (aux[0] == '2') db = criaCollumnRestore (raiz, db, selectedTable, splitByChars(aux, ","), file);
        if (aux[0] == '3') novo = addValueRestore (raiz, db, selectedTable, novo, splitByChars(aux, ","), file);
    }
     
    // printf("%s\n", processado[2]);
    return db;
}


DataBase createTableRestore (DataBase raiz, DataBase db, FILE *file, char *nomeTable) {
    Table novo;
    novo = malloc (sizeof(struct table));
    novo->name = malloc (255 * sizeof(char));
    //printf("%s\n", processado[2]);
    nomeTable = splitByChars(nomeTable, ",")[1];
    nomeTable[strlen(nomeTable)-1] = '\0';
    strcpy (novo->name, nomeTable);
    //printf("%s\n", novo->name);
    if (db->tables == NULL) {
        Table raiz;
        raiz = malloc (sizeof(struct table));
        raiz->name = malloc (255 * sizeof(char));
        //printf("%s\n", processado[2]);
        strcpy (raiz->name, "NNNNNNNNNNNNNNNNNN");
        db->tables = raiz;
    }
    char *aux;
    aux = malloc(255*sizeof(char));
    while (fgets(aux, 255, file)) {
        if (aux[0] == '1') {
            db = createTableRestore (raiz, db, file, aux);
        }
        if (aux[0] == '0') raiz = criaNovoDataBase(raiz, file, aux);
        if (aux[0] == '2') db = criaCollumnRestore (raiz, db, novo, splitByChars(aux, ","), file);
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
                novo = createTableRestore (raiz, novo, file, dataBaseName);
            }
            if (dataBaseName[0] == '0') raiz = criaNovoDataBase(raiz, file, dataBaseName);
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
       // printf ("%s", aux);
    }
    return raiz;
}