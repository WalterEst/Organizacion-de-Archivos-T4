#include <iostream>
#include <fstream>

// Definicion de la estructura para representar un automovil
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

// Funcion para obtener el valor del contador desde un archivo
int ObtenerContador() {
    std::ifstream contadorArchivo("contador.txt");
    if (!contadorArchivo.is_open()) {
        return 0;
    }
    int contador;
    contadorArchivo >> contador;
    contadorArchivo.close();
    return contador;
}

// Funcion para actualizar el valor del contador en el archivo
void ActualizarContador(int nuevoContador) {
    std::ofstream contadorArchivo("contador.txt");
    if (!contadorArchivo.is_open()) {
        std::cout << "Error al abrir el archivo del contador." << std::endl;
        return;
    }
    contadorArchivo << nuevoContador;
    contadorArchivo.close();
}

// Funcion para ingresar un automovil
void Ingresar() {
    // Abrir el archivo binario en modo de escritura binaria (append)
    std::ofstream archivo("archivo.bin", std::ios::binary | std::ios::app);
    
    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    // Obtener el numero de fila actual
    int numeroFila = ObtenerContador();
    numeroFila++;

    // Crear una nueva instancia de Automovil
    struct Automovil nuevoAutomovil;
    nuevoAutomovil.id = numeroFila;

    // Solicitar informacion al usuario y asignarla al nuevoAutomovil
    std::cout << "Marca: ";
    std::cin >> nuevoAutomovil.marca;
    std::cout << "Modelo: ";
    std::cin >> nuevoAutomovil.modelo;
    std::cout << "Cilindrada de motor: ";
    std::cin >> nuevoAutomovil.motor_cilindrada;
    std::cout << "Tipo de gasolina: ";
    std::cin >> nuevoAutomovil.tipo_gasolina;
    std::cout << "Cantidad de asientos: ";
    std::cin >> nuevoAutomovil.cantidad_asientos;
    std::cout << "Cantidad de puertas: ";
    std::cin >> nuevoAutomovil.cantidad_puertas;
    std::cout << "Color: ";
    std::cin >> nuevoAutomovil.color;

    // Escribir el nuevoAutomovil en el archivo binario
    archivo.write(reinterpret_cast<char*>(&nuevoAutomovil), sizeof(Automovil));
    std::cout << "Auto ingresado con exito." << std::endl;

    // Actualizar el contador en el archivo
    ActualizarContador(numeroFila);

    // Cerrar el archivo
    archivo.close();
}

// Funcion para mostrar el contenido del archivo
void Mostrar() {
    // Abrir el archivo binario en modo de lectura binaria
    std::ifstream archivo("archivo.bin", std::ios::binary);
    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    // Crear una instancia de Automovil para almacenar la informacion leida
    struct Automovil automovil;

    // Leer y mostrar cada Automovil en el archivo binario
    while (archivo.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        std::cout << "ID: " << automovil.id << ", Marca: " << automovil.marca << ", Modelo: " << automovil.modelo
                  << ", Cilindrada: " << automovil.motor_cilindrada << ", Gasolina: " << automovil.tipo_gasolina
                  << ", Asientos: " << automovil.cantidad_asientos << ", Puertas: " << automovil.cantidad_puertas
                  << ", Color: " << automovil.color << std::endl;
    }

    // Cerrar el archivo
    archivo.close();
}

