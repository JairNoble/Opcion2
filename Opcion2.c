#include <stdio.h>
#include <string.h>

#define MAX_PROD 50

float validarFloat(float a, float b);

int main (int argc, char *argv[]) {

    char nombres[MAX_PROD][30];
    int cantidad[MAX_PROD];
    float tiempoUnitario[MAX_PROD];
    float recursoUnitario[MAX_PROD];

    int numProductos = 0;
    int opc, opc2;

    char buscado[30];
    int encontrado, i, j;
    float tiempoDisponible, recursosDisponibles;
    float tiempoTotal, recursosTotales;

    do {
        printf("\n--- MENU DE PRODUCCION ---\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Calcular demanda y verificar disponibilidad\n");
        printf("6. Salir\n");
        printf(">> ");
        opc = (int)validarFloat(1, 6);

        switch (opc)
        {
        case 1:
            if (numProductos >= MAX_PROD) {
                printf("Error: se ha alcanzado el limite maximo de productos.\n");
                break;
            }
            printf("Ingrese los datos del producto:\n");
            printf("Nombre (sin espacios): ");
            scanf("%29s", nombres[numProductos]);
            while((getchar()) != '\n'); // Limpiar buffer

            printf("Cantidad demandada: ");
            cantidad[numProductos] = (int)validarFloat(1, 10000);

            printf("Tiempo de fabricacion por unidad (horas): ");
            tiempoUnitario[numProductos] = validarFloat(0.1, 1000);

            printf("Recursos necesarios por unidad: ");
            recursoUnitario[numProductos] = validarFloat(0.1, 1000);

            numProductos++;
            printf("Producto registrado con exito.\n");
            break;

        case 2:
            if (numProductos == 0) {
                printf("No hay productos registrados para editar.\n");
                break;
            }
            printf("Ingrese el nombre del producto a editar: ");
            scanf("%29s", buscado);
            while((getchar()) != '\n');

            encontrado = -1;
            for (i = 0; i < numProductos; i++) {
                if (strcmp(nombres[i], buscado) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {
                printf("Producto encontrado. Ingrese los nuevos datos:\n");
                printf("Nuevo nombre (sin espacios): ");
                scanf("%29s", nombres[encontrado]);
                while((getchar()) != '\n');

                printf("Nueva cantidad demandada: ");
                cantidad[encontrado] = (int)validarFloat(1, 10000);

                printf("Nuevo tiempo por unidad (horas): ");
                tiempoUnitario[encontrado] = validarFloat(0.1, 1000);

                printf("Nuevos recursos por unidad: ");
                recursoUnitario[encontrado] = validarFloat(0.1, 1000);

                printf("Producto actualizado correctamente.\n");
            } else {
                printf("Error: no se encontro un producto con ese nombre.\n");
            }
            break;

        case 3:
            if (numProductos == 0) {
                printf("No hay productos registrados para eliminar.\n");
                break;
            }
            printf("Ingrese el nombre del producto a eliminar: ");
            scanf("%29s", buscado);
            while((getchar()) != '\n');

            encontrado = -1;
            for (i = 0; i < numProductos; i++) {
                if (strcmp(nombres[i], buscado) == 0) {
                    encontrado = i;
                    break;
                }
            }

            if (encontrado != -1) {

                for (j = encontrado; j < numProductos - 1; j++) {
                    strcpy(nombres[j], nombres[j + 1]);
                    cantidad[j] = cantidad[j + 1];
                    tiempoUnitario[j] = tiempoUnitario[j + 1];
                    recursoUnitario[j] = recursoUnitario[j + 1];
                }
                numProductos--;
                printf("Producto eliminado correctamente.\n");
            } else {
                printf("Error: no se encontro un producto con ese nombre.\n");
            }
            break;

        case 4:
            if (numProductos == 0) {
                printf("No hay productos registrados.\n");
                break;
            }
            printf("\nNombre \t\t Cantidad \t Tiempo/U \t Recursos/U\n");
            for (i = 0; i < numProductos; i++) {
                printf("%-15s\t %d \t\t %.2f \t\t %.2f\n", 
                       nombres[i], cantidad[i], tiempoUnitario[i], recursoUnitario[i]);
            }
            break;

        case 5:
            if (numProductos == 0) {
                printf("No hay productos registrados para calcular.\n");
                break;
            }
            tiempoTotal = 0;
            recursosTotales = 0;

            for (i = 0; i < numProductos; i++) {
                tiempoTotal += cantidad[i] * tiempoUnitario[i];
                recursosTotales += cantidad[i] * recursoUnitario[i];
            }

            printf("\n--- RESULTADOS DE PRODUCCION ---\n");
            printf("Tiempo total de fabricacion requerido: %.2f horas\n", tiempoTotal);
            printf("Cantidad total de recursos necesarios: %.2f unidades\n\n", recursosTotales);

            printf("Ingrese el tiempo de produccion disponible en la fabrica (horas): ");
            tiempoDisponible = validarFloat(0, 100000);
            printf("Ingrese la cantidad de recursos disponibles en la fabrica: ");
            recursosDisponibles = validarFloat(0, 100000);

            printf("\n--- EVALUACION DE CAPACIDAD ---\n");
            if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
                printf("SI es posible cumplir con la demanda.\n");
            } else {
                printf("NO es posible cumplir con la demanda.\n");
                if (tiempoTotal > tiempoDisponible) {
                    printf("- Faltan %.2f horas de produccion.\n", tiempoTotal - tiempoDisponible);
                }
                if (recursosTotales > recursosDisponibles) {
                    printf("- Faltan %.2f unidades de recursos.\n", recursosTotales - recursosDisponibles);
                }
            }
            break;

        case 6:
            return 0;

        default:
            printf("No existe la opcion\n");
            break;
        }

        printf("\nDesea seleccionar otra opcion 1.Si / 2.No: ");
        opc2 = (int)validarFloat(1, 2);

    } while (opc2 == 1);

    return 0;
}

float validarFloat(float a, float b) {
    float num;
    int val = 0;
    do {
        val = scanf("%f", &num);
        while ((getchar()) != '\n');
        if (num < a || num > b || val != 1) {
            printf("Error: el valor ingresado es incorrecto. Intente nuevamente: ");
        }
    } while (num < a || num > b || val != 1);
    return num;
}
