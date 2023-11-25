#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Articulo {
    int numero;
    string nombre;
    int cantidad;
    double precioUnitario;
};

struct Orden {
    int numeroTicket;
    string razonSocial;
    string nombreVendedor;
    string fecha;
    vector<Articulo> articulos;
    double descuento;
    double propina;
    double impuesto;
    double total;
    bool cancelada;
    int numeroMesa;
    int numeroOrden;
};

void altaOrden(vector<Orden>& listaOrdenes, int& numeroTicket) {
    Orden nuevaOrden;
    nuevaOrden.numeroTicket = numeroTicket++;
    cout << "Razon Social del Restaurante: ";
    cin.ignore();
    getline(cin, nuevaOrden.razonSocial);
    cout << "Nombre del Vendedor: ";
    getline(cin, nuevaOrden.nombreVendedor);
    cout << "Fecha (DD/MM/AAAA): ";
    cin >> nuevaOrden.fecha;

    int numArticulos;
    cout << "-------------------------------\n";
    cout << "Ingrese el numero de articulos: ";
    cin >> numArticulos;

    for (int i = 0; i < numArticulos; ++i) {
        Articulo nuevoArticulo;
        cout << "Articulo " << i + 1 << ":\n";
        cout << "Numero: ";
        cin >> nuevoArticulo.numero;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, nuevoArticulo.nombre);
        cout << "Cantidad: ";
        cin >> nuevoArticulo.cantidad;
        cout << "Precio Unitario: ";
        cin >> nuevoArticulo.precioUnitario;

        nuevaOrden.articulos.push_back(nuevoArticulo);
    }
    cout << "-------------------------------\n";
    cout << "Numero de Mesa: ";
    cin >> nuevaOrden.numeroMesa;
    cout << "Numero de Orden: ";
    cin >> nuevaOrden.numeroOrden;
    cout << "-------------------------------\n";
    cout << "Descuento (%): ";
    cin >> nuevaOrden.descuento;
    cout << "Propina (%): ";
    cin >> nuevaOrden.propina;
    cout << "Impuesto (%): ";
    cin >> nuevaOrden.impuesto;

    // Calcular total
    nuevaOrden.total = 0;

    for (const Articulo& articulo : nuevaOrden.articulos) {
        nuevaOrden.total += articulo.cantidad * articulo.precioUnitario;
    }
    cout << "-------------------------------\n";
    cout << "El total de articulos es: " << nuevaOrden.total << "\n";
    nuevaOrden.total = nuevaOrden.total * (1 - nuevaOrden.descuento / 100);
    nuevaOrden.total = nuevaOrden.total * (1 + nuevaOrden.propina / 100);
    nuevaOrden.total = nuevaOrden.total * (1 + nuevaOrden.impuesto / 100);
   
    nuevaOrden.cancelada = false;

    listaOrdenes.push_back(nuevaOrden);

    cout << "Orden creada con exito. Numero de Ticket: " << nuevaOrden.numeroTicket << "\n";
    cout << "-------------------------------\n";
}

void modificarOrden(vector<Orden>& listaOrdenes) {
    int numeroTicket;
    cout << "Ingrese el numero de Ticket a modificar: ";
    cin >> numeroTicket;
    cout << "-------------------------------\n";
    for (Orden& orden : listaOrdenes) {
        if (orden.numeroTicket == numeroTicket && !orden.cancelada) {
            cout << "Informacion actual de la Orden:\n";
            cout << "-------------------------------\n";
            cout << "Razon Social del Restaurante: " << orden.razonSocial << "\n";
            cout << "Nombre del Vendedor: " << orden.nombreVendedor << "\n";
            cout << "Fecha: " << orden.fecha << "\n";
            cout << "-------------------------------\n";

            cout << "Articulos:\n";
            for (Articulo& articulo : orden.articulos) {
                cout << "Numero: " << articulo.numero << "\nNombre: " << articulo.nombre
                    << "\nCantidad: " << articulo.cantidad << "\nPrecio Unitario: " << articulo.precioUnitario << "\n";
                cout << "-------------------------------\n";
                // articulos modificar
                cout << "Ingrese la nueva informacion del articulo:\n";
                cout << "Numero del articulo:";
                cin >> articulo.numero;
                cout << "Nombre del articulo: ";
                cin >> articulo.nombre;
                cout << "Cantidad:";
                cin >> articulo.cantidad;
                cout << "Precio Unitario del articulo: ";
                cin >> articulo.precioUnitario;
            }
            cout << "-------------------------------\n";
            cout << "TOTAL ANTES DE MODIFICAR\n";
            cout << "Descuento (%): " << orden.descuento << "\n";
            cout << "Propina (%): " << orden.propina << "\n";
            cout << "Impuesto (%): " << orden.impuesto << "\n";
            cout << "Total: " << orden.total << "\n";
            cout << "Estado: " << (orden.cancelada ? "Cancelada" : "Activa") << "\n";
            cout << "---------------------------------\n";

            // orden modificar
            cout << "Ingrese la nueva informacion de la orden:\n";
            cout << "Razon Social del Restaurante: ";
            cin.ignore();
            getline(cin, orden.razonSocial);
            cout << "Nombre del Vendedor: ";
            getline(cin, orden.nombreVendedor);
            cout << "Fecha (DD/MM/AAAA): ";
            cin >> orden.fecha;
            cout << "-------------------------------\n";

            cout << "Numero de Mesa: ";
            cin >> orden.numeroMesa;
            cout << "Numero de Orden: ";
            cin >> orden.numeroOrden;
            cout << "-------------------------------\n";

            cout << "Descuento (%): ";
            cin >> orden.descuento;
            cout << "Propina (%): ";
            cin >> orden.propina;
            cout << "Impuesto (%): ";
            cin >> orden.impuesto;
            cout << "-------------------------------\n";

            orden.total = 0;
            for (const Articulo& articulo : orden.articulos) {
                orden.total += articulo.cantidad * articulo.precioUnitario;
            }
            cout << "El total de articulos es: " << orden.total << "\n";
            cout << "-------------------------------\n";
            orden.total = orden.total * (1 - orden.descuento / 100);
            orden.total = orden.total * (1 + orden.propina / 100);
            orden.total = orden.total * (1 + orden.impuesto / 100);

            cout << "Orden modificada con exito.\n";
            cout << "-------------------------------\n";
            return;
        }
    }

    cout << "No se encontro la Orden o esta cancelada.\n";
}


