#include "neurona.hpp"
#include <fstream>
#include <sstream>

// Función del Inyector de Conocimiento
void inyectarConocimiento(clssNeurona& n, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cout << "[-] No se encontro enciclopedia.txt" << std::endl;
        return;
    }

    std::string linea;
    std::cout << ">>> INICIANDO TRANSFERENCIA AXONAL <<<" << std::endl;

    int contador = 0;
    while (std::getline(archivo, linea)) {
        size_t pos = linea.find('|');
        if (pos != std::string::npos) {
            n.sinapsis = linea.substr(0, pos);
            n.respuesta = linea.substr(pos + 1);

            n.aprender(); // Guarda en disco

            // Obtenemos el número de registro actual
            unsigned long reg = n.contar_registros();

            // Cargamos en los axones (RAM)
            n.estimular(n.sinapsis, (long)reg);

            contador++;
            if (contador % 10 == 0) {
                std::cout << "Cargando conceptos: " << contador << "\r" << std::flush;
            }
        }
    }
    std::cout << "\n>>> CARGA FINALIZADA: " << contador << " conceptos listos. <<<\n" << std::endl;
    archivo.close();
}

int main() {
    clssNeurona neurona("memoria.nrn");

    // 1. INTENTO DE CARGA MASIVA
    // Si creas un archivo llamado enciclopedia.txt, el programa lo leerá primero
    inyectarConocimiento(neurona, "enciclopedia.txt");

    // 2. MODO CHAT INTERACTIVO
    std::string entrada;
    std::cout << "--- PROYECTO NEURONA (Modo Consulta 2026) ---" << std::endl;
    std::cout << "Escriba una palabra para consultar o '.' para salir." << std::endl;

    while (true) {
        std::cout << "\n? ";
        std::cin >> entrada;
        if (entrada == ".") break;

        neurona.estimular(entrada, -1);
        // Si la neurona ya conoce la palabra, imprimirá la respuesta de 1024 caracteres
        std::cout << "!! " << neurona.sinapsis << " es: " << neurona.respuesta << std::endl;
    }

    return 0;
}
