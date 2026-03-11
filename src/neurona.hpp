#ifndef NEURONA_HPP
#define NEURONA_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>

// Mantenemos tus constantes originales de capacidad
const int NR_CADENA = 16;
const int NR_ANCHO = 1024;

// Estructura de datos persistente (exactamente como la tenías en el archivo plano)
struct st_saber {
    unsigned long registro;
    char cadena[NR_CADENA];
    char concepto[NR_ANCHO];
    unsigned long imagen;
    unsigned long sonido;
};

// El Nodo con gestión de memoria moderna y segura
struct vneurona {
    // Usamos unique_ptr para evitar fugas de memoria y reinicios del sistema
    std::unique_ptr<vneurona> axion[28];
    unsigned long direccion = 0;

    vneurona() {
        for(int i = 0; i < 28; ++i) axion[i] = nullptr;
    }
};

class clssNeurona {
private:
    std::string nombreArchivo;
    std::unique_ptr<vneurona> raiz; // Tu puntero "alfa" evolucionado

public:
    std::string sinapsis;
    std::string respuesta;

    clssNeurona(const std::string& nombre);
    void despertar();
    void estimular(const std::string& bcadena, long lugar);
    void recordar(unsigned long r);
    void aprender();
    unsigned long obtener_tamano();
    unsigned long contar_registros();
};

#endif