// Funcion para eliminar una entrada de un archivo
void Eliminar() {
    // Abrir el archivo de entrada para lectura
    std::ifstream archivoEntrada("archivo.bin", std::ios::binary);
    if (!archivoEntrada.is_open()) {
        std::cout << "No se pudo abrir el archivo para lectura." << std::endl;
        return;
    }

    // Crear una instancia de Automovil para almacenar la informacion leida
    struct Automovil automovil;
    std::cout << "Lista de automoviles:" << std::endl;

    // Mostrar la lista de automoviles
    while (archivoEntrada.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        std::cout << "ID: " << automovil.id << ", Marca: " << automovil.marca << ", Modelo: " << automovil.modelo
                  << ", Cilindrada: " << automovil.motor_cilindrada << ", Gasolina: " << automovil.tipo_gasolina
                  << ", Asientos: " << automovil.cantidad_asientos << ", Puertas: " << automovil.cantidad_puertas
                  << ", Color: " << automovil.color << std::endl;
    }

    // Cerrar el archivo de entrada
    archivoEntrada.close();

    // Solicitar al usuario el ID del automovil que desea eliminar
    int idAEliminar;
    std::cout << "Ingrese el ID del automovil que desea eliminar: ";
    std::cin >> idAEliminar;

    // Abrir el archivo de entrada nuevamente para leer
    std::ifstream archivoEntrada2("archivo.bin", std::ios::binary);
    if (!archivoEntrada2.is_open()) {
        std::cout << "No se pudo abrir el archivo para lectura." << std::endl;
        return;
    }

    // Abrir un archivo temporal para escribir
    std::ofstream archivoTemporal("temporal.bin", std::ios::binary);
    if (!archivoTemporal.is_open()) {
        std::cout << "No se pudo abrir el archivo temporal." << std::endl;
        archivoEntrada2.close();
        return;
    }

    // Leer y escribir los automoviles en el archivo temporal, omitiendo el que se va a eliminar
    while (archivoEntrada2.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        if (automovil.id != idAEliminar) {
            archivoTemporal.write(reinterpret_cast<char*>(&automovil), sizeof(Automovil));
        } else {
            std::cout << "El automovil con el ID " << idAEliminar << " ha sido eliminado." << std::endl;
        }
    }

    // Cerrar los archivos de entrada y temporal
    archivoEntrada2.close();
    archivoTemporal.close();

    // Eliminar el archivo original y renombrar el temporal
    if (remove("archivo.bin") != 0) {
        std::cout << "Error al eliminar el archivo original." << std::endl;
        return;
    }

    if (rename("temporal.bin", "archivo.bin") != 0) {
        std::cout << "Error al renombrar el archivo temporal." << std::endl;
        return;
    }
}

// Funcion para modificar un automovil por su ID
void Modificar() {
    // Solicitar al usuario el ID del automovil que desea modificar
    int idAModificar;
    std::cout << "Ingrese el ID del automovil que desea modificar: ";
    std::cin >> idAModificar;

    // Abrir el archivo binario para lectura y escritura
    std::fstream archivo("archivo.bin", std::ios::binary | std::ios::in | std::ios::out);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo para lectura/escritura." << std::endl;
        return;
    }

    // Crear una instancia de Automovil para almacenar la informacion leida
    Automovil automovil;

    // Leer y buscar el automovil con el ID a modificar
    while (archivo.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        if (automovil.id == idAModificar) {
            // Mostrar informacion del automovil encontrado
            std::cout << "Automovil con el ID " << idAModificar << "." << std::endl;

            // Solicitar al usuario que ingrese los datos modificados
            std::cout << "Nueva Marca: ";
            std::cin >> automovil.marca;
            std::cout << "Nuevo Modelo: ";
            std::cin >> automovil.modelo;
            std::cout << "Nueva Cilindrada de motor: ";
            std::cin >> automovil.motor_cilindrada;
            std::cout << "Nuevo Tipo de gasolina: ";
            std::cin >> automovil.tipo_gasolina;
            std::cout << "Nueva Cantidad de asientos: ";
            std::cin >> automovil.cantidad_asientos;
            std::cout << "Nueva Cantidad de puertas: ";
            std::cin >> automovil.cantidad_puertas;
            std::cout << "Nuevo Color: ";
            std::cin >> automovil.color;

            // Colocar el puntero de lectura/escritura en la posicion correcta
            archivo.seekp(-static_cast<int>(sizeof(Automovil)), std::ios::cur);

            // Escribir los datos modificados en el archivo
            archivo.write(reinterpret_cast<char*>(&automovil), sizeof(Automovil));

            std::cout << "Automovil modificado con exito." << std::endl;
            break;
        }
    }

    // Cerrar el archivo
    archivo.close();
}

// Funcion principal
int main() {
    int opcion;
    do {
        // Menu de opciones
        std::cout << "-------------------- CRUD DE AUTOMOVILES --------------------" << std::endl;
        std::cout << "Menu de opciones:" << std::endl;
        std::cout << "1. Ingresar" << std::endl;
        std::cout << "2. Mostrar" << std::endl;
        std::cout << "3. Eliminar" << std::endl;
        std::cout << "4. Modificar" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "-------------------- CRUD DE AUTOMOVILES --------------------" << std::endl;
        std::cout << "Ingrese su eleccion: ";
        std::cin >> opcion;

        // Realizar acciones segun la opción seleccionada
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
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida." << std::endl;
        }
    } while (opcion != 0);

    return 0;
}


//se compila -> g++ main.cpp -o main.exe
//luego -> main.exe