void eliminarOrden(vector<Orden>& listaOrdenes) {
    int numeroTicket;
    cout << "Ingrese el numero de Ticket a eliminar: ";
    cin >> numeroTicket;

    for (Orden& orden : listaOrdenes) {
        if (orden.numeroTicket == numeroTicket) {
            // Marca la orden como cancelada
            orden.cancelada = true;
            cout << "Orden cancelada con exito.\n";
            return;
        }
    }

    cout << "No se encontro la Orden.\n";
}

void mostrarOrdenes(const vector<Orden>& listaOrdenes) {
    if (listaOrdenes.empty()) {
        cout << "No hay ordenes para mostrar.\n";
        return;
    }

    cout << "Lista de Ordenes:\n";
    for (const Orden& orden : listaOrdenes) {
        cout << "Numero de Ticket: " << orden.numeroTicket << "\n";
        cout << "Razon Social del Restaurante: " << orden.razonSocial << "\n";
        cout << "Nombre del Vendedor: " << orden.nombreVendedor << "\n";
        cout << "Fecha: " << orden.fecha << "\n";

        cout << "Articulos:\n";
        for (const Articulo& articulo : orden.articulos) {
            cout << "    Numero: " << articulo.numero << "\n"
                << "    Nombre: " << articulo.nombre << "\n"
                << "    Cantidad: " << articulo.cantidad << "\n"
                << "    Precio Unitario: " << articulo.precioUnitario << "\n";
        }

        cout << "Numero de Mesa: " << orden.numeroMesa << "\n";
        cout << "Numero de Orden: " << orden.numeroOrden << "\n";
        cout << "Descuento (%): " << orden.descuento << "\n";
        cout << "Propina (%): " << orden.propina << "\n";
        cout << "Impuesto (%): " << orden.impuesto << "\n";
        cout << "Total: " << orden.total << "\n";
        cout << "Estado: " << (orden.cancelada ? "Cancelada" : "Activa") << "\n";
        cout << "------------------------\n";
    }
}


void generarArchivo(const vector<Orden>& listaOrdenes) {
    ofstream archivo("La Casa de las papas.txt");

    if (archivo.is_open()) {
        for (const Orden& orden : listaOrdenes) {
            archivo << "Numero de Ticket: " << orden.numeroTicket << "\n";
            archivo << "Razon Social del Restaurante: " << orden.razonSocial << "\n";
            archivo << "Nombre del Vendedor: " << orden.nombreVendedor << "\n";
            archivo << "Fecha: " << orden.fecha << "\n";
            //modificacion estetica pendiente
            archivo << "Articulos:\n";
            for (const Articulo& articulo : orden.articulos) {
                archivo << "Numero: " << articulo.numero << "\n"
                    << "Nombre: " << articulo.nombre << "\n"
                    << "Cantidad: " << articulo.cantidad << "\n"
                    << "Precio Unitario: " << articulo.precioUnitario << "\n";
            }
            archivo << "Numero de Mesa: " << orden.numeroMesa << "\n";
            archivo << "Numero de Orden: " << orden.numeroOrden << "\n";
            archivo << "Descuento (%): " << orden.descuento << "\n";
            archivo << "Propina (%): " << orden.propina << "\n";
            archivo << "Impuesto (%): " << orden.impuesto << "\n";
            archivo << "Total: " << orden.total << "\n";
            archivo << "Estado: " << (orden.cancelada ? "Cancelada" : "Activa") << "\n";
            archivo << "---------------------------------\n";
        }

        archivo.close();
        cout << "Archivo generado con la informacion de las ordenes.\n";
    }
    else {
        cerr << "Error al abrir el archivo para escribir.\n";
    }
}

void limpiarPantalla() {
    system("cls");
}

int main() {
    vector<Orden> listaOrdenes;
    int numeroTicket = 1;
    int opcion;

    do {
        cout << "BIENVENIDO LA CASA DE LAS PAPAS\n";
        cout << ".........................\n";
        cout << "Menu de opciones:\n";
        cout << "1. Alta de Orden\n";
        cout << "2. Modificar Orden\n";
        cout << "3. Eliminar o Cancelar Orden\n";
        cout << "4. Lista de Ordenes\n";
        cout << "5. Limpiar pantalla\n";
        cout << "6. Salir\n";
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            altaOrden(listaOrdenes, numeroTicket);
            break;
        case 2:
            modificarOrden(listaOrdenes);
            break;
        case 3:
            eliminarOrden(listaOrdenes);
            break;
        case 4:
            mostrarOrdenes(listaOrdenes);
            break;
        case 5:
            limpiarPantalla();
            break;
        case 6:
            generarArchivo(listaOrdenes);
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}
