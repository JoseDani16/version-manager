#include "version.h"


TipoRet crearVersion(Archivo &a, string version){
    Version v = a->versiones;
    if (v==nullptr){
        if (version != "1") return ERROR;
        a->versiones = new nodoVersion;
        a->versiones->versionStr = version;
        a->versiones->sigversion = nullptr;
        a->versiones->subversion = nullptr;
        a->versiones->linea = nullptr;
        a->versiones->cambios = nullptr;
        registrarCambio(v, "Version creada", "Creacion", 0);
        return OK;
    };
    if (mismoNivel(crearVersionNumber(v->versionStr), crearVersionNumber(version))){
        while (v->sigversion != nullptr){
            v = v->sigversion;
            if (sonIguales(crearVersionNumber(v->versionStr), crearVersionNumber(version))) {
                return ERROR;
            }
        }
        if (esContigua(crearVersionNumber(v->versionStr), crearVersionNumber(version))){
            v->sigversion = new nodoVersion;
            v->sigversion->versionStr = version;
            v->sigversion->sigversion = nullptr;
            v->sigversion->subversion = nullptr;
            v->sigversion->linea = nullptr;
            v->sigversion->cambios = nullptr;

            return OK;
        }
        return ERROR;
    }
    
    VersionNumber versionVN = crearVersionNumber(version);
    VersionNumber padreVN = traerPadre(versionVN);
    
    Version padre = encontrar(a->versiones, versionNumberToString(padreVN));
    if (padre != nullptr){

        if (padre->subversion == nullptr){
            if (version!= padre->versionStr+".1") return ERROR;
            
            padre->subversion = new nodoVersion;
            padre->subversion->versionStr = version;
            padre->subversion->sigversion = nullptr;
            padre->subversion->subversion = nullptr;
            padre->subversion->linea = copiarLineas(padre->linea);
            padre->subversion->cambios = nullptr;
            destruirVersionNumber(padreVN);
            destruirVersionNumber(versionVN);
            return OK;
        }
        else{
            Version current = padre->subversion;
            while (current->sigversion != nullptr){
                current = current->sigversion;
            }
            VersionNumber currentVN = crearVersionNumber(current->versionStr);
            if (esContigua(currentVN, versionVN)){
                current->sigversion = new nodoVersion;
                current->sigversion->versionStr = version;
                current->sigversion->sigversion = nullptr;
                current->sigversion->subversion = nullptr;
                current->sigversion->linea = copiarLineas(padre->linea);
                current->sigversion->cambios = nullptr;
                destruirVersionNumber(padreVN);
                destruirVersionNumber(versionVN);
                destruirVersionNumber(currentVN);
                return OK;
            }
        }   
    }
    destruirVersionNumber(padreVN);
    destruirVersionNumber(versionVN);
    return ERROR;
};


Version encontrar(Version raiz, const string versionBuscada) {

    if (raiz == nullptr || versionBuscada.empty()) return nullptr;

    // parse una vez la versión objetivo
    VersionNumber objetivoVN = crearVersionNumber(versionBuscada);
    if (objetivoVN == nullptr) {
        return nullptr;
    }

    // 1) Intentar coincidencia por mismo nivel entre hermanos
    {
        Version actual = raiz;
        while (actual != nullptr) {
            VersionNumber actualVN = crearVersionNumber(actual->versionStr);
            if (actualVN == nullptr) {
                destruirVersionNumber(objetivoVN);
                return nullptr;
            }

            // ¿están en el mismo nivel?
            bool mismo = mismoNivel(actualVN, objetivoVN);

            if (!mismo) {
                destruirVersionNumber(actualVN);
                break; // si el primero ya no está en el mismo nivel, no tiene sentido seguir hermanos como "primer nivel objetivo"
            }

            // si están en el mismo nivel, buscamos igualdad exacta
            bool iguales = sonIguales(actualVN, objetivoVN);
            destruirVersionNumber(actualVN);

            if (iguales) {
                destruirVersionNumber(objetivoVN);
                return actual;
            }

            actual = actual->sigversion;
        }
    }

    // 2) Si no lo encontré en el mismo nivel, busco en subversiones
    {
        Version actual = raiz;
        while (actual != nullptr) {
            VersionNumber actualVN = crearVersionNumber(actual->versionStr);

            if (actualVN != nullptr && estaIncluida(actualVN, objetivoVN)) {
                destruirVersionNumber(actualVN);
                Version resultado = encontrar(actual->subversion, versionBuscada);
                destruirVersionNumber(objetivoVN);
                return resultado;
            }

            destruirVersionNumber(actualVN);
            actual = actual->sigversion;
        }
    }

    destruirVersionNumber(objetivoVN);
    return nullptr;
}

