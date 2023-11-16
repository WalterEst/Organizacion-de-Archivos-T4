#include <stdio.h>

// Definición de la estructura para representar un automóvil
struct Automovil {
    int id;
    char marca[100];
    char modelo[100];
    float motor_cilindrada;
    char tipo_gasolina[100];
    int cantidad_asientos;
    int cantidad_puertas;
    char color[100];
};

// Función para obtener el valor del contador desde un archivo
int ObtenerContador() {
    FILE *contadorArchivo = fopen("contador.txt", "r");
    if (contadorArchivo == NULL) {
        return 0;
    }
    int contador;
    fscanf(contadorArchivo, "%d", &contador);
    fclose(contadorArchivo);
    return contador;
}

// Función para actualizar el valor del contador en el archivo
void ActualizarContador(int nuevoContador) {
    FILE *contadorArchivo = fopen("contador.txt", "w");
    if (contadorArchivo == NULL) {
        printf("Error al abrir el archivo del contador.\n");
        return;
    }
    fprintf(contadorArchivo, "%d", nuevoContador);
    fclose(contadorArchivo);
}

// Función para ingresar un automóvil
void Ingresar() {
    FILE *archivo = fopen("archivo.dat", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    int numeroFila = ObtenerContador();
    numeroFila++;

    struct Automovil nuevoAutomovil;

    nuevoAutomovil.id = numeroFila;

    printf("Marca: ");
    scanf("%s", nuevoAutomovil.marca);
    printf("Modelo: ");
    scanf("%s", nuevoAutomovil.modelo);
    printf("Cilindrada de motor: ");
    scanf("%f", &nuevoAutomovil.motor_cilindrada);
    printf("Tipo de gasolina: ");
    scanf("%s", nuevoAutomovil.tipo_gasolina);
    printf("Cantidad de asientos: ");
    scanf("%d", &nuevoAutomovil.cantidad_asientos);
    printf("Cantidad de puertas: ");
    scanf("%d", &nuevoAutomovil.cantidad_puertas);
    printf("Color: ");
    scanf("%s", nuevoAutomovil.color);

    fprintf(archivo, "%d: %s-%s-%.1f-%s-%d-%d-%s\n", nuevoAutomovil.id, nuevoAutomovil.marca, nuevoAutomovil.modelo, nuevoAutomovil.motor_cilindrada, nuevoAutomovil.tipo_gasolina, nuevoAutomovil.cantidad_asientos, nuevoAutomovil.cantidad_puertas, nuevoAutomovil.color);
    printf("Auto ingresado con éxito.\n");

    ActualizarContador(numeroFila);

    fclose(archivo);
}

// Función para mostrar el contenido del archivo
void Mostrar() {
    FILE *archivo = fopen("archivo.dat", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char linea[1000];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s \n", linea);
    }

    fclose(archivo);
}

// Funcion para eliminar una entrada de un archivo
void Eliminar() {
    // Abrir el archivo original en modo lectura
    FILE *archivoLectura = fopen("archivo.dat", "r");
    if (archivoLectura == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n"); // Mostrar un mensaje de error si no se puede abrir el archivo
        return;
    }

    // Abrir un archivo temporal en modo escritura
    FILE *archivoTemporal = fopen("temporal.dat", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo abrir el archivo temporal.\n"); // Mostrar un mensaje de error si no se puede abrir el archivo temporal
        fclose(archivoLectura); // Cerrar el archivo original si no se puede abrir el archivo temporal
        return;
    }

    int idAEliminar;
    printf("ID a eliminar: ");
    scanf("%d", &idAEliminar);

    int idAutomovil;
    char linea[1000]; // Suponemos que cada linea en el archivo tiene un maximo de 1000 caracteres

    while (fgets(linea, sizeof(linea), archivoLectura) != NULL) {
        sscanf(linea, "%d", &idAutomovil);

        if (idAutomovil == idAEliminar) {
            printf("El automovil con el ID %d ha sido eliminado.\n", idAEliminar); // Mostrar un mensaje de confirmacion de eliminacion
        } else {
            fprintf(archivoTemporal, "%s", linea); // Escribir la linea en el archivo temporal si no se debe eliminar
        }
    }

    // Cerrar los archivos
    fclose(archivoLectura);
    fclose(archivoTemporal);

    // Eliminar el archivo original
    if (remove("archivo.dat") != 0) {
        printf("Error al eliminar el archivo original.\n"); // Mostrar un mensaje de error si no se puede eliminar el archivo original
        return;
    }

    // Renombrar el archivo temporal
    if (rename("temporal.dat", "archivo.dat") != 0) {
        printf("Error al renombrar el archivo temporal.\n"); // Mostrar un mensaje de error si no se puede renombrar el archivo temporal
        return;
    }
}


// Funcion para modificar un automovil por su ID
void Modificar() {
    FILE *archivoLectura = fopen("archivo.dat", "r");
    if (archivoLectura == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    FILE *archivoTemporal = fopen("temporal.dat", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo abrir el archivo temporal.\n");
        fclose(archivoLectura); // Cerrar el archivo de lectura si no se pudo abrir el temporal
        return;
    }

    int idAModificar;
    printf("Ingrese el ID del automovil que desea modificar: ");
    scanf("%d", &idAModificar);

    int idAutomovil;
    char linea[1000];

    while (fgets(linea, sizeof(linea), archivoLectura) != NULL) {
        sscanf(linea, "%d", &idAutomovil);

        if (idAutomovil == idAModificar) {
            printf("Automovil con el ID %d.\n", idAModificar);

            // Solicitar al usuario que ingrese los datos modificados
            char marca[100], modelo[100], tipo_gasolina[100], color[100];
            float motor_cilindrada;
            int cantidad_asientos, cantidad_puertas;

            printf("Nueva Marca: ");
            scanf("%s", marca);
            printf("Nuevo Modelo: ");
            scanf("%s", modelo);
            printf("Nueva Cilindrada de motor: ");
            scanf("%f", &motor_cilindrada);
            printf("Nuevo Tipo de gasolina: ");
            scanf("%s", tipo_gasolina);
            printf("Nueva Cantidad de asientos: ");
            scanf("%d", &cantidad_asientos);
            printf("Nueva Cantidad de puertas: ");
            scanf("%d", &cantidad_puertas);
            printf("Nuevo Color: ");
            scanf("%s", color);

            // Escribir los datos modificados en el archivo temporal
            fprintf(archivoTemporal, "%d: %s-%s-%.1f-%s-%d-%d-%s\n", idAModificar, marca, modelo, motor_cilindrada, tipo_gasolina, cantidad_asientos, cantidad_puertas, color);
            printf("Automovil modificado con exito.\n");
        } else {
            // Si no es el automovil a modificar, simplemente copiar la linea al archivo temporal
            fprintf(archivoTemporal, "%s", linea);
        }
    }

    fclose(archivoLectura);
    fclose(archivoTemporal);

    if (remove("archivo.dat") != 0) {
        printf("Error al eliminar el archivo original.\n");
        return;
    }

    if (rename("temporal.dat", "archivo.dat") != 0) {
        printf("Error al renombrar el archivo temporal.\n");
        return;
    }
}

int main() {
    int opcion;
    do {
        printf("-------------------- CRUD DE AUTOMOVILES --------------------");
        printf("\nMenu de opciones:\n");
        printf("1. Ingresar\n");
        printf("2. Mostrar\n");
        printf("3. Eliminar\n");
        printf("4. Modificar\n");
        printf("0. Salir\n");
        printf("-------------------- CRUD DE AUTOMOVILES -------------------- \n");
        printf("Ingrese su eleccion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                Ingresar();
                break;
            case 2:
                Mostrar();
                break;
            case 3:
                Eliminar();
                break;
            case 4:
                Modificar();
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}