#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "Func.h"




int parseDeposito(char* path , ArrayList* this)
{
    char descripcion[20], id[20],stock[6];
    eDeposito*deposito;
    FILE *pFile;
    pFile=fopen(path,"r");
    int end;
    int error;
    int flag=0;
    char *aux;
    fseek(pFile,0,SEEK_END);
    end=ftell(pFile);
    rewind(pFile);
    while(ftell(pFile)<end)
    {
        deposito=eDeposito_new();
        fscanf(pFile, "%[^,],%[^,],%[^\n]\n", id, descripcion,stock);
        if(flag==0)
        {   flag=1;
            continue;
        }
        sscanf(id,"%d",&deposito->id);
        strcpy(deposito->descripcion,descripcion);
        sscanf(stock,"%d",&deposito->stock);
        error=al_add(this,deposito);
    }
    fclose(pFile);

    return error;
}

eDeposito* eDeposito_new(void)
{

    eDeposito* returnAux = NULL;
    returnAux=(eDeposito*)malloc(sizeof(eDeposito));
    return returnAux;

}
void eDeposito_print(eDeposito* this)
{
        printf("%5d %15s %5d\n",this->id,this->descripcion,this->stock);
}
void eDeposito_printall(ArrayList*this)
{   eDeposito*aux;
    for(int i=0;i<al_len(this);i++)


                            {
                                aux=(eDeposito*)(eDeposito*)al_get(this,i);
                                eDeposito_print(aux);
                            }

}
int eDeposito_mover(char * Path1,char * Path2,ArrayList*this,ArrayList*this2)
{   int opcion;
    int opcion2;
    int id;
    int aux;
    eDeposito*deposito;
    printf("Desea mover un producto del deposito 1 o 2. 0 para salir:\n");
            scanf("%d",&opcion);
            printf("Desea mover un producto al deposito 1 o 2. 0 para salir:\n");
            scanf("%d",&opcion2);
            do
            {   if(opcion2!=1&&opcion2!=2)
                {
                    printf("Ingrese un numero de deposito valido: deposito 1 o 2. 0 para salir:\n");
                    scanf("%d",&opcion2);
                    continue;
                }

                if(opcion==1)
                {
                    eDeposito_printall(this);
                    printf("Ingrese codigo de producto a mover:\n");
                    scanf("%d",&id);
                    aux=al_searchID(this,eDeposito_comparaID,id);
                    deposito=(eDeposito*)al_get(this,aux);
                    printf("Esta seguro de que desea mover:1.Si 2.No\n");
                    eDeposito_print(deposito);
                    scanf("%d",&id);
                    if(id==1)
                    {
                      opcion=0;
                      al_remove(this,aux);
                      if (opcion2==1)
                      {
                          al_add(this,deposito);
                          nuevo_archivo(this,Path1);
                          nuevo_archivo(this2,Path2);
                      }

                      if (opcion2==2)
                      {
                          al_add(this2,deposito);
                          nuevo_archivo(this2,Path2);
                           nuevo_archivo(this,Path1);
                      }
                    }
                    opcion=0;
                }else if(opcion==2)
                {
                    eDeposito_printall(this2);
                    printf("Ingrese codigo de producto a mover:\n");
                    scanf("%d",&id);
                    aux=al_searchID(this2,eDeposito_comparaID,id);
                    deposito=(eDeposito*)al_get(this2,aux);
                    printf("Esta seguro de que desea mover:1.Si 2.No\n");
                    eDeposito_print(deposito);
                    scanf("%d",&id);
                    if(id==1)
                    {
                      opcion=0;
                      al_remove(this2,aux);

                      if (opcion2==1)
                      {
                          al_add(this,deposito);
                          nuevo_archivo(this,Path1);
                          nuevo_archivo(this2,Path2);
                      }

                      if (opcion2==2)
                      {
                          al_add(this2,deposito);
                          nuevo_archivo(this2,Path2);
                          nuevo_archivo(this,Path1);
                      }
                    }
                    opcion=0;
                }else if(opcion!=0)
                {
                    printf("Ingrese un numero de deposito valido: deposito 1 o 2. 0 para salir:\n");
                    scanf("%d",&opcion);
                }

            }while (opcion!=0&&opcion2!=0);
}
int eDeposito_comparaID(eDeposito* this,int id)
{
    if(this->id==id)
    {
        return 1;
    }
        return 0;

}