TipoRet eliminarVersion(Archivo a, string version) {
    if (a == nullptr || a->versiones == nullptr) return ERROR;

    VersionNumber vn = crearVersionNumber(version);
    VersionNumber padreVN = traerPadre(vn);   // puede ser nullptr si es raíz

    if (padreVN == nullptr) {
        Version &head = a->versiones;

        if (head != nullptr && head->versionStr == version) {
            Version eliminar = head;
            head = head->sigversion;
            eliminarEnCadena(eliminar);       
            reacomodarVersiones(head);                 
            destruirVersionNumber(vn);
            return OK;
        }

        Version cur = head;
        while (cur != nullptr && cur->sigversion != nullptr &&
               cur->sigversion->versionStr != version) {
            cur = cur->sigversion;
        }
        if (cur == nullptr || cur->sigversion == nullptr) {
            destruirVersionNumber(vn);
            return ERROR;
        }
        Version eliminar = cur->sigversion;
        cur->sigversion = eliminar->sigversion;
        eliminarEnCadena(eliminar);
        reacomodarVersiones(cur->sigversion);
        destruirVersionNumber(vn);
        return OK;
    }

    string padreStr = versionNumberToString(padreVN); 
    Version padre = encontrar(a->versiones, padreStr);
    if (padre == nullptr) {
        destruirVersionNumber(padreVN);
        destruirVersionNumber(vn);
        return ERROR;
    }
    
    if (padre->subversion == nullptr) {
        destruirVersionNumber(padreVN);
        destruirVersionNumber(vn);
        return ERROR; 
    }
    
    if (padre->subversion->versionStr == version) {
        Version eliminar = padre->subversion;
        padre->subversion = eliminar->sigversion;
        eliminarEnCadena(eliminar);
        reacomodarVersiones(padre->subversion);
        destruirVersionNumber(padreVN);
        destruirVersionNumber(vn);
        return OK;
    }
    
    Version cur = padre->subversion;
    while (cur->sigversion != nullptr && cur->sigversion->versionStr != version) {
        cur = cur->sigversion;
    }
    if (cur->sigversion == nullptr) {
        destruirVersionNumber(padreVN);
        destruirVersionNumber(vn);
        return ERROR; 
    }
    
    Version eliminar = cur->sigversion;
    cur->sigversion = eliminar->sigversion;
    eliminarEnCadena(eliminar->subversion);
    delete eliminar;
    eliminar = nullptr;
    reacomodarVersiones(cur->sigversion);
    
    destruirVersionNumber(padreVN);
    destruirVersionNumber(vn);
    return OK;
}


TipoRet eliminarEnCadena(Version v){
    if (v==nullptr) return OK;
    eliminarEnCadena(v->subversion);
    eliminarEnCadena(v->sigversion);
    destruirCambios(v->cambios);
    destruirLineas(v->linea);
    delete v;
    v = nullptr;
    return OK;
}

TipoRet reacomodarVersiones(Version v){
    if (v==nullptr) return OK;
    reacomodarVersiones(v->subversion);
    reacomodarVersiones(v->sigversion);
    VersionNumber vVN = crearVersionNumber(v->versionStr);
    restarEnN(traerPadre(vVN), vVN);
    string nuevoStr = versionNumberToString(vVN);
    v->versionStr = nuevoStr;
    destruirVersionNumber(vVN);
    return OK;
};

TipoRet imprimirTabulado(Version v, int nivel){
    if (v == nullptr) return OK;

    Version actual = v;
    while (actual != nullptr) {
        if (nivel!=0){
            for (int i = 0; i < nivel; i++) {
                cout << "│   ";
            }
            cout << (actual->sigversion == nullptr ? "└── " : "├── ");
        }
        cout << actual->versionStr ;
        if (actual->subversion!=nullptr){
            cout<< "--" << endl;
        }
        
        imprimirTabulado(actual->subversion, nivel + 1);
        actual = actual->sigversion;
    }
    return OK;
}


TipoRet mostrarVersiones(Archivo a){
    Version v = a->versiones;
    return imprimirTabulado(v, 0);
};

TipoRet versionIndependiente(Archivo a, string version){
    Version v = encontrar(a->versiones, version);
    if (v == nullptr) return ERROR;
    Version aux = a->versiones;
    if (aux != nullptr){
        while (aux->sigversion != nullptr) {
            aux = aux->sigversion;
        }
        aux->sigversion = new nodoVersion;
        aux->sigversion->cambios = nullptr;
        aux->sigversion->linea = copiarLineas(v->linea);
        aux->sigversion->sigversion = nullptr;
        aux->sigversion->subversion = nullptr;
        aux->sigversion->versionStr = versionNumberToString(aumentarUltimo(crearVersionNumber(aux->versionStr)));
    }
    


    return OK;
};

TipoRet sonIguales(Archivo a, string version1, string version2, bool& iguales) {
    Version v1 = encontrar(a->versiones, version1);
    Version v2 = encontrar(a->versiones, version2);
    if (v1== nullptr && v2==nullptr) {
        iguales = true;
        return OK;
    }
    if (v1 == nullptr || v2 == nullptr) {
        iguales = false;
        return OK;
    }
    Linea l1 = v1->linea;
    Linea l2 = v2->linea;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->contenido != l2->contenido) {
            iguales = false;
            return OK;
        }
        l1 = l1->sig;
        l2 = l2->sig;
    }
    iguales = (l1 == nullptr && l2 == nullptr);
    return OK;
}

TipoRet destruirVersiones(Archivo a){
    eliminarEnCadena(a->versiones);
    return OK;
}
