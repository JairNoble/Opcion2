#include <stdio.h>
#include <string.h>

#define PRODUCTOS 5

float tiempoDemanda(int demanda[], float tiempo[], int TotalProductos);
float CantidadRecursos(float recurso[], int demanda[], int TotalProductos);
void validacion_demanda(float tiempo[], float recursos[], float tiempo_D, float recursos_D, int TotalProductos, int demanda[]);
void IngresoProductos(char nombres[][20], float tiempo[], float recursos[], int demanda[], int *TotalProductos);
void modificarVariables(char nombres[][20], float tiempo[], float recursos[], int demanda[], int TotalProductos);
void EliminarProducto(char nombres[][20], float tiempo[], float recursos[], int demanda[], int *TotalProductos);
void mostrarProductos(char nombres[][20], float tiempo[], float recursos[], int demanda[], int TotalProductos);

int main(int argc, char const *argv[]) {
    char nombres[PRODUCTOS][20];
    float tiempo[PRODUCTOS];
    float recursos[PRODUCTOS];
    int demanda[PRODUCTOS];
    int TotalProductos = 0;
    int opc;

    do {
        printf("\n========================================\n");
        printf("      SISTEMA DE GESTION - FABRICA      \n");
        printf("========================================\n");
        printf("1. Ingresar nuevo producto\n");
        printf("2. Mostrar productos registrados\n");
        printf("3. Calcular tiempo total de fabricacion requerido\n");
        printf("4. Calcular recursos necesarios totales\n");
        printf("5. Verificar si es posible cumplir con la demanda\n");
        printf("6. Editar datos de un producto\n");
        printf("7. Eliminar un producto\n");
        printf("8. Salir\n");
        printf("----------------------------------------\n");
        printf("Escoja una opcion (1-8): ");
        
        if (scanf("%d", &opc) != 1) {
            printf("Error: Ingrese un numero valido.\n");
            while (getchar() != '\n');
            opc = 0;
            continue;
        }
        while (getchar() != '\n');

        switch (opc) {
            case 1:
                IngresoProductos(nombres, tiempo, recursos, demanda, &TotalProductos);
                break;
            
            case 2:
                mostrarProductos(nombres, tiempo, recursos, demanda, TotalProductos);
                break;

            case 3:
                if (TotalProductos == 0) {
                    printf("\n[!] No hay productos registrados aun.\n");
                } else {
                    float totalT = tiempoDemanda(demanda, tiempo, TotalProductos);
                    printf("\n--> Tiempo total de fabricacion requerido: %.2f horas\n", totalT);
                }
                break;

            case 4:
                if (TotalProductos == 0) {
                    printf("\n[!] No hay productos registrados aun.\n");
                } else {
                    float totalR = CantidadRecursos(recursos, demanda, TotalProductos);
                    printf("\n--> Cantidad total de recursos necesarios: %.2f unidades\n", totalR);
                }
                break;

            case 5:
                if (TotalProductos == 0) {
                    printf("\n[!] No hay productos registrados aun.\n");
                } else {
                    float tiempo_D, recursos_D;
                    printf("\nIngrese el tiempo limite disponible en la fabrica (horas): ");
                    scanf("%f", &tiempo_D);
                    printf("Ingrese la cantidad de recursos disponibles: ");
                    scanf("%f", &recursos_D);
                    while (getchar() != '\n');

                    validacion_demanda(tiempo, recursos, tiempo_D, recursos_D, TotalProductos, demanda);
                }
                break;
                
            case 6:
                modificarVariables(nombres, tiempo, recursos, demanda, TotalProductos);
                break;

            case 7:
                EliminarProducto(nombres, tiempo, recursos, demanda, &TotalProductos);
                break;

            case 8:
                printf("\nSaliendo del sistema. ¡Hasta luego!\n");
                return 0;
            
            default:
                printf("\n[X] Opcion invalida, intente otra vez.\n");
                break;
        }

        if (opc != 8) {
            printf("\n¿Desea realizar otra operacion? (Si: 1 / No: 0): ");
            scanf("%d", &opc);
            while (getchar() != '\n');
            if (opc != 1) {
                printf("\nSaliendo del sistema. ¡Hasta luego!\n");
                break;
            }
        }

    } while (1);

    return 0;
}

float tiempoDemanda(int demanda[], float tiempo[], int TotalProductos) {
    float TiempoTacumulado = 0.0;
    for (int i = 0; i < TotalProductos; i++) {
        float TotalTiempo = demanda[i] * tiempo[i];
        TiempoTacumulado += TotalTiempo;
    }
    return TiempoTacumulado;
}

float CantidadRecursos(float recurso[], int demanda[], int TotalProductos) {
    float RecursosA = 0.0;
    for (int i = 0; i < TotalProductos; i++) {
        float TotalRecursos = recurso[i] * demanda[i];
        RecursosA += TotalRecursos;
    }
    return RecursosA;
}

