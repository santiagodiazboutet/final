#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
typedef struct{
int id;
char descripcion[20];
int stock;

}eDeposito;


int parseDeposito(char* , ArrayList* this);
void eDeposito_print(eDeposito* this);
eDeposito* eDeposito_new(void);
void eDeposito_printall(ArrayList*);
int eDeposito_comparaID(eDeposito* this,int id);
int eDeposito_mover(char * Path1,char * Path2,ArrayList*this,ArrayList*this2);
void nuevo_archivo(ArrayList *this,char*path);
int eDeposito_descontar(char * Path1,char * Path2,ArrayList*this,ArrayList*this2);
int eDeposito_aumentar(char * Path1,char * Path2,ArrayList*this,ArrayList*this2);
#endif // FUNC_H_INCLUDED
