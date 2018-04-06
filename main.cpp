#include "main.hpp"

int main( int argc, const char* argv[] ){
    
    if( argc > 2 ){

        Controlador_busqueda c_general( argv[2] );
        std::tuple < std::vector < std::string >, int, int, double > acciones;

        std::cout << std::endl << "Mario - Smart" << std::endl;
        std::cout << "============="<< std::endl << std::endl;

        c_general.get_controlador_entorno().pintar_pos_inicial();
        c_general.get_controlador_entorno().pintar_entorno();

        bool debug_mode = false;
        if( argc == 4 ){
            if( ( std::string ) argv[3] == "debug_mode=true" ){
                debug_mode = true;
                std::cout << std::endl; 
                std::cout << "Modo debug activo, esto puede ocacionar retardos en los tiempos de ejecución de los algoritmos" << std::endl;
            }else if( ( std::string ) argv[3] == "debug_mode=false" ){
                debug_mode = false;
            }else{
                std::cout << std::endl; 
                std::cout << "Argumento '" << argv[3] << "' no válido" << std::endl << std::endl;
                std::cout << "  puede intentarlo con: 'debug_mode=true' o 'debug_mode=false'" << std::endl << std::endl;
                
                return -1;
            }
        }

        if( ( std::string ) argv[1] == "amplitud" ){
            acciones = c_general.jugar_busqueda_no_informada_amplitud( c_general.get_entorno(), c_general.get_agente(), debug_mode );
            c_general.escribir_informacion_json( acciones );
        }else if( ( std::string ) argv[1] == "costo_uniforme" ){ 
            acciones = c_general.jugar_busqueda_no_informada_costo_uniforme( c_general.get_entorno(), c_general.get_agente(), debug_mode );
            c_general.escribir_informacion_json( acciones );
        }else if( ( std::string ) argv[1] == "profundidad" ){
            acciones = c_general.jugar_busqueda_no_informada_profundidad( c_general.get_entorno(), c_general.get_agente(), debug_mode );
            c_general.escribir_informacion_json( acciones );
        }else if( ( std::string ) argv[1] == "avara" ){
            //Heuristica: Distancia en linea recta. 
            acciones = c_general.jugar_busqueda_informada_avara( c_general.get_entorno(), c_general.get_agente(), debug_mode );
            c_general.escribir_informacion_json( acciones );
        }else if( ( std::string ) argv[1] == "a_estrella" ){
            //Heuristica: Distancia en linea recta. 
            acciones = c_general.jugar_busqueda_informada_a_estrella( c_general.get_entorno(), c_general.get_agente(), debug_mode );
            c_general.escribir_informacion_json( acciones );
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
