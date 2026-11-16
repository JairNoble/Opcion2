#include <stdio.h>
#include <string.h>

#define PRODUCTOS 5

    char nombres [PRODUCTOS][20];
    float tiempo [PRODUCTOS];
    float recursos [PRODUCTOS];
    int demanda [PRODUCTOS];
    int TotalProductos=0;
 
    







 float tiempoDemanda(int demanda[],float tiempo[],int TotalProductos){
     
     float TiempoTacumulado=0.0;
     
     for (int i=0;i< TotalProductos ; i++) {
         
         
         float TotalTiempo = demanda[i]*tiempo[i];
         TiempoTacumulado += TotalTiempo;
         
     }
     return TiempoTacumulado;
 }
 
 float CantidadRecursos (float recurso[],int demanda[],int TotalProductos ){
     
     float RecursosA=0.0;
     
     for (int i=0 ;i< TotalProductos;i++){
         
         float TotalRecursos = recurso [i] * demanda[i];
         RecursosA += TotalRecursos;
         
     }
     
     return RecursosA;
     
 }

 void validacion_demanda ( float tiempo[],float recursos[],float tiempo_D,float recursos_D , int TotalProductos,int demanda[]  ){

  float tiempo_R =  tiempoDemanda( demanda, tiempo, TotalProductos);
  float recursos_R =  CantidadRecursos ( recursos, demanda, TotalProductos );

 if (tiempo_R <= tiempo_D && recursos_R <= recursos_D)
 {
    printf("La fabrica puede realizar la demanda \n");
 }else 
 {
    printf("La fabrica no puede realizar la demanda\n");
 }
 
if (tiempo_R > tiempo_D && tiempo_R > 0)
{
    printf("falta tiempo de produccion\n");
}

   if (recursos_R > recursos_D && recursos_R > 0)
   {
    printf("falta recursos para esta accion\n");
   }
   

 }

void IngresoProductos(char nombres[][20],float tiempo[],float recursos[],int demanda[],int *TotalProductos){

if (*TotalProductos >= PRODUCTOS)
{
    printf("Limite de productos alcanzado");
    return;
}

int i = *TotalProductos;
printf("Ingrese el nombre del producto\n");
scanf("%s",nombres[i]);
printf ("Ingrese la demanda \n");
scanf("%d",&demanda[i]);
printf("Ingresar el tiempo en fabricarse un producto\n");
scanf("%f",&tiempo[i]);
printf("Cantidad de recursos necesarios para producir un prodcuto\n");
scanf("%f",&recursos[i]);

while (getchar() != '\n');

(*TotalProductos)++;

}

void modificarVariables (char nombres[][20], float tiempo[],float recursos[],int demanda[],int TotalProductos){

char buscar [20];
int encontrado = -1;
int pos;

 printf("\n#\t\tPrductos\t\tTiempo\t\tRecursos\t\tDemanda");

 for (int i = 0; i < TotalProductos; i++)
 {
     printf("%d\t\t%s\t\t%.2f\t\t%.2f\t\t%d",i + 1,nombres[i],tiempo[i],recursos[i],demanda[i]);
 }
 


printf("Que producto desea modificar?");
scanf("%s",buscar);
for (int i = 0; i < TotalProductos; i++)
{
    if (strcmp(buscar,nombres[i])== 0)
    {
        
        pos=i;
        printf("Ingrese los nuevos datos del produtcto");
        printf("Nombre");
        scanf("%s",nombres[pos]);
        printf("Tiempo");
        scanf("%f",&tiempo[pos]);
        printf("Recursos");
        scanf("%f",&recursos[pos]);
        printf("Demanda");
        scanf("%d",&demanda[pos]);
    
        encontrado=1;
        break;
    }
}

if (encontrado==-1)
{
    printf("Producto no encontrado");
}
}

void EliminarProducto (char nombres[][20], float tiempo[],float recursos[],int demanda[],int *TotalProductos){
 
char buscar [20];
int encontrado =-1;
printf("\n#\t\tPrductos\t\tTiempo\t\tRecursos\t\tDemanda");

printf("Que producto desea eliminar?");
scanf("%s",buscar);

 for (int i = 0; i < *TotalProductos; i++)
 {
     printf("%d\t\t%s\t\t%.2f\t\t%.2f\t\t%d",i + 1,nombres[i],tiempo[i],recursos[i],demanda[i]);
 }

 for (int i = 0; i < *TotalProductos; i++)
{
    
    if (strcmp(buscar,nombres[i])== 0)
    {
         encontrado=1;
         for (int j = i ; i < *TotalProductos-1; i++)
         {
            strcpy(nombres[i],nombres[i+1]);
            tiempo[i]= tiempo[i+1];
            recursos[i]= recursos[i+1];
            demanda[i]= demanda[i+1];
           
         }
         

        *(TotalProductos)--;
        printf("Producto eliminado");
          break;
       
    }
  
}
if (encontrado==-1)
{   
    printf("Producto no encontrado");
}
}


int main(int argc, char const *argv[])
{
    
    int opc;

    printf("escoga una funcion para su producto\n");
    printf("1.Tiempo total de fabricaicon requerido\n");
    printf("2.Cantidad de recursos necesarios para producir los productos\n");
    printf("3.¿Es posbile cumplir con la demanda ?\n");
    printf("4.Ingreso de los nombres\n");
    printf("5.Edicion de los datos del producto\n");
    printf("6.Eliminacion de productos ingresados\n");
    scanf("%d",&opc);
    do
    {
          switch (opc)
    {
    case 1:
    
    IngresoProductos( nombres , tiempo, recursos, demanda,&TotalProductos);
        break;
    
    case 2:
       tiempoDemanda( demanda,tiempo, TotalProductos);
        break;

    case 3:
        CantidadRecursos (recursos, demanda,TotalProductos );
        break;

    case 4:
    float tiempo_D;
    float recursos_D;
    printf("Inresar el tiempo limite de fabrica");
    scanf("%f",&tiempo_D);
    printf("Ingresar los recursos disponibles");
    scanf("%f",&recursos_D);
       validacion_demanda (  tiempo, recursos, tiempo_D, recursos_D ,  TotalProductos, demanda  );
        break;
        
    case 5:
     modificarVariables ( nombres,  tiempo,recursos, demanda,TotalProductos);
        break;

    case 6:
    EliminarProducto ( nombres, tiempo,recursos, demanda, &TotalProductos);
        break;
    
    
    default:
    printf("Opcion invalida ,intente otra vez ");
        break;
    }
    
    printf("Desea continuar Si:1,No:0");
    scanf("%d",&opc);
    } while (opc == 1);

  



    
    return 0;
}

