#include "main.hpp"

int main( int argc, const char* argv[] ){

    std::cout << "Mario - Smart" << std::endl;
    std::cout << "============="<< std::endl << std::endl;
    Controlador_busqueda c_general( "entorno.txt" );
    c_general.get_controlador_entorno().pintar_pos_inicial();
    c_general.get_controlador_entorno().pintar_entorno();

    //std::cout << c_general.get_entorno().get_mapa().size() << std::endl;

    c_general.jugar_busqueda_no_informada_amplitud( c_general.get_entorno(), c_general.get_agente() );

    
    /*std::tuple<int, std::string, std::string, int, std::uintptr_t > root;
    root = std::make_tuple(1, "r", "root", 3, std::uintptr_t( &root )); 

    std::tuple<int, std::string, std::string, int, std::uintptr_t > xy;
    xy = std::make_tuple(1, "z", "zy", 3, std::uintptr_t( &root )); 

    std::cout << "Pos: " << &xy << std::endl;

    volatile std::uintptr_t n = std::uintptr_t( &xy );
    std::cout << "N: " << n  << std::endl;

    std::tuple< int, std::string, std::string, int, std::uintptr_t  > *ll = 
                                ( std::tuple< int, std::string, std::string, int, std::uintptr_t  >* )n;
                                
    std::cout << "R: " << std::get<2>(  *( std::tuple< int, std::string, std::string, int, std::uintptr_t  >* ) std::get<4>( *ll ) ) << std::endl;
    */
    


    return 0;
};
