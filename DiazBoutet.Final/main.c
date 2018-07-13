#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "Func.h"

int main()
{
    printf("Hello world!\n");
    ArrayList* deposito1;
    deposito1=al_newArrayList();
    ArrayList* deposito2;
    deposito2=al_newArrayList();
    eDeposito*aux;
    char*path1={"dep0.csv"};
    char*path2={"dep1.csv"};
    int opcion=0;
    char seguir='s';
    int error;
    while(seguir!='n')
    {   system("cls");
        printf("Menu:\n\t1. Cargar depositos\n\t2. Listar productos deposito\n\t3. Mover productos de deposito\n\t4. Descontar productos de deposito\n\t5. Agregar productos a deposito\n\t6. Salir\n\t");
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            error=parseDeposito(path1,deposito1);
            error=parseDeposito(path2,deposito2);
            break;
        case 2:

            printf("Imprimir deposito 1 o 2, 0 para salir:\n");
            scanf("%d",&opcion);
            do
            {   if(opcion==1)
                {
                    eDeposito_printall(deposito1);
                    opcion=0;
                }else if(opcion==2)
                {
                    eDeposito_printall(deposito2);
                    opcion=0;
                }else if(opcion!=0)
                {
                    printf("Ingrese un numero de deposito valido: deposito 1 o 2. 0 para salir:\n");
                    scanf("%d",&opcion);
                }

            }while (opcion!=0);
                system("pause");
            break;
        case 3:
                error=eDeposito_mover(path1,path2,deposito1,deposito2);


            break;
        case 4:
                error=eDeposito_descontar(path1,path2,deposito1,deposito2);
            break;
        case 5:
            //printf("Ingrese que elemento desea borrar\n");
            //scanf("%d",&fromTo[0]);
                error=eDeposito_aumentar(path1,path2,deposito1,deposito2);
            //error=al_remove(empleados,fromTo[0]);
            break;
        case 6:
            seguir='n';
            break;
        }
    }

    return 0;
}
