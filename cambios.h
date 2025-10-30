#ifndef CAMBIOS_H
#define CAMBIOS_H

#include <iostream>
#include <string>
using namespace std;

#include "tipos.h"
#include "tiporet.h"
#include "archivo.h"
#include "version.h"
#include "versionnumber.h"
#include "linea.h"

struct nodoCambio{
    string tipo;
    int linea;
    string contenido;
    nodoCambio*sig;
};
typedef nodoCambio* Cambio;

TipoRet registrarCambio(Version, string, string, int);
TipoRet mostrarCambios(Archivo, string);
TipoRet destruirCambios(Cambio&);



#endif