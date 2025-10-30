#include "linea.h"


TipoRet insertarLinea(Archivo ar, string version, string contenido, int numLinea){
    Version v = encontrar(ar->versiones, version);
    if (v == nullptr) return ERROR;
    Linea nueva = new nodoLinea;
    Linea aux = v->linea;
    nueva->contenido = contenido;
    if (aux==nullptr && numLinea == 1){
        v->linea = nueva;
        nueva->sig = nullptr;
        registrarCambio(v, contenido, "IL", numLinea);
        return OK;
    }
    for(int i = 1; i < numLinea-1 && aux != nullptr; i++){
        aux = aux->sig;
    }
    if (aux == nullptr) {
        delete nueva;
        return ERROR;
    }
    nueva->sig = aux->sig;
    aux->sig = nueva;
    registrarCambio(v, contenido, "IL", numLinea);
    return OK;
};
TipoRet eliminarLinea(Archivo& ar, string version, int numLinea){
    Version v = encontrar(ar->versiones, version);
    if (v == nullptr) return ERROR;
    Linea aux = v->linea;
    if (aux == nullptr) return ERROR;
    if (numLinea == 1){
        v->linea = aux->sig;
        delete aux;
        registrarCambio(v, "", "BL", numLinea);
        return OK;
    }
    for(int i = 1; i < numLinea-1 && aux != nullptr; i++){
        aux = aux->sig;
    }
    if (aux == nullptr || aux->sig == nullptr) return ERROR;
    Linea eliminar = aux->sig;
    aux->sig = eliminar->sig;
    delete eliminar;
    registrarCambio(v, "", "BL", numLinea);
    return OK;
};

TipoRet mostrarTexto(Archivo a, string version) {
    Version v = encontrar(a->versiones, version);
    if (v == nullptr) return ERROR;
    Linea l = v->linea;
    if (l == nullptr) return ERROR;
    cout << "---------------------------" << endl;
    cout << a->nombre << " - Version " << version << endl<< endl;
    while (l != nullptr){
        cout << l->contenido << endl;
        l = l->sig;
    }
    cout << "---------------------------" << endl;
    return OK;
}

Linea copiarLineas(Linea l){
    if (l==nullptr) return nullptr;
    Linea nuevo = new nodoLinea;
    nuevo->contenido=l->contenido;
    nuevo->sig = copiarLineas(l->sig);
    return nuevo;
}

TipoRet destruirLineas(Linea& l){
    if(l != nullptr) {
        destruirLineas(l->sig);
        delete l;
        l = nullptr;
        return OK;
    }
    return ERROR;
};