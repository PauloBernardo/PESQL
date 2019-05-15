#include <stdio.h>
#include <stdbool.h>
#include <string.h>


DataBase createDataBaseSQL (DataBase raiz, char **processado, int tam) {
    DataBase novo;
    novo = malloc (sizeof(struct database));
    novo->name = malloc (255 * sizeof(char));
    //printf("%s\n", processado[2]);
    strcpy (novo->name, processado[2]);
    //printf("%s\n", novo->name);
    return addDataBase(raiz, novo);
}
DataBase createTableSQL (DataBase db, char **processado) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table novo;
    novo = malloc (sizeof(struct table));
    novo->name = malloc (255 * sizeof(char));
    //printf("%s\n", processado[2]);
    strcpy (novo->name, processado[2]);
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
void showCollumnsSQL (DataBase db, char *table) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    printCollumns (selectedTable->columns);
}
DataBase useDataBaseSQL (DataBase raiz, char *database) {
    DataBase db = buscaDataBase(raiz, database);
    if (db == NULL) {
        printf ("Erro, database não existe\n");
    }
    return db;
}
void showTablesSQL (DataBase db) {
    if (db == NULL){
        printf ("Database não selecionado.\n");
        return;
    }
    printTables (db->tables);
}

void describeSQL (DataBase db,char * table) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    printf ("| NOME | TIPO |\n");
    printCollumnsCompleto(selectedTable->columns);
}

DataBase alterTableDropSQL (DataBase db, char * table, char *collumn) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    selectedTable->columns = removeCollumn(selectedTable->columns, collumn);
    return db;
}
DataBase alterTableAddSQL (DataBase db, char **processado, int tam) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, processado[2]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
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
    strcpy (novo->name, processado[5]);
    switch (getType(processado[6]))
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
        int size = getSize (processado, tam);
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
        printf ("Erro, tipo da coluna não suportado.\n");
        break;
    }
    selectedTable->columns = addCollumn (selectedTable->columns, novo);
    return db;
}

DataBase alterTableModifySQL (DataBase db, char **processado, int tam) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, processado[2]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    if (selectedTable->columns == NULL) {
         printf ("Erro, collumn não existe.\n");
        return db;
    }
    Collumn collumn = buscaCollumn(selectedTable->columns, processado[5]);
    if (collumn == NULL) {
         printf ("Erro, collumn não existe.\n");
        return db;
    }
    switch (getType(processado[6]))
    {
    case 1:
        strcpy (collumn->tipo,"INTEGER");
        Integer init;
        init = malloc(sizeof (struct integer));
        init->id = 0;
        init->valor = 0;
        collumn->integers =  init;
        break;
    case 2:
        strcpy(collumn->tipo,"BOOLEAN");
        Booleano init1;
        init1 = malloc(sizeof (struct boolean));
        init1->id = 0;
        init1->valor = false;
        collumn->booleans =  init1;
        break;
    case 3:
        strcpy (collumn->tipo,"VARCHAR");
        int size = getSize (processado, tam);
        Varchar inicio;
        inicio = malloc(sizeof (struct varchar));
        inicio->id = 0;
        inicio->size = size;
        inicio->valor = malloc((inicio->size +1) *sizeof(char));
        strcmp (inicio->valor , " ");
        collumn->varchars =  inicio;
        break;
    case 4:
        strcpy (collumn->tipo,"CHAR");
        Char init2;
        init2 = malloc(sizeof (struct caracter));
        init2->id = 0;
        init2->valor = 0;
        collumn->chars =  init2;
        break;
    default:
        printf ("Erro, tipo da coluna não suportado.\n");
        break;
    }
    return db;
}

DataBase insertIntoValuesSQL (DataBase db, char *table, char *collumns, char *values) {
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return db;
    }
    Table selectedTable = buscaTable (db->tables, table);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return db;
    }
    char help [5] = {'(', ')',',' ,' ','\0'};
    char **nomeColunas = splitByChars (collumns, help);
    char **valores = splitByChars(values, help);
    int numeroColunas = 0, numeroValores = 0, j;
    for (j = 0; j < 255 && nomeColunas[j] != NULL; j++) numeroColunas++;
    for (j = 0; j < 255 && valores[j] != NULL; j++) numeroValores++;
    if (numeroColunas != numeroValores) {
        printf ("Erro: Inconsistencia nos dados.\n");
        return db;
    } 
    for (j =0 ; j < numeroColunas-1; j++) {
        Collumn collumn = buscaCollumn(selectedTable->columns, nomeColunas[j]);
        if (collumn == NULL) {
            printf ("Erro: Coluna %s não existe.\n", nomeColunas[j]);
            return db;
        }
        switch (getType(collumn->tipo))
        {
        case 1:
            if (!verificaInteiro (valores[j])) {
                printf ("Valor %d da coluna %s não é inteiro!\n", j, collumn->name);
                return db;
            }
            break;
        case 2:
            if (!verificaBoolean (valores[j])) {
                printf ("Valor %d da coluna %s não é booleano!\n", j, collumn->name);
                return db;
            }
            break;
        case 3:
            if (!verificaVarchar (valores[j])) {
                printf ("Valor %d da coluna %s não é string!\n", j, collumn->name);
                return db;
            }
            break;
        case 4:
            if (!verificaChar (valores[j])) {
                printf ("Valor %d da coluna %s não é char!\n", j, collumn->name);
                return db;
            }
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    }
    printf ("SUCESSO!\n");
    return db;
}