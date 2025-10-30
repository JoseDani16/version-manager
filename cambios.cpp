#include "cambios.h"


TipoRet registrarCambio(Version v, string contenido, string tipo, int linea){
    if (v == nullptr) return ERROR;
    Cambio nuevo = new nodoCambio;
    nuevo->contenido = contenido;
    nuevo->tipo = tipo;
    nuevo->linea = linea;
    nuevo->sig = v->cambios;
    v->cambios = nuevo;
    return OK;
};

TipoRet mostrarCambios(Archivo a, string version){
    Version v = encontrar(a->versiones, version);
    if (v==nullptr) return ERROR;
    cout << "---------------------------" << endl;
    cout << a->nombre << " - Version " << version << endl<< endl;

    Cambio c = v->cambios;
    if(c == nullptr) return ERROR;
    while (c!=nullptr){
        cout << c->tipo <<"    "<< c->linea <<"    "<< c->contenido << endl;
        c = c->sig;
    }
    cout << "---------------------------" << endl;

    return OK;
};

TipoRet destruirCambios(Cambio& c){
    if(c != nullptr) {
        destruirCambios(c->sig);
        delete c;
        c = nullptr;
        return OK;
    }
    return ERROR;
};