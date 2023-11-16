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
    std::ofstream archivo("archivo.bin", std::ios::binary | std::ios::app);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    int numeroFila = ObtenerContador();
    numeroFila++;

    struct Automovil nuevoAutomovil;

    nuevoAutomovil.id = numeroFila;

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

    archivo.write(reinterpret_cast<char*>(&nuevoAutomovil), sizeof(Automovil));
    std::cout << "Auto ingresado con exito." << std::endl;

    ActualizarContador(numeroFila);

    archivo.close();
}

// Funcion para mostrar el contenido del archivo
void Mostrar() {
    std::ifstream archivo("archivo.bin", std::ios::binary);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    struct Automovil automovil;

    while (archivo.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        std::cout << "ID: " << automovil.id << ", Marca: " << automovil.marca << ", Modelo: " << automovil.modelo
                  << ", Cilindrada: " << automovil.motor_cilindrada << ", Gasolina: " << automovil.tipo_gasolina
                  << ", Asientos: " << automovil.cantidad_asientos << ", Puertas: " << automovil.cantidad_puertas
                  << ", Color: " << automovil.color << std::endl;
    }

    archivo.close();
}

// Funcion para eliminar una entrada de un archivo
void Eliminar() {
    std::ifstream archivoEntrada("archivo.bin", std::ios::binary);
    if (!archivoEntrada.is_open()) {
        std::cout << "No se pudo abrir el archivo para lectura." << std::endl;
        return;
    }

    struct Automovil automovil;
    std::cout << "Lista de automoviles:" << std::endl;

    while (archivoEntrada.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        std::cout << "ID: " << automovil.id << ", Marca: " << automovil.marca << ", Modelo: " << automovil.modelo
                  << ", Cilindrada: " << automovil.motor_cilindrada << ", Gasolina: " << automovil.tipo_gasolina
                  << ", Asientos: " << automovil.cantidad_asientos << ", Puertas: " << automovil.cantidad_puertas
                  << ", Color: " << automovil.color << std::endl;
    }

    archivoEntrada.close();

    int idAEliminar;
    std::cout << "Ingrese el ID del automovil que desea eliminar: ";
    std::cin >> idAEliminar;

    std::ifstream archivoEntrada2("archivo.bin", std::ios::binary);
    if (!archivoEntrada2.is_open()) {
        std::cout << "No se pudo abrir el archivo para lectura." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("temporal.bin", std::ios::binary);
    if (!archivoTemporal.is_open()) {
        std::cout << "No se pudo abrir el archivo temporal." << std::endl;
        archivoEntrada2.close();
        return;
    }

    while (archivoEntrada2.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        if (automovil.id != idAEliminar) {
            archivoTemporal.write(reinterpret_cast<char*>(&automovil), sizeof(Automovil));
        } else {
            std::cout << "El automovil con el ID " << idAEliminar << " ha sido eliminado." << std::endl;
        }
    }

    archivoEntrada2.close();
    archivoTemporal.close();

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
    int idAModificar;
    std::cout << "Ingrese el ID del automovil que desea modificar: ";
    std::cin >> idAModificar;

    std::fstream archivo("archivo.bin", std::ios::binary | std::ios::in | std::ios::out);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo para lectura/escritura." << std::endl;
        return;
    }

    Automovil automovil;

    while (archivo.read(reinterpret_cast<char*>(&automovil), sizeof(Automovil))) {
        if (automovil.id == idAModificar) {
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

            // Colocar el puntero de lectura/escritura en la posición correcta
            archivo.seekp(-static_cast<int>(sizeof(Automovil)), std::ios::cur);

            // Escribir los datos modificados en el archivo
            archivo.write(reinterpret_cast<char*>(&automovil), sizeof(Automovil));

            std::cout << "Automovil modificado con exito." << std::endl;
            break;
        }
    }

    archivo.close();
}

int main() {
    int opcion;
    do {
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