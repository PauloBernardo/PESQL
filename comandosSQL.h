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
    for (j =0 ; j < numeroColunas-1; j++) {
        Collumn collumn = buscaCollumn(selectedTable->columns, nomeColunas[j]);
        switch (getType(collumn->tipo))
        {
        case 1:
            insereInteger(collumn->integers, atoi (valores[j]));
            break;
        case 2:
            if (strcmp (valores[j], "TRUE") == 0) {
                insereBoolean (collumn->booleans, true);
            } else {
                insereBoolean(collumn->booleans, false);
            }
            break;
        case 3:
            insereVarchar(collumn->varchars, valores[j]);
            break;
        case 4:
            insereChar(collumn->chars, valores[j][1]);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
    }
    //PREENCHER OS CAMPOS NÃO INSERIDOS COM VALORES NULOS
    int numero = numeroDeColunas(selectedTable->columns);
    //SE FOREM IGUAIS NÃO É PRECISO VERIFICAR
    if (numero == numeroColunas) {
        printf ("SUCESSO!\n");
        return db;
    } 
    int i , flag;
    char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
    for (j = 1; j < numero; j++) {
        flag = 1;
        for (i = 0; i < numeroColunas-1; i++) {
        if (strcmp( todasColunas[j], nomeColunas[i]) == 0 ) flag = 0;
        }
        if (flag) {
            Collumn collumn = buscaCollumn(selectedTable->columns, todasColunas[j]);
            switch (getType(collumn->tipo))
            {
                case 1:
                    insereInteger(collumn->integers, 0);
                    break;
                case 2:
                    if (strcmp (valores[j], "TRUE") == 0) {
                        insereBoolean (collumn->booleans, false);
                    }
                    break;
                case 3:
                    insereVarchar(collumn->varchars, "");
                    break;
                case 4:
                    insereChar(collumn->chars, 0);
                    break;
                default:
                    printf ("Erro, tipo da coluna não suportado.\n");
                    break;
            }
        }
    }
    printf ("SUCESSO!\n");
    return db;
}
void selectFromSQL (DataBase db, char **processado, int tam, int num) {
    int i, j;
    char *colunas;
    if (db == NULL) {
        printf ("Erro, banco de dados não selecionado.\n");
        return;
    }
    Table selectedTable = buscaTable (db->tables, processado[num+1]);
    if (selectedTable == NULL) {
        printf ("Erro, table não existe.\n");
        return;
    }
    colunas = malloc(255 * sizeof(char));
    strcpy (colunas, "");
    for (i = 1; i < num; i++) {
        strcat (colunas, processado[i]);
    }
    if (colunas[strlen(colunas)-1] ==  ',') {
        printf ("Erro de sintaxe identicado.\n");
        return;
    }
    char **nomeColunas = splitByChars (colunas, ",");
    int numeroColunasPesquisadas = 0;
    for (i = 0; i < 255 && nomeColunas[i] != NULL; i++) {
         //printf("%s\n", nomeColunas[i]);
         numeroColunasPesquisadas++;
    }
    if (strcmp(nomeColunas[0], "*") == 0) {
        int numero = numeroDeColunas(selectedTable->columns);
        char **todasColunas = splitByChars (getNomeColunas(selectedTable->columns), ",");
        Collumn *collumns;
        collumns = malloc (numero * sizeof(Collumn));
        for (i = 1, j= 0; i < numero && todasColunas[i] != NULL; i++, j++) {
            collumns[j] = buscaCollumn(selectedTable->columns, todasColunas[i]);
        }
       // printf ("OPA");
        //printf ("%s\n", collumns[0]->tipo);
        
        int *listaIDs, tamanhoLista;
        switch (getType(collumns[0]->tipo))
        {
        case 1:
            tamanhoLista = getTamanhoListaInteger (collumns[0]->integers);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
             listaIDs = listarIdOfCollumnInteger (collumns[0]->integers, listaIDs);
            break;
        case 2:
            tamanhoLista = getTamanhoListaBoolean (collumns[0]->booleans);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnBoolean (collumns[0]->booleans, listaIDs);
            break;
        case 3:
            tamanhoLista = getTamanhoListaVarchar (collumns[0]->varchars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnVarchar(collumns[0]->varchars, listaIDs);
            break;
        case 4:
            tamanhoLista = getTamanhoListaChar (collumns[0]->chars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnChar(collumns[0]->chars, listaIDs);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
        for (int i = 1; i < numero; i++) {
            printf ("| %s |", todasColunas[i]);
        }
        printf ("\n");
        Collumn aux;
        for (i = 1; i < tamanhoLista; i++) {
            for (j = 1; j < numero; j++) {
                aux = buscaCollumn (selectedTable->columns, todasColunas[j]);
                switch (getType(aux->tipo)) {
                    case 1:
                        printf ("| %d |", buscaIntegerById(listaIDs[i], aux->integers)->valor);
                        break;
                    case 2:
                        printf ("| %d |", buscaBooleanById(listaIDs[i], aux->booleans)->valor);
                        break;
                    case 3:
                        printf ("| %s |", buscaVarcharById(listaIDs[i], aux->varchars)->valor);
                        break;
                    case 4:
                        printf ("| %c |", buscaCharById(listaIDs[i], aux->chars)->valor);
                        break;
                }
            }
            printf ("\n");
        }
            
    } else {
        Collumn *collumns;
        collumns = malloc (numeroColunasPesquisadas * sizeof(Collumn));
        for (i = 0, j= 0; i < numeroColunasPesquisadas && nomeColunas[i] != NULL; i++, j++) {
            collumns[j] = buscaCollumn(selectedTable->columns, nomeColunas[i]);
        }
       // printf ("OPA");
        //printf ("%s\n", collumns[0]->tipo);
        
        int *listaIDs, tamanhoLista;
        switch (getType(collumns[0]->tipo))
        {
        case 1:
            tamanhoLista = getTamanhoListaInteger (collumns[0]->integers);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
             listaIDs = listarIdOfCollumnInteger (collumns[0]->integers, listaIDs);
            break;
        case 2:
            tamanhoLista = getTamanhoListaBoolean (collumns[0]->booleans);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnBoolean (collumns[0]->booleans, listaIDs);
            break;
        case 3:
            tamanhoLista = getTamanhoListaVarchar (collumns[0]->varchars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnVarchar(collumns[0]->varchars, listaIDs);
            break;
        case 4:
            tamanhoLista = getTamanhoListaChar (collumns[0]->chars);
            //printf ("Tamanho = %d\n", tamanhoLista);
            listaIDs = malloc(tamanhoLista * sizeof(int));
            listaIDs = listarIdOfCollumnChar(collumns[0]->chars, listaIDs);
            break;
        default:
            printf ("Erro, tipo da coluna não suportado.\n");
            break;
        }
        for (int i = 0; i < numeroColunasPesquisadas; i++) {
            printf ("| %s |", nomeColunas[i]);
        }
        printf ("\n");
        Collumn aux;
        for (i = 1; i < tamanhoLista; i++) {
            for (j = 0; j < numeroColunasPesquisadas; j++) {
                aux = buscaCollumn (selectedTable->columns, nomeColunas[j]);
                switch (getType(aux->tipo)) {
                    case 1:
                        printf ("| %d |", buscaIntegerById(listaIDs[i], aux->integers)->valor);
                        break;
                    case 2:
                        printf ("| %d |", buscaBooleanById(listaIDs[i], aux->booleans)->valor);
                        break;
                    case 3:
                        printf ("| %s |", buscaVarcharById(listaIDs[i], aux->varchars)->valor);
                        break;
                    case 4:
                        printf ("| %c |", buscaCharById(listaIDs[i], aux->chars)->valor);
                        break;
                }
            }
            printf ("\n");
        }
    }
}