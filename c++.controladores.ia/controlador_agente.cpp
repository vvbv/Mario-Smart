#include "controlador_agente.hpp"

Controlador_agente::Controlador_agente(){}
Controlador_agente::Controlador_agente( Agente agente ){
    this->agente = agente;
}
Controlador_agente::~Controlador_agente(){}
Agente Controlador_agente::cargar_agente( std::string ubicacion ){

    Agente agente;

    std::vector < std::string > lineas;
    std::ifstream flujo_entrada( ubicacion.c_str() );
    std::string linea = "";

    while( std::getline( flujo_entrada, linea ) ){
        if( ( linea[0] == 'N' ) || ( linea[0] == 'P' ) ){
            lineas.push_back( linea );
        }
    }

    flujo_entrada.close();

    for(int i = 0; i < lineas.size(); i++){

        std::stringstream ss_linea( lineas[i] );
        std::vector < std::string > substrings_definicion_agente;
        std::string substring = "";

        bool bandera_nombre = false;
        bool bandera_percepcion = false;

        std::vector < std::string > percepciones;

        while( ss_linea >> substring ){
            if( substring.length() > 0 ){
                if( substring[0] == 'N' ){
                    bandera_nombre = true;
                }else if( bandera_nombre ){
                    agente.set_nombre( substring );
                    bandera_nombre = false;
                }else if( substring[0] == 'P' ){
                    bandera_percepcion = true;
                }else if( bandera_percepcion ){
                    percepciones.push_back( substring );
                }
            }
        }

        if( percepciones.size() == 6 ){
            agente.adicionar_percepcion_accion(
                percepciones[0],
                percepciones[1],
                percepciones[2],
                percepciones[3],
                percepciones[4],
                percepciones[5]
            );
        }
    }
    
    return agente;
}

void Controlador_agente::pintar_agente( Agente agente ){    
    this->agente = agente;
    this->pintar_agente();
}

void Controlador_agente::pintar_agente(){    
    Agente agente = this->agente;
    std::cout << agente.get_nombre() << std::endl;
}