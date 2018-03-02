#include "controlador_busqueda.hpp"

Controlador_busqueda::Controlador_busqueda( std::string ubicacion_entorno ){
    this->entorno = this->c_entorno.cargar_entorno( ubicacion_entorno );
}
Controlador_busqueda::Controlador_busqueda( std::string ubicacion_entorno, std::string ubicacion_agente ){
    this->entorno = this->c_entorno.cargar_entorno( ubicacion_entorno );
    this->agente = this->c_agente.cargar_agente( ubicacion_agente );
}
Controlador_busqueda::~Controlador_busqueda(){}
Controlador_entorno Controlador_busqueda::get_controlador_entorno(){
    Controlador_entorno c_e( this->entorno );
    return c_e;
}
Controlador_agente Controlador_busqueda::get_controlador_agente(){
    Controlador_agente c_a( this->agente );
    return c_a;
}

Entorno Controlador_busqueda::get_entorno(){
    return this->entorno;
};

Agente Controlador_busqueda::get_agente(){
    return this->agente;
};

void Controlador_busqueda::set_entorno( Entorno entorno ){
    this->entorno = entorno;
};

void Controlador_busqueda::set_agente( Agente agente ){
    this->agente = agente;
};

void Controlador_busqueda::jugar_agente_simple( Entorno entorno, Agente agente ){
    this->entorno = entorno;
    this->agente = agente;
    this->jugar_agente_simple();
};

void Controlador_busqueda::jugar_agente_simple(){
    /*
    int posicion_actual[2];
    posicion_actual[0] = this->entorno.get_posicion_inicial()[0];
    posicion_actual[1] = this->entorno.get_posicion_inicial()[1];

    std::vector < std::string > informacion_pos = this->get_controlador_entorno().get_informacion_entorno_pos( posicion_actual );
    while(informacion_pos[4] != "M"){
        
        int arriba, izquierda, abajo, derecha = -1;
        if( ( informacion_pos[0] == "0" ) || ( informacion_pos[0] == "M" ) || ( informacion_pos[0] == "S" ) ){
            arriba = 0;
        }else if( ( informacion_pos[0] == "1" ) ){
            arriba = 1;
        }
        if( ( informacion_pos[1] == "0" ) || ( informacion_pos[1] == "M" ) || ( informacion_pos[1] == "S" ) ){
            izquierda = 0;
        }else if( ( informacion_pos[1] == "1" ) ){
            izquierda = 1;
        }
        if( ( informacion_pos[2] == "0" ) || ( informacion_pos[2] == "M" ) || ( informacion_pos[2] == "S" ) ){
            abajo = 0;
        }else if( ( informacion_pos[2] == "1" ) ){
            abajo = 1;
        }
        if( ( informacion_pos[3] == "0" ) || ( informacion_pos[3] == "M" ) || ( informacion_pos[3] == "S" ) ){
            derecha = 0;
        }else if( ( informacion_pos[3] == "1" ) ){
            derecha = 1;
        }
        std::string accion = this->agente.get_percepciones()[arriba][izquierda][abajo][derecha][0][0];
        if( accion == "A" ){
            posicion_actual[0] = posicion_actual[0] - 1;
            posicion_actual[1] = posicion_actual[0];
        }else if( accion == "X" ){
            posicion_actual[0] = posicion_actual[0] + 1;
            posicion_actual[1] = posicion_actual[0];
        }else if( accion == "I" ){
            posicion_actual[0] = posicion_actual[0];
            posicion_actual[1] = posicion_actual[0] - 1;
        }else if( accion == "D" ){
            posicion_actual[0] = posicion_actual[0];
            posicion_actual[1] = posicion_actual[0] + 1;
        }
        std::cout << posicion_actual[0] << " - "  << posicion_actual[1] << " =>" << accion << " Valor " << informacion_pos[4] << std::endl;
        usleep(2 * 1000);
        informacion_pos = this->get_controlador_entorno().get_informacion_entorno_pos( posicion_actual );
       
    } */

};

