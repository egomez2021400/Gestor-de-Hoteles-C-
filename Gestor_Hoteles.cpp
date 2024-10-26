// Edgar Edwin Alexander Gómez García 9989 24 12591
// Paula Estefania Donado Castillo 9989 24 3203
// Jorge Luis Torres Jimenez 9989 24 17775
// Diego Rafael Mix Ochoa 9989 24 8050
// Sección: C
// Fecha de Creación: Indefinida
// Fecha de Modificación: 24/10/2024

#include <iostream>
#include <fstream> // Para manejo de archivos ifstream y ofstream
#include <vector>  // Para usar vectores dinamicos
#include <string>  // Para manejar cadenas de caracteres
#include <iomanip> // Para formatear salida con setw()
#include <sstream> // Para convertir flotantes a string en C++98

using namespace std;

// Clase de habitacion (equivalente a la clase hijo)
class Cuarto {
public:
    string id; 
    string detalle;
    float costo;

    Cuarto(string id, string detalle, float costo)  // Constructor inicializa atributos
        : id(id), detalle(detalle), costo(costo) {}
};

// Clase de reservacion (equivalente a la clase padre)
class Reserva {
public:
    string idReserva;
    string nombreHuesped;
    string checkIn;
    string checkOut;
    vector<Cuarto> cuartos;
    float totalReserva;

    Reserva(const string& idReserva, const string& nombreHuesped, const string& checkIn, const string& checkOut)
        : idReserva(idReserva), nombreHuesped(nombreHuesped), checkIn(checkIn), checkOut(checkOut), totalReserva(0.0f) {}

    // Metodo para agregar una habitacion a la reserva
    void agregarCuarto(const Cuarto& cuarto) {
        cuartos.push_back(cuarto);
        totalReserva += cuarto.costo;
    }

    // Metodo para convertir un número flotante a cadena (equivalente a to_string)
    string floatToString(float number) const {
        ostringstream buff;
        buff << number;
        return buff.str();
    }

    // Metodo para guardar la reserva en un archivo
    void guardarReserva() const {
        ofstream archivo(("Reserva_" + idReserva + ".txt").c_str());  // Guardar con nombre diferente
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo para guardar la reserva." << endl;
            return;
        }

        archivo << "ID de la Reserva: " << idReserva << endl;
        archivo << "Nombre del Huesped: " << nombreHuesped << endl; 
        archivo << "Fecha de ingreso: " << checkIn << endl;
        archivo << "Fecha de salida: " << checkOut << endl;
        archivo << "Cuartos reservados:" << endl;

        // Imprimir cabecera de tabla con ancho fijo de columnas
        archivo << left << setw(10) << "ID"
                << setw(30) << "Detalle"
                << setw(10) << "Costo" << endl;
        archivo << string(50, '-') << endl;

        // Recorrer y mostrar cuartos reservados usando un bucle tradicional
        for (size_t i = 0; i < cuartos.size(); ++i) {
            archivo << left << setw(10) << cuartos[i].id
                    << setw(30) << cuartos[i].detalle
                    << setw(10) << "Q" + floatToString(cuartos[i].costo) << endl;
        }

        archivo << string(50, '-') << endl;
        archivo << "Total de la Reserva: Q" << floatToString(totalReserva) << endl;
        archivo.close();

        cout << "Reserva guardada exitosamente en el archivo 'Reserva_" << idReserva << ".txt'" << endl;
    }
};

// Funcion para registrar una nueva reserva
void nuevaReserva() {
    string idReserva, nombreHuesped, checkIn, checkOut;
    
    cout << "Ingrese el codigo de reservación: ";
    cin >> idReserva;
    cin.ignore();
    cout << "Ingrese el nombre del huesped: ";
    getline(cin, nombreHuesped);
    cout << "Ingrese la fecha de ingreso: ";
    cin >> checkIn;
    cout << "Ingrese la fecha de salida: ";
    cin >> checkOut;

    Reserva reserva(idReserva, nombreHuesped, checkIn, checkOut);

    char masCuartos;
    do {
        string idCuarto, detalle;
        float costo;

        cout << "Ingrese el codigo de habitación: ";
        cin >> idCuarto;
        cin.ignore();
        cout << "Ingrese la descripción del cuarto: ";
        getline(cin, detalle);	        
        cout << "Ingrese el costo del cuarto: ";
        cin >> costo;

        Cuarto cuarto(idCuarto, detalle, costo);
        reserva.agregarCuarto(cuarto);

        cout << "Desea agregar otro cuarto? (s/n): ";
        cin >> masCuartos;

    } while (masCuartos == 's' || masCuartos == 'S');

    reserva.guardarReserva();
}

// Funcion para buscar una reserva existente
void buscarReserva() {
    string idReserva;
    cout << "Ingrese el ID de la reserva a buscar: ";
    cin >> idReserva;

    ifstream archivo(("Reserva_" + idReserva + ".txt").c_str());

    if (!archivo.is_open()) {
        cout << "No se encontro la reserva con ID: " << idReserva << "." << endl;
        return;
    }

    // Mostrar línea por línea en lugar de palabra por palabra
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

// Funcion del menu
void mostrarMenu() {
    int opcion;
    do {
        cout << "\nMenu de Reservas" << endl;
        cout << "1. Registrar nueva reserva" << endl;
        cout << "2. Buscar reserva" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            nuevaReserva();
            break;
        case 2:
            buscarReserva();
            break;
        case 3:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 3);
}

int main() {
    setlocale(LC_ALL, "");	
    mostrarMenu();
    return 0;
}

