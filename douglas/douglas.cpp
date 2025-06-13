#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;

// Definicion de colores de la interfaz del usuario
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

class Database {
public:
    MYSQL* conectar;

    Database() {
        conectar = mysql_init(0);
        if (conectar == NULL) {
            cerr << RED << "mysql_init() fallo" << RESET << endl;
            exit(1);
        }

        conectar = mysql_real_connect(conectar, "localhost", "root", "douglas", "BoardingPassDB", 3306, NULL, 0);
        if (conectar) {
            cout << GREEN << "Conexion Exitosa" << RESET << endl;
        }
        else {
            cerr << RED << "No se conecto: " << mysql_error(conectar) << RESET << endl;
            exit(1);
        }
    }

    ~Database() {
        if (conectar) {
            mysql_close(conectar);
        }
    }

    // CRUD para Pasajeros
    void createPassenger(const string& name) {
        string query = "INSERT INTO Pasajeros (nombre_completo) VALUES ('" + name + "')";
        executeQuery(query, "Pasajero agregado exitosamente.", "Error al agregar pasajero");
    }

    void readPassengers() {
        executeReadQuery("SELECT * FROM Pasajeros", "ID", "Nombre");
    }

    void updatePassenger(int id, const string& newName) {
        string query = "UPDATE Pasajeros SET nombre_completo = '" + newName + "' WHERE id = " + to_string(id);
        executeQuery(query, "Pasajero actualizado exitosamente.", "Error al actualizar pasajero");
    }

    void deletePassenger(int id) {
        string query = "DELETE FROM Pasajeros WHERE id = " + to_string(id);
        executeQuery(query, "Pasajero eliminado exitosamente.", "Error al eliminar pasajero");
    }

    // CRUD para Aeropuertos
    void createAirport(const string& name, const string& code) {
        string query = "INSERT INTO Aeropuertos (nombre, codigo) VALUES ('" + name + "', '" + code + "')";
        executeQuery(query, "Aeropuerto agregado exitosamente.", "Error al agregar aeropuerto");
    }

    void readAirports() {
        executeReadQuery("SELECT * FROM Aeropuertos", "ID", "Nombre", "Codigo");
    }

    void updateAirport(int id, const string& newName, const string& newCode) {
        string query = "UPDATE Aeropuertos SET nombre = '" + newName + "', codigo = '" + newCode + "' WHERE id = " + to_string(id);
        executeQuery(query, "Aeropuerto actualizado exitosamente.", "Error al actualizar aeropuerto");
    }

    void deleteAirport(int id) {
        string query = "DELETE FROM Aeropuertos WHERE id = " + to_string(id);
        executeQuery(query, "Aeropuerto eliminado exitosamente.", "Error al eliminar aeropuerto");
    }

    // CRUD para Vuelos
    void createFlight(const string& flightNumber, int airportId) {
        string query = "INSERT INTO Vuelos (numero_vuelo, aeropuerto_id) VALUES ('" + flightNumber + "', " + to_string(airportId) + ")";
        executeQuery(query, "Vuelo agregado exitosamente.", "Error al agregar vuelo");
    }

    void readFlights() {
        executeReadQuery("SELECT * FROM Vuelos", "ID", "Numero de Vuelo", "Aeropuerto ID");
    }

    void updateFlight(int id, const string& newFlightNumber) {
        string query = "UPDATE Vuelos SET numero_vuelo = '" + newFlightNumber + "' WHERE id = " + to_string(id);
        executeQuery(query, "Vuelo actualizado exitosamente.", "Error al actualizar vuelo");
    }

    void deleteFlight(int id) {
        string query = "DELETE FROM Vuelos WHERE id = " + to_string(id);
        executeQuery(query, "Vuelo eliminado exitosamente.", "Error al eliminar vuelo");
    }

private:
    void executeQuery(const string& query, const string& successMsg, const string& errorMsg) {
        if (mysql_query(conectar, query.c_str())) {
            cerr << RED << errorMsg << ": " << mysql_error(conectar) << RESET << endl;
        }
        else {
            cout << GREEN << successMsg << RESET << endl;
        }
    }

