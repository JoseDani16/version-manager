#ifndef TIPOS_H
#define TIPOS_H

struct nodoArchivo;
struct nodoLinea;
struct nodoVersion;
struct nodoVersionNumber;
struct nodoCambio;

typedef nodoArchivo* Archivo;
typedef nodoLinea* Linea;
typedef nodoVersion* Version;
typedef nodoVersionNumber* VersionNumber;
typedef nodoCambio* Cambio;

#endif
