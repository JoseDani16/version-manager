#include "versionnumber.h"

using namespace std;


TipoRet verificarFormato(string numStr){
    if(numStr.empty()) return ERROR;
    for(char c : numStr){
        if((c > '9' || c < '0') && c != '.') return ERROR;
    }
    return OK;
};

VersionNumber crearVersionNumber(string numStr){
    if(verificarFormato(numStr) == ERROR) return nullptr;
    VersionNumber head = new nodoVersionNumber;
    VersionNumber current = head;
    string buffer = "";
    for(char c : numStr){
        if(c == '.'){
            if(buffer.empty()) return nullptr;
            current->number = stoi(buffer);
            buffer = "";
            current->next = new nodoVersionNumber;
            current = current->next;
            current->next = nullptr;

        } else {
            buffer += c;
        }
    }
    if(buffer.empty() || current == nullptr) return nullptr;
    current->number = stoi(buffer);
    current->next = nullptr;
    return head;
}

bool estaIncluida(VersionNumber vn1, VersionNumber vn2){
    if(vn1 == nullptr) return true;
    if(vn2 == nullptr) return false;
    if(vn1->number != vn2->number) return false;
    return estaIncluida(vn1->next, vn2->next);
};

bool mismoNivel(VersionNumber vn1, VersionNumber vn2) {
    if (vn1 == nullptr && vn2 == nullptr) return true;
    if (vn1 == nullptr || vn2 == nullptr) return false;

    if (vn1->next == nullptr && vn2->next == nullptr)
        return true;

    if (vn1->next == nullptr || vn2->next == nullptr)
        return false;

    if (vn1->number != vn2->number)
        return false;

    return mismoNivel(vn1->next, vn2->next);
}


bool sonIguales(VersionNumber vn1, VersionNumber vn2){
    if(vn1 == nullptr && vn2 == nullptr) return true;
    if(vn1 == nullptr || vn2 == nullptr) return false;
    if(vn1->number != vn2->number) return false;
    return sonIguales(vn1->next, vn2->next);
};

bool esContigua(VersionNumber vn1, VersionNumber vn2){
    if(mismoNivel(vn1, vn2)){
        while(vn1->next != nullptr && vn2->next != nullptr){
            if(vn1->number != vn2->number) return false;
            vn1 = vn1->next;
            vn2 = vn2->next;
        }
        if (vn1->next == nullptr && vn2->next == nullptr) return vn2->number - vn1->number == 1;
    }
    return false;
};

string versionNumberToString(VersionNumber vn){
    if(vn == nullptr) return "";
    string resultado = to_string(vn->number);
    vn = vn->next;
    while(vn != nullptr){
        resultado += "." + to_string(vn->number);
        vn = vn->next;
    }
    return resultado;
};

VersionNumber traerPadre(VersionNumber vn1) {
    if (vn1 == nullptr || vn1->next == nullptr)
        return nullptr;

    VersionNumber resultado = new nodoVersionNumber;
    resultado->number = vn1->number;
    resultado->next = nullptr;

    VersionNumber aux = resultado;

    while (vn1->next->next != nullptr) {
        vn1 = vn1->next;
        aux->next = new nodoVersionNumber;
        aux = aux->next;
        aux->number = vn1->number;
        aux->next = nullptr;
    }

    return resultado;
}

void restarEnN(VersionNumber vn1, VersionNumber &vn2){
    if (vn1 != nullptr){
        VersionNumber aux = vn2;
        while (vn1 != nullptr && aux != nullptr){
            vn1 = vn1->next;
            aux = aux->next;
        }
        if(aux != nullptr) aux->number--;
    }
};

TipoRet destruirVersionNumber(VersionNumber& vn){
    if(vn != nullptr) {
    destruirVersionNumber(vn->next);
    delete vn;
    vn = nullptr;
    return OK;
    }
    return ERROR;
};

VersionNumber aumentarUltimo(VersionNumber vn){
    if (vn!=nullptr){
        while (vn->next!=nullptr){
            vn=vn->next;
        }
        vn->number++;
        return vn;
    }
    return nullptr;   
}

void imprimirLista(VersionNumber l){
    while (l !=nullptr){
    cout << l->number;
    if(l->next != nullptr) cout<< ".";
     l=l->next;
    }
    cout<< endl;
}