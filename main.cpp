#include "main.hpp"

int main( int argc, const char* argv[] ){

    if( argc > 2 ){

        Controlador_busqueda c_general( argv[2] );
        std::vector < std::string > acciones;

        std::cout << std::endl << "Mario - Smart" << std::endl;
        std::cout << "============="<< std::endl << std::endl;

        c_general.get_controlador_entorno().pintar_pos_inicial();
        c_general.get_controlador_entorno().pintar_entorno();

        if( ( std::string ) argv[1] == "amplitud" ){
            acciones = c_general.jugar_busqueda_no_informada_amplitud( c_general.get_entorno(), c_general.get_agente() );
            c_general.escribir_trayecto( acciones );
        }else if( ( std::string ) argv[1] == "costo_uniforme" ){ 
            acciones = c_general.jugar_busqueda_no_informada_costo_uniforme( c_general.get_entorno(), c_general.get_agente() );
        }else if( ( std::string ) argv[1] == "profundidad" ){
            c_general.jugar_busqueda_no_informada_profundidad( c_general.get_entorno(), c_general.get_agente() );
        }else if( ( std::string ) argv[1] == "avara" ){
            //Heuristica: Distancia en linea recta. 
            c_general.jugar_busqueda_informada_avara( c_general.get_entorno(), c_general.get_agente() );
            
        }else if( ( std::string ) argv[1] == "a_estrella" ){

        }else{
            return -1;
        }

    }else{
        std::cout << std::endl 
                  << "  bin [ amplitud || costo_uniforme || profundidad || avara || a_estrella ] [ entorno.txt ] "
                  << std::endl << std::endl;
    }

    return 0;
};
