#include "main.hpp"

int main( int argc, const char* argv[] ){

    std::cout << "Mario - Smart" << std::endl;
    std::cout << "============="<< std::endl << std::endl;

    Controlador_busqueda c_general( "entorno.txt" );
    
    c_general.get_controlador_entorno().pintar_pos_inicial();
    c_general.get_controlador_entorno().pintar_entorno();

    std::vector < std::string > acciones = c_general.jugar_busqueda_no_informada_amplitud( c_general.get_entorno(), c_general.get_agente() );
    //c_general.jugar_busqueda_no_informada_profundidad( c_general.get_entorno(), c_general.get_agente() );
    c_general.escribir_trayecto( acciones );

    return 0;
};