void validacion_demanda(float tiempo[], float recursos[], float tiempo_D, float recursos_D, int TotalProductos, int demanda[]) {
    float tiempo_R = tiempoDemanda(demanda, tiempo, TotalProductos);
    float recursos_R = CantidadRecursos(recursos, demanda, TotalProductos);

    printf("\n--- RESULTADOS DE LA EVALUACION ---\n");
    printf("Tiempo requerido: %.2f hrs | Tiempo disponible: %.2f hrs\n", tiempo_R, tiempo_D);
    printf("Recursos requeridos: %.2f   | Recursos disponibles: %.2f\n", recursos_R, recursos_D);

    if (tiempo_R <= tiempo_D && recursos_R <= recursos_D) {
        printf("\n[OK] La fabrica SI puede realizar la demanda con exito.\n");
    } else {
        printf("\n[X] La fabrica NO puede realizar la demanda.\n");
    }
    
    if (tiempo_R > tiempo_D) {
        printf("- Alerta: Falta tiempo de produccion (deficit de %.2f horas).\n", tiempo_R - tiempo_D);
    }

    if (recursos_R > recursos_D) {
        printf("- Alerta: Faltan recursos para esta acción (deficit de %.2f unidades).\n", recursos_R - recursos_D);
    }
}

void IngresoProductos(char nombres[][20], float tiempo[], float recursos[], int demanda[], int *TotalProductos) {
    if (*TotalProductos >= PRODUCTOS) {
        printf("\n[X] Error: Limite de productos alcanzado (Maximo %d).\n", PRODUCTOS);
        return;
    }

    int i = *TotalProductos;
    printf("\n--- INGRESAR PRODUCTO [%d/%d] ---\n", i + 1, PRODUCTOS);
    printf("Ingrese el nombre del producto (sin espacios): ");
    scanf("%19s", nombres[i]);
    printf("Ingrese la demanda (cantidad): ");
    scanf("%d", &demanda[i]);
    printf("Ingrese el tiempo en fabricarse una unidad (horas): ");
    scanf("%f", &tiempo[i]);
    printf("Cantidad de recursos necesarios para producir una unidad: ");
    scanf("%f", &recursos[i]);

    while (getchar() != '\n');

    (*TotalProductos)++;
    printf("\n[OK] Producto ingresado con exito.\n");
}

void mostrarProductos(char nombres[][20], float tiempo[], float recursos[], int demanda[], int TotalProductos) {
    if (TotalProductos == 0) {
        printf("\n[!] No hay productos registrados.\n");
        return;
    }

    printf("#\tProductos\tTiempo/U\tRecursos/U\tDemanda\n");
    for (int i = 0; i < TotalProductos; i++) {
        printf("%d\t%-12s\t%.2f\t\t%.2f\t\t%d\n", i + 1, nombres[i], tiempo[i], recursos[i], demanda[i]);
    }

}

void modificarVariables(char nombres[][20], float tiempo[], float recursos[], int demanda[], int TotalProductos) {
    if (TotalProductos == 0) {
        printf("\n[!] No hay productos registrados para modificar.\n");
        return;
    }

    mostrarProductos(nombres, tiempo, recursos, demanda, TotalProductos);

    char buscar[20];
    int encontrado = -1;

    printf("\nIngrese el nombre exacto del producto a modificar: ");
    scanf("%19s", buscar);
    while (getchar() != '\n');

    for (int i = 0; i < TotalProductos; i++) {
        if (strcmp(buscar, nombres[i]) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("\nProducto encontrado. Ingrese los nuevos datos:\n");
        printf("Nuevo nombre: ");
        scanf("%19s", nombres[encontrado]);
        printf("Nuevo tiempo por unidad: ");
        scanf("%f", &tiempo[encontrado]);
        printf("Nuevos recursos por unidad: ");
        scanf("%f", &recursos[encontrado]);
        printf("Nueva demanda: ");
        scanf("%d", &demanda[encontrado]);
        while (getchar() != '\n');

        printf("\n[OK] Datos del producto actualizados correctamente.\n");
    } else {
        printf("\n[X] Producto no encontrado.\n");
    }
}

void EliminarProducto(char nombres[][20], float tiempo[], float recursos[], int demanda[], int *TotalProductos) {
    if (*TotalProductos == 0) {
        printf("\n[!] No hay productos registrados para eliminar.\n");
        return;
    }

    mostrarProductos(nombres, tiempo, recursos, demanda, *TotalProductos);

    char buscar[20];
    int encontrado = -1;

    printf("\nIngrese el nombre del producto que desea eliminar: ");
    scanf("%19s", buscar);
    while (getchar() != '\n');

    for (int i = 0; i < *TotalProductos; i++) {
        if (strcmp(buscar, nombres[i]) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int j = encontrado; j < *TotalProductos - 1; j++) {
            strcpy(nombres[j], nombres[j + 1]);
            tiempo[j] = tiempo[j + 1];
            recursos[j] = recursos[j + 1];
            demanda[j] = demanda[j + 1];
        }
        (*TotalProductos)--;
        printf("\n[OK] Producto eliminado correctamente.\n");
    } else {
        printf("\n[X] Producto no encontrado.\n");
    }
}