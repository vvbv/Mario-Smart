#include "main.hpp"

int main( int argc, const char* argv[] ){

    std::cout << "Mario - Smart" << std::endl;
    std::cout << "============="<< std::endl << std::endl;
    Controlador_busqueda c_general( "entorno.txt" );
    c_general.get_controlador_entorno().pintar_pos_inicial();
    c_general.get_controlador_entorno().pintar_entorno();

    std::cout << c_general.get_entorno().get_mapa().size() << std::endl;

    c_general.jugar_busqueda_no_informada_amplitud( c_general.get_entorno(), c_general.get_agente() );
    /*int pos[2];
    pos[0] = 7;
    pos[1] = 2;
    std::cout << c_general.get_controlador_entorno().get_informacion_entorno_pos( pos )[4];*/
    
    /*std::tuple<int, std::string, std::string> xy;
    xy = std::make_tuple(1, "xx", "yy"); 
    std::cout << std::get<1>(xy);
    int ke = -1;
    std::cout << std::to_string(ke);*/



    return 0;
};
