#ifndef LINEA_H
#define LINEA_H

#include <iostream>
#include <string>
using namespace std;

#include "tipos.h"
#include "tiporet.h"
#include "archivo.h"
#include "version.h"
#include "versionnumber.h"
#include "cambios.h"

struct nodoLinea{
    string contenido;
    nodoLinea* sig;
};


typedef nodoLinea* Linea;

TipoRet insertarLinea(Archivo, string, string, int);
TipoRet eliminarLinea(Archivo&, string, int);
TipoRet mostrarTexto(Archivo, string);

TipoRet mostrarCambios(Archivo, string);

Linea copiarLineas(Linea);
TipoRet destruirLineas(Linea&);

#endif // LINEA_H