void nuevo_archivo(ArrayList *this,char*path)
{
    FILE * fp;
    eDeposito* deposito;
    fp=fopen(path,"w");
    fprintf(fp,"%s\n","producto,descripcion,cantidad");
    for (int i =0;i<al_len(this);i++)
    {   deposito=(eDeposito*)(eDeposito*)al_get(this,i);

        fprintf(fp,"%d,%s,%d\n",deposito->id ,deposito->descripcion,deposito->stock);

    }
    system("pause");
    fclose(fp);


}
int eDeposito_descontar(char * Path1,char * Path2,ArrayList*this,ArrayList*this2)
{
    int opcion=1;

    int id;
    int aux;
    eDeposito*deposito;

    printf("Ingrese codigo de producto a descontar.Ingrese 0 para salir::\n");
    scanf("%d",&id);
    if(id==0)
    {
        return 0;
    }
    aux=al_searchID(this,eDeposito_comparaID,id);
    if(aux!=-1)
    {   do
    {
        deposito=(eDeposito*)al_get(this,aux);
        printf("Cuanto stock desea quitar\n");
        eDeposito_print(deposito);
        scanf("%d",&id);
        if(id<=deposito->stock)
        {
            deposito->stock=(deposito->stock)-id;
            nuevo_archivo(this,Path1);
            opcion=0;
        }
        else
        {
            printf("Por favor, ingrese un numero valido\n");
            system("pause");
            system("cls");
        }
    }while(opcion!=0);
    }
    else
    {
        aux=al_searchID(this2,eDeposito_comparaID,id);
        if(aux!=-1)
        {
            do{
            deposito=(eDeposito*)al_get(this2,aux);
            printf("Cuanto stock desea quitar\n");
            eDeposito_print(deposito);
            scanf("%d",&id);
            if(id<=deposito->stock)
            {
                deposito->stock=(deposito->stock)-id;
                nuevo_archivo(this2,Path2);
                opcion=0;
            }
            else
            {
                printf("Por favor, ingrese un numero valido\n");
                system("pause");
                system("cls");
            }
            }while(opcion!=0);
        }
        else
        {
            printf("Por favor, ingrese un codigo valido\n");
                system("pause");
                system("cls");
        }
    }
}
int eDeposito_aumentar(char * Path1,char * Path2,ArrayList*this,ArrayList*this2)
{
    int opcion=1;

    int id;
    int aux;
    eDeposito*deposito;

    printf("Ingrese codigo de producto a mover, Ingrese 0 para salir:\n");
    scanf("%d",&id);
    if(id==0)
    {
        return 0;
    }
    aux=al_searchID(this,eDeposito_comparaID,id);
    if(aux!=-1)
    {   do
    {
        deposito=(eDeposito*)al_get(this,aux);
        printf("Cuanto stock desea agregar\n");
        eDeposito_print(deposito);
        scanf("%d",&id);
        if(id<=deposito->stock)
        {
            deposito->stock=(deposito->stock)+id;
            nuevo_archivo(this,Path1);
            opcion=0;
        }
        else
        {
            printf("Por favor, ingrese un numero valido\n");
            system("pause");
            system("cls");
        }
    }while(opcion!=0);
    }
    else
    {
        aux=al_searchID(this2,eDeposito_comparaID,id);
        if(aux!=-1)
        {
            do{
            deposito=(eDeposito*)al_get(this2,aux);
            printf("Cuanto stock desea quitar\n");
            eDeposito_print(deposito);
            scanf("%d",&id);
            if(id<=deposito->stock)
            {
                deposito->stock=(deposito->stock)+id;
                nuevo_archivo(this2,Path2);
                opcion=0;
            }
            else
            {
                printf("Por favor, ingrese un numero valido\n");
                system("pause");
                system("cls");
            }
            }while(opcion!=0);
        }
        else
        {
            printf("Por favor, ingrese un codigo valido\n");
                system("pause");
                system("cls");
        }
    }
}
