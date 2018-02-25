#include "main.hpp"

int main( int argc, const char* argv[] ){

    std::cout << "Mario - Smart" << std::endl;
    std::cout << "============="<< std::endl << std::endl;
    Controlador_general c_general( "entorno.txt", "agente_percepcion_accion.txt" );
    c_general.get_controlador_entorno().pintar_entorno();

    return 0;
};
