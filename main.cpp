#include <iostream>
#include <string>
#include <limits>
#include "archivo.h"
#include "linea.h"
#include "cambios.h"
#include "version.h"

using namespace std;


void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


int leerInt(const string& prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente de nuevo.\n";
    }
}


string leerLinea(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}


void menuArchivos(Archivo& archivoActual) {
    int opcion = -1;
    while (opcion != 0) {
        limpiarPantalla();
        cout << "===== MENU ARCHIVOS =====\n";
        cout << "Archivo actual: " << (archivoActual != nullptr ? archivoActual->nombre : "(ninguno)") << "\n\n";
        cout << "1) Crear archivo nuevo\n";
        cout << "2) Borrar archivo actual\n";
        cout << "3) Mostrar arbol de versiones\n";
        cout << "0) Volver\n\n";

        opcion = leerInt("Opcion: ");

        switch (opcion) {
        case 1: {
            if (archivoActual!=nullptr) {
                cout<< "Precaucion: Se eliminara el archivo actual.\n";
                cout<< "Presione 1 para confirmar o cualquier otra cosa para cancelar: ";
                int confirmacion;
                cin >> confirmacion;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (confirmacion != 1) {
                    cout << "Operacion cancelada.\n";
                    pausar();
                    break;
                }

                borrarArchivo(archivoActual);
            }
            string nombre = leerLinea("Nombre del archivo: ");
            archivoActual = crearArchivo(nombre);
            cout << "Archivo creado.\n";
            pausar();
            break;
        }
        case 2: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                borrarArchivo(archivoActual);
                cout << "Archivo eliminado.\n";
            }
            pausar();
            break;
        }
        case 3: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                mostrarVersiones(archivoActual);
            }
            pausar();
            break;
        }
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
            pausar();
        }
    }
}

void menuVersiones(Archivo& archivoActual) {
    int opcion = -1;
    while (opcion != 0) {
        limpiarPantalla();
        cout << "===== MENU VERSIONES =====\n";
        cout << "Archivo actual: " << (archivoActual ? archivoActual->nombre : "(ninguno)") << "\n\n";
        cout << "1) Crear version\n";
        cout << "2) Borrar version\n";
        cout << "3) Mostrar versiones\n";
        cout << "4) Version independiente?\n";
        cout << "0) Volver\n\n";

        opcion = leerInt("Opcion: ");

        switch (opcion) {
        case 1: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string ver = leerLinea("Ingrese numero de version (ej 1.2.3): ");
                TipoRet r = crearVersion(archivoActual, ver);
                cout << (r == OK ? "OK" : "ERROR") << "\n";
            }
            pausar();
            break;
        }
        case 2: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string ver = leerLinea("Ingrese version a borrar: ");
                TipoRet r = eliminarVersion(archivoActual, ver);
                cout << (r == OK ? "OK" : "ERROR") << "\n";
            }
            pausar();
            break;
        }
        case 3: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                mostrarVersiones(archivoActual);
            }
            pausar();
            break;
        }
        case 4: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string ver = leerLinea("Ingrese version: ");
                TipoRet r = versionIndependiente(archivoActual, ver);
                cout << (r == OK ? "Es independiente (OK)" : "No es independiente / ERROR") << "\n";
            }
            pausar();
            break;
        }
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
            pausar();
        }
    }
}

void menuContenido(Archivo& archivoActual) {
    int opcion = -1;
    while (opcion != 0) {
        limpiarPantalla();
        cout << "===== MENU CONTENIDO =====\n";
        cout << "Archivo actual: " << (archivoActual ? archivoActual->nombre : "(ninguno)") << "\n\n";
        cout << "1) Insertar linea en una version\n";
        cout << "2) Borrar linea de una version\n";
        cout << "3) Mostrar texto de una version\n";
        cout << "4) Mostrar cambios entre versiones\n";
        cout << "5) Son iguales dos versiones?\n";
        cout << "0) Volver\n\n";

        opcion = leerInt("Opcion: ");

        switch (opcion) {
        case 1: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string ver   = leerLinea("Version destino: ");
                string texto = leerLinea("Contenido de la linea: ");
                int num      = leerInt("Numero de linea: ");
                TipoRet r = insertarLinea(archivoActual, ver, texto, num);
                cout << (r == OK ? "OK" : "ERROR") << "\n";
            }
            pausar();
            break;
        }
        case 2: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string ver = leerLinea("Version destino: ");
                int num    = leerInt("Numero de linea a eliminar: ");
                TipoRet r  = eliminarLinea(archivoActual, ver, num);
                cout << (r == OK ? "OK" : "ERROR") << "\n";
            }
            pausar();
            break;
        }
        case 3: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string ver = leerLinea("Version a mostrar: ");
                TipoRet r = mostrarTexto(archivoActual, ver);
                cout << (r == OK ? "" : "ERROR mostrando texto") << "\n";
            }
            pausar();
            break;
        }
        case 4: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string v1 = leerLinea("Version base: ");
                TipoRet r = mostrarCambios(archivoActual, v1);
                cout << (r == OK ? "" : "ERROR mostrando cambios") << "\n";
            }
            pausar();
            break;
        }
        case 5: {
            if (!archivoActual) {
                cout << "No hay archivo cargado.\n";
            } else {
                string v1  = leerLinea("Version 1: ");
                string v2  = leerLinea("Version 2: ");
                bool igualesOut = false;
                TipoRet r = sonIguales(archivoActual, v1, v2, igualesOut);
                if (r == OK) {
                    cout << (igualesOut ? "Son iguales.\n" : "Son distintas.\n");
                } else {
                    cout << "ERROR comparando.\n";
                }
            }
            pausar();
            break;
        }
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
            pausar();
        }
    }
}


int main() {
    Archivo archivoActual = nullptr;

    int opcion = -1;
    while (opcion != 0) {
        limpiarPantalla();
        cout << "===== MENU PRINCIPAL =====\n";
        cout << "Archivo actual: " 
             << (archivoActual ? archivoActual->nombre : "(ninguno)") 
             << "\n\n";
        cout << "1) Gestion de archivos\n";
        cout << "2) Gestion de versiones\n";
        cout << "3) Gestion de contenido\n";
        cout << "0) Salir\n\n";

        opcion = leerInt("Opcion: ");

        switch (opcion) {
        case 1:
            menuArchivos(archivoActual);
            break;
        case 2:
            menuVersiones(archivoActual);
            break;
        case 3:
            menuContenido(archivoActual);
            break;
        case 0:
            limpiarPantalla();
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
            pausar();
        }
    }
    borrarArchivo(archivoActual);
    return 0;
}