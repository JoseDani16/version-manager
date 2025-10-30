#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <string>
using namespace std;

#include "tipos.h"
#include "tiporet.h"
#include "version.h"
#include "versionnumber.h"
#include "cambios.h"
#include "linea.h"

struct nodoArchivo{
    string nombre;
    Version versiones;
};
typedef nodoArchivo* Archivo;

Archivo crearArchivo(string);
TipoRet borrarArchivo(Archivo&);

#endif