void Controlador_busqueda::jugar_busqueda_no_informada_amplitud( Entorno entorno, Agente agente ){

    int pos_actual[2];
    pos_actual[0] = entorno.get_posicion_inicial()[0]; 
    pos_actual[1] = entorno.get_posicion_inicial()[1]; 
    //std::cout << pos_actual[0] << " -- " << pos_actual[1] << std::endl;
    
    /*for(int i = 0; i < this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual ).size(); i++ ){
        std::cout << this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual )[i] << "  ";
    }*/

    std::tuple < int, int*, std::string, std::string > ultima_tupla;
    std::vector < std::tuple < int, int*, std::string, std::string > > arbol_expansiones;

    std::vector < std::string > info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual );
    std::string info_casilla = info_entorno[4];

    int indice_controlador = -1;

    while ( info_casilla != "5" ){
        //std::cout << "Tupla controladora: " << std::to_string( indice_controlador ) << " Arbol.size() " << arbol_expansiones.size() << std::endl;
        /*if( indice_controlador == 5 ){
            break;
        }*/

        if( indice_controlador == -1 ){
            // index, posicion, información de la casilla, operador aplicado( nodo root, operador root )
            std::tuple  <int, int*, std::string, std::string > expansion;
            int *pos_apuntada = new int[2]();

            pos_apuntada[0] = pos_actual[0];
            pos_apuntada[1] = pos_actual[1];

            expansion = std::make_tuple( 0, pos_apuntada, info_casilla, "root" );

            arbol_expansiones.push_back( expansion );
            ultima_tupla = expansion;
            indice_controlador++;
        }else{

            int pos_tupla_controladora[2];
            pos_tupla_controladora[0] = std::get<1>(arbol_expansiones[indice_controlador])[0];
            pos_tupla_controladora[1] = std::get<1>(arbol_expansiones[indice_controlador])[1];

            info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_tupla_controladora );
            info_casilla = info_entorno[4];

            std::cout << std::to_string( pos_tupla_controladora[0] ) << " <> " << std::to_string( pos_tupla_controladora[1] ) << " [" << info_entorno[4] << "]" << std::endl;
            std::cout << "Información del entorno: A:" << info_entorno[0] << " I:" << info_entorno[1] << " X:" << info_entorno[2] << " D:" << info_entorno[3] << std::endl;
            
            int pos_superior[2];
            int pos_lateral_izquierda[2];
            int pos_inferior[2];
            int pos_lateral_derecha[2];
            
            pos_superior[0] = this->c_entorno.get_pos_entorno_arriba( pos_tupla_controladora )[0];
            pos_superior[1] = this->c_entorno.get_pos_entorno_arriba( pos_tupla_controladora )[1];
            pos_lateral_izquierda[0] = this->c_entorno.get_pos_entorno_izquierda( pos_tupla_controladora )[0];
            pos_lateral_izquierda[1] = this->c_entorno.get_pos_entorno_izquierda( pos_tupla_controladora )[1];
            pos_inferior[0] = this->c_entorno.get_pos_entorno_abajo( pos_tupla_controladora )[0];
            pos_inferior[1] = this->c_entorno.get_pos_entorno_abajo( pos_tupla_controladora )[1];
            pos_lateral_derecha[0] = this->c_entorno.get_pos_entorno_derecha( pos_tupla_controladora )[0];
            pos_lateral_derecha[1] = this->c_entorno.get_pos_entorno_derecha( pos_tupla_controladora )[1];

            std::vector < std::string > info_entorno_casilla_superior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_superior );
            std::vector < std::string > info_entorno_casilla_lateral_izquierda = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_izquierda );
            std::vector < std::string > info_entorno_casilla_inferior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_inferior );
            std::vector < std::string > info_entorno_casilla_lateral_derecha = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_derecha );
            
            if( info_entorno_casilla_superior[4] != "1" ){
                std::tuple  <int, int*, std::string, std::string > expansion;
                int *pos_apuntada = new int[2]();

                pos_apuntada[0] = pos_superior[0];
                pos_apuntada[1] = pos_superior[1];

                expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba" );
                if ( ultima_tupla != expansion ){
                    arbol_expansiones.push_back( expansion );
                    ultima_tupla = expansion;
                }
            }

            if( info_entorno_casilla_lateral_izquierda[4] != "1" ){
                std::tuple  <int, int*, std::string, std::string > expansion;
                int *pos_apuntada = new int[2]();

                pos_apuntada[0] = pos_lateral_izquierda[0];
                pos_apuntada[1] = pos_lateral_izquierda[1];

                expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda" );
                if ( ultima_tupla != expansion ){
                    arbol_expansiones.push_back( expansion );
                    ultima_tupla = expansion;
                }
            }

            if( info_entorno_casilla_inferior[4] != "1" ){
                std::tuple  <int, int*, std::string, std::string > expansion;
                int *pos_apuntada = new int[2]();

                pos_apuntada[0] = pos_inferior[0];
                pos_apuntada[1] = pos_inferior[1];

                expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo" );
                if ( ultima_tupla != expansion ){
                    arbol_expansiones.push_back( expansion );
                    ultima_tupla = expansion;
                }
            }

            if( info_entorno_casilla_lateral_derecha[4] != "1" ){
                std::tuple  <int, int*, std::string, std::string > expansion;
                int *pos_apuntada = new int[2]();

                pos_apuntada[0] = pos_lateral_derecha[0];
                pos_apuntada[1] = pos_lateral_derecha[1];

                expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha" );
                if ( ultima_tupla != expansion ){
                    arbol_expansiones.push_back( expansion );
                    ultima_tupla = expansion;
                }
            }


            indice_controlador++;
        }

        
    }    

    std::cout << std::endl << "Encontrado!!" << std::endl;

};


