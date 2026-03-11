#include "neurona.hpp"
#include <cstring>

clssNeurona::clssNeurona(const std::string& nombre) : nombreArchivo(nombre) {
    raiz = std::make_unique<vneurona>();
    despertar();
}

void clssNeurona::despertar() {
    std::ifstream in(nombreArchivo, std::ios::binary);
    if (!in) return;

    st_saber Snocion;
    unsigned long contador_registro = 1; // El primer registro es el 1

    while (in.read(reinterpret_cast<char*>(&Snocion), sizeof(st_saber))) {
        // Forzamos el modo silencioso pasando la dirección del registro
        estimular(Snocion.cadena, (long)contador_registro);
        contador_registro++;
    }
    in.close();
}


void clssNeurona::estimular(const std::string& bcadena, long lugar) {
    if (bcadena.empty()) return;
    sinapsis = bcadena;
    vneurona* actual = raiz.get();

    for (char c : bcadena) {
        int z = std::tolower(c) - 'a' + 1;
        if (z < 1 || z > 26) z = 27;

        if (!actual->axion[z]) {
            actual->axion[z] = std::make_unique<vneurona>();
        }
        actual = actual->axion[z].get();
    }

    // --- BLOQUE DE DECISIÓN CRÍTICO ---
    if (lugar > 0) {
        // Estamos en modo CARGA (despertar o inyectar)
        actual->direccion = (unsigned long)lugar;
        return; // SALIDA INMEDIATA: No imprimimos nada en consola
    }

    // Si llegamos aquí, lugar es <= 0 (Modo INTERACTIVO del main)
    if (actual->direccion > 0) {
        recordar(actual->direccion);
    }
    else {
        // Solo pregunta si realmente no existe la dirección en RAM
        std::cout << "Que es " << sinapsis << " ? ";
        std::getline(std::cin >> std::ws, respuesta);
        aprender();
        actual->direccion = contar_registros();
    }
}


void clssNeurona::recordar(unsigned long r) {
    std::ifstream in(nombreArchivo, std::ios::binary);
    if (!in) return;

    st_saber Snocion;
    in.seekg((r - 1) * sizeof(st_saber));
    in.read(reinterpret_cast<char*>(&Snocion), sizeof(st_saber));
    respuesta = Snocion.concepto;
    in.close();
}

void clssNeurona::aprender() {
    st_saber Snocion = {};
    // Limpiamos la estructura con ceros para evitar basura
    memset(&Snocion, 0, sizeof(st_saber));

    std::strncpy(Snocion.cadena, sinapsis.c_str(), NR_CADENA - 1);
    std::strncpy(Snocion.concepto, respuesta.c_str(), NR_ANCHO - 1);

    // Abrimos, escribimos y CERRAMOS inmediatamente
    std::ofstream out(nombreArchivo, std::ios::binary | std::ios::app);
    if (out.is_open()) {
        out.write(reinterpret_cast<const char*>(&Snocion), sizeof(st_saber));
        out.flush();
        out.close();
    }
}

unsigned long clssNeurona::obtener_tamano() {
    std::ifstream in(nombreArchivo, std::ios::binary | std::ios::ate);
    return in.tellg();
}


unsigned long clssNeurona::contar_registros() {
    std::ifstream in(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!in) return 0;
    return (unsigned long)in.tellg() / sizeof(st_saber);
}
