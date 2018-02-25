#include "main.hpp"

int main( int argc, const char* argv[] ){

    std::cout << "Mario - Smart" << std::endl;
    std::cout << "============="<< std::endl << std::endl;
    Controlador_busqueda c_general( "entorno.txt" );
    c_general.get_controlador_entorno().pintar_entorno();

    return 0;
};
