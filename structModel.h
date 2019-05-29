struct database {
    char *name;
    struct database *direita;
    struct database *esquerda;
    struct table *tables;
};
typedef struct database *DataBase;
struct table {
    char *name;
    struct table *direita;
    struct table *esquerda;
    struct collumn *columns;
};
typedef struct table *Table;
struct collumn {
    
    char *name;
    char *tipo;
    bool primary_key;
    struct collumn *direita;
    struct collumn *esquerda;
    struct integer *integers;
    struct boolean *booleans;
    struct varchar *varchars;
    struct caracter *chars;
};
typedef struct collumn *Collumn;
struct integer
{
    unsigned int id;
    struct integer *proximo;
    int valor;
};
typedef struct integer *Integer;
struct boolean
{
    unsigned int id;
    struct boolean *proximo;
    bool valor;
};
typedef struct boolean *Booleano;
struct varchar
{
    unsigned int id;
    unsigned int size;
    struct varchar *proximo;
    char *valor;
};
typedef struct varchar *Varchar;
struct caracter {
    unsigned int id;
    struct caracter *proximo;
    char valor;
};
typedef struct caracter *Char;
