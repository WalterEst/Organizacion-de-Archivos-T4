#include <stdio.h>

// Funcion para obtener el valor del contador desde un archivo
int ObtenerContador() {

    // Abrimos el archivo "contador.txt" en modo lectura
    FILE *contadorArchivo = fopen("contador.txt", "r");
    if (contadorArchivo == NULL) {
        return 0; // Si el archivo no existe, el contador se inicia en 0
    }
    int contador;

    // Leemos el valor del contador desde el archivo
    fscanf(contadorArchivo, "%d", &contador);
    fclose(contadorArchivo); // Cerramos el archivo
    return contador; // Devolvemos el valor del contador
}

// Funcion para actualizar el valor del contador en el archivo
void ActualizarContador(int nuevoContador) {
    FILE *contadorArchivo = fopen("contador.txt", "w");

    if (contadorArchivo == NULL) {
        printf("Error al abrir el archivo del contador.\n");
        return; // Si no se pudo abrir el archivo, mostramos un mensaje de error y salimos de la funcion
    }

    // Escribimos el nuevo valor del contador en el archivo
    fprintf(contadorArchivo, "%d", nuevoContador);
    fclose(contadorArchivo); // Cerramos el archivo
}

// Declarar la funcion Ingresar
void Ingresar() {
    FILE *archivo = fopen("archivo.dat", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    // Obtener el valor actual del contador
    int numeroFila = ObtenerContador();

    // Incrementar el contador para la siguiente insercion
    numeroFila++;

    // Declarar variables para almacenar los datos del auto
    char marca[100], modelo[100], tipo_gasolina[100], color[100];
    float motor_cilindrada;
    int cantidad_asientos, cantidad_puertas;
    
    // Solicitar al usuario que ingrese los datos del auto
    printf("Marca: ");
    scanf("%s", marca);
    printf("Modelo: ");
    scanf("%s", modelo);
    printf("Cilindrada de motor: ");
    scanf("%f", &motor_cilindrada);
    printf("Tipo de gasolina: ");
    scanf("%s", tipo_gasolina);
    printf("Cantidad de asientos: ");
    scanf("%d", &cantidad_asientos);
    printf("Cantidad de puertas: ");
    scanf("%d", &cantidad_puertas);
    printf("Color: ");
    scanf("%s", color);

    // Escribir los datos del auto en el archivo en un formato especifico con el numero de fila
    fprintf(archivo, "%d: %s-%s-%.1f-%s-%d-%d-%s\n", numeroFila, marca, modelo, motor_cilindrada, tipo_gasolina, cantidad_asientos, cantidad_puertas, color);
    printf("Auto ingresado con exito.\n");

    // Actualizar el contador en el archivo
    ActualizarContador(numeroFila);

    // Cerrar el archivo
    fclose(archivo);
}

// Funcion para abrir y mostrar el contenido de un archivo
void Mostrar() {
    // Abrir el archivo "archivo.dat" en modo lectura
    FILE *archivo = fopen("archivo.dat", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n"); // Mostrar un mensaje de error si no se puede abrir el archivo
        return;
    }

    char linea[1000];
    // Leer y mostrar cada linea del archivo
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s \n", linea); // Imprimir cada linea en la consola
    }

    // Cerrar el archivo despues de leerlo
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

// Funcion para cambiar el formato de separacion en el archivo
void CambiarFormatoEnArchivo() {
    // Abrir el archivo en modo lectura y escritura
    FILE *archivo = fopen("archivo.dat", "r+");
    if (archivo == NULL) {
        printf("El archivo no se puede abrir.\n");
        return;
    }

    char formato;
    // Solicitar al usuario que ingrese el nuevo caracter de separacion
    printf("Ingresa separador, '-' o '/' o ';' o ':': ");
    scanf(" %c", &formato);

    int caracter;
    // Leer cada caracter en el archivo y reemplazar '-' o '/' por el nuevo caracter
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == '-' || caracter == '/' || caracter == ';' || caracter == ':') {
            fseek(archivo, -1, SEEK_CUR);
            fputc(formato, archivo);
            fseek(archivo, 0, SEEK_CUR);
        }
    }

    // Cerrar el archivo
    fclose(archivo);
    printf("Reemplazo completado.\n");
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
        printf("5. Cambiar separador\n");
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
            case 5:
                CambiarFormatoEnArchivo();
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