#include "archivo.h"


Archivo crearArchivo(string nombre){
    Archivo nuevo = new nodoArchivo;
    nuevo->nombre = nombre;
    nuevo->versiones = nullptr;
    return nuevo;
};
TipoRet borrarArchivo(Archivo &a){
    if (a== nullptr) return ERROR;
    destruirVersiones(a);
    delete a;
    a = nullptr;
    return OK;
};