#ifndef VERSION_H
#define VERSION_H

#include <iostream>
#include <string>
using namespace std;

#include "tipos.h"
#include "tiporet.h"
#include "archivo.h"
#include "versionnumber.h"
#include "cambios.h"
#include "linea.h"

struct nodoVersion{
    Linea linea;
    string versionStr;
    nodoVersion* subversion;
    nodoVersion* sigversion;
    Cambio cambios;
};

typedef nodoVersion * Version;

TipoRet crearVersion(Archivo &, string);
Version encontrar(Version, string);
TipoRet eliminarVersion(Archivo, string);
TipoRet mostrarVersiones(Archivo);
TipoRet versionIndependiente(Archivo, string);
TipoRet imprimirTabulado(Version v, int nivel);
TipoRet eliminarEnCadena(Version);
TipoRet reacomodarVersiones(Version v);
TipoRet sonIguales(Archivo,string, string, bool&);
TipoRet destruirVersiones(Archivo);
#endif // VERSION_H