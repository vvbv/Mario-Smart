#include "main.hpp"

int main( int argc, const char* argv[] ){

    std::cout << "Mario - Smart" << std::endl;
    std::cout << "============="<< std::endl << std::endl;
    Controlador_busqueda c_general( "entorno.txt" );
    //c_general.get_controlador_entorno().pintar_pos_inicial();
    c_general.get_controlador_entorno().pintar_entorno();
    c_general.jugar_busqueda_no_informada_amplitud( c_general.get_entorno(), c_general.get_agente() );
    /*std::tuple<int, std::string, std::string> xy;
    xy = std::make_tuple(1, "xx", "yy"); 
    std::cout << std::get<1>(xy);
    int ke = -1;
    std::cout << std::to_string(ke);*/



    return 0;
};