    void executeReadQuery(const string& query, const string& col1, const string& col2, const string& col3 = "") {
        if (mysql_query(conectar, query.c_str())) {
            cerr << RED << "Error al consultar: " << mysql_error(conectar) << RESET << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(conectar);
        if (result) {
            while (MYSQL_ROW row = mysql_fetch_row(result)) {
                cout << CYAN << col1 << ": " << row[0] << ", " << col2 << ": " << row[1];
                if (!col3.empty()) cout << ", " << col3 << ": " << row[2];
                cout << RESET << endl;
            }
            mysql_free_result(result);
        }
        else {
            cerr << RED << "Error al obtener resultados: " << mysql_error(conectar) << RESET << endl;
        }
    }
};

void displayMenu() {
    cout << "\n" << BLUE << "--- Menu ---" << RESET << endl;
    cout << YELLOW << "1. Agregar Pasajero" << RESET << endl;
    cout << YELLOW << "2. Mostrar Pasajeros" << RESET << endl;
    cout << YELLOW << "3. Actualizar Pasajero" << RESET << endl;
    cout << YELLOW << "4. Eliminar Pasajero" << RESET << endl;
    cout << YELLOW << "5. Agregar Aeropuerto" << RESET << endl;
    cout << YELLOW << "6. Mostrar Aeropuertos" << RESET << endl;
    cout << YELLOW << "7. Actualizar Aeropuerto" << RESET << endl;
    cout << YELLOW << "8. Eliminar Aeropuerto" << RESET << endl;
    cout << YELLOW << "9. Agregar Vuelo" << RESET << endl;
    cout << YELLOW << "10. Mostrar Vuelos" << RESET << endl;
    cout << YELLOW << "11. Actualizar Vuelo" << RESET << endl;
    cout << YELLOW << "12. Eliminar Vuelo" << RESET << endl;
    cout << YELLOW << "0. Salir" << RESET << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Database db;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            cout << "Ingrese el nombre completo del pasajero: ";
            cin.ignore();
            getline(cin, name);
            db.createPassenger(name);
            break;
        }
        case 2:
            db.readPassengers();
            break;
        case 3: {
            int id;
            string newName;
            cout << "Ingrese el ID del pasajero a actualizar: ";
            cin >> id;
            cout << "Ingrese el nuevo nombre: ";
            cin.ignore();
            getline(cin, newName);
            db.updatePassenger(id, newName);
            break;
        }
        case 4: {
            int id;
            cout << "Ingrese el ID del pasajero a eliminar: ";
            cin >> id;
            db.deletePassenger(id);
            break;
        }
        case 5: {
            string name, code;
            cout << "Ingrese el nombre del aeropuerto: ";
            cin.ignore();
            getline(cin, name);
            cout << "Ingrese el codigo del aeropuerto: ";
            getline(cin, code);
            db.createAirport(name, code);
            break;
        }
        case 6:
            db.readAirports();
            break;
        case 7: {
            int id;
            string newName, newCode;
            cout << "Ingrese el ID del aeropuerto a actualizar: ";
            cin >> id;
            cout << "Ingrese el nuevo nombre: ";
            cin.ignore();
            getline(cin, newName);
            cout << "Ingrese el nuevo codigo: ";
            getline(cin, newCode);
            db.updateAirport(id, newName, newCode);
            break;
        }
        case 8: {
            int id;
            cout << "Ingrese el ID del aeropuerto a eliminar: ";
            cin >> id;
            db.deleteAirport(id);
            break;
        }
        case 9: {
            string flightNumber;
            int airportId;
            cout << "Ingrese el numero de vuelo: ";
            cin.ignore();
            getline(cin, flightNumber);
            cout << "Ingrese el ID del aeropuerto: ";
            cin >> airportId;
            db.createFlight(flightNumber, airportId);
            break;
        }
        case 10:
            db.readFlights();
            break;
        case 11: {
            int id;
            string newFlightNumber;
            cout << "Ingrese el ID del vuelo a actualizar: ";
            cin >> id;
            cout << "Ingrese el nuevo numero de vuelo: ";
            cin.ignore();
            getline(cin, newFlightNumber);
            db.updateFlight(id, newFlightNumber);
            break;
        }
        case 12: {
            int id;
            cout << "Ingrese el ID del vuelo a eliminar: ";
            cin >> id;
            db.deleteFlight(id);
            break;
        }
        case 0:
            cout << GREEN << "Saliendo..." << RESET << endl;
            break;
        default:
            cerr << RED << "Opcion no valida. Intente de nuevo." << RESET << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}