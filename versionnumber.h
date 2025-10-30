#ifndef VERSIONNUMBER_H
#define VERSIONNUMBER_H

#include <iostream>
#include <string>
using namespace std;

#include "tipos.h"
#include "tiporet.h"
#include "archivo.h"
#include "version.h"
#include "cambios.h"
#include "linea.h"

struct nodoVersionNumber{
    int number;
    nodoVersionNumber* next;   
};

typedef nodoVersionNumber* VersionNumber;

VersionNumber crearVersionNumber(string numStr);

TipoRet verificarFormato(string numStr);

TipoRet destruirVersionNumber(VersionNumber&);

bool estaIncluida(VersionNumber, VersionNumber);

bool esContigua(VersionNumber, VersionNumber);

VersionNumber traerPadre(VersionNumber);

void restarEnN(VersionNumber, VersionNumber &);

string versionNumberToString(VersionNumber);

bool mismoNivel(VersionNumber, VersionNumber);

bool sonIguales(VersionNumber, VersionNumber);

void imprimirLista(VersionNumber);

VersionNumber aumentarUltimo(VersionNumber);

#endif // VERSIONNUMBER_H
