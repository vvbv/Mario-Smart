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

std::vector < std::string > Controlador_busqueda::jugar_busqueda_no_informada_amplitud( Entorno entorno, Agente agente ){

    int pos_actual[2];
    pos_actual[0] = entorno.get_posicion_inicial()[0]; 
    pos_actual[1] = entorno.get_posicion_inicial()[1]; 

    std::tuple < int, int*, std::string, std::string, int, int > ultima_tupla;
    std::vector < std::tuple < int, int*, std::string, std::string, int, int > > arbol_expansiones;

    std::vector < std::string > info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual, false );
    std::string info_casilla = info_entorno[4];

    int indice_controlador = -1;
    int pos_meta_vector = -1;
    int numero_nodos_expandidos = 0;

    auto inicio = std::chrono::system_clock::now();
    std::time_t tiempo_inicio = std::chrono::system_clock::to_time_t( inicio );
    std::cout << std::endl << "Inició: " << std::ctime(&tiempo_inicio) << std::endl;

    while( info_casilla != "5" ){

        if( indice_controlador == -1 ){
            // index, posicion, información de la casilla, operador aplicado( nodo root, operador root )
            std::tuple  < int, int*, std::string, std::string, int, int > expansion;
            int *pos_apuntada = new int[2]();

            pos_apuntada[0] = pos_actual[0];
            pos_apuntada[1] = pos_actual[1];

            expansion = std::make_tuple( 0, pos_apuntada, info_casilla, "root", 0, 0 );

            arbol_expansiones.push_back( expansion ); 
            ultima_tupla = expansion;
            indice_controlador++;
        }else{
            

            int pos_tupla_controladora[2];

            pos_tupla_controladora[0] = std::get<1>( arbol_expansiones[indice_controlador] )[0];
            pos_tupla_controladora[1] = std::get<1>( arbol_expansiones[indice_controlador] )[1];

            info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_tupla_controladora, false );
            
            info_casilla = info_entorno[4];

            if( info_casilla == "5" ){
                pos_meta_vector = arbol_expansiones.size();
            }

            numero_nodos_expandidos++;

            //std::cout << std::to_string( pos_tupla_controladora[0] ) << " <> " << std::to_string( pos_tupla_controladora[1] ) << " [" << info_entorno[4] << "]" << std::endl;
            //std::cout << "Información del entorno: A:" << info_entorno[0] << " I:" << info_entorno[1] << " X:" << info_entorno[2] << " D:" << info_entorno[3] << std::endl;
            
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

            std::vector < std::string > info_entorno_casilla_superior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_superior, false );
            std::vector < std::string > info_entorno_casilla_lateral_izquierda = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_izquierda, false );
            std::vector < std::string > info_entorno_casilla_inferior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_inferior, false );
            std::vector < std::string > info_entorno_casilla_lateral_derecha = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_derecha, false );
            
            if( !info_entorno_casilla_superior.empty() ){
                if( info_entorno_casilla_superior[4] != "1" ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_superior[0];
                    pos_apuntada[1] = pos_superior[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        arbol_expansiones.push_back( expansion );
                        ultima_tupla = expansion;
                    }
                }
            }

            if( !info_entorno_casilla_lateral_izquierda.empty() ){
                if( info_entorno_casilla_lateral_izquierda[4] != "1" ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_izquierda[0];
                    pos_apuntada[1] = pos_lateral_izquierda[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        arbol_expansiones.push_back( expansion );
                        ultima_tupla = expansion;
                    }
                }
            }
            
            if( !info_entorno_casilla_inferior.empty() ){
                if( info_entorno_casilla_inferior[4] != "1" ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_inferior[0];
                    pos_apuntada[1] = pos_inferior[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        arbol_expansiones.push_back( expansion );
                        ultima_tupla = expansion;
                    }
                }
            }
            
            if( !info_entorno_casilla_lateral_derecha.empty() ){
                if( info_entorno_casilla_lateral_derecha[4] != "1" ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_derecha[0];
                    pos_apuntada[1] = pos_lateral_derecha[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        arbol_expansiones.push_back( expansion );
                        ultima_tupla = expansion;
                    }
                }
            }

            indice_controlador++;
            
            if( info_casilla == "5" ){
                break;
            }
        }
    };    

    auto fin = std::chrono::system_clock::now();
    std::time_t tiempo_fin = std::chrono::system_clock::to_time_t( fin );
    std::cout << "Finalizó: " << std::ctime(&tiempo_fin) << std::endl;

    std::tuple  < int, int*, std::string, std::string, int, int > *tupla_regresion = &arbol_expansiones[ pos_meta_vector ];
    int *pos_regresion = std::get<1>( *tupla_regresion );
    std::string val_tupla_regresion = std::get<2>( *tupla_regresion );
    std::string accion_tupla_regresion = std::get<3>( *tupla_regresion );
    int indice_padre =  std::get<4>( *tupla_regresion );

    bool nodo_error = true;
    std::string mensaje_error = " [Nodo error]";

    std::vector < std::string > acciones;

    do{
        
        std::cout << " Pos: "
                  << "[" << pos_regresion[0] << "," << pos_regresion[1] << "]" 
                  << " Val: " << val_tupla_regresion 
                  << " Acción previa: " 
                  << accion_tupla_regresion 
                  << " Indice padre: " << indice_padre 
                  << mensaje_error << std::endl;
        tupla_regresion = &arbol_expansiones[std::get<4>( *tupla_regresion )];
                
        pos_regresion = std::get<1>( *tupla_regresion );
        val_tupla_regresion = std::get<2>( *tupla_regresion );
        accion_tupla_regresion = std::get<3>( *tupla_regresion );
        indice_padre = std::get<4>( *tupla_regresion );

        acciones.push_back( accion_tupla_regresion );

        if( nodo_error ){
            nodo_error = false;
            mensaje_error = "";
        }
       
    }while( val_tupla_regresion != "2" );

    std::cout << std::endl 
              << "Tamaño del arbol: " << arbol_expansiones.size() << std::endl;

    std::cout << "Pos de la meta en el vector: " 
              << pos_meta_vector << std::endl;

    std::cout << "Número de nodos expandidos: " 
              << numero_nodos_expandidos << std::endl;

    std::cout << "Profundidad del árbol: " 
              << std::get<5>( arbol_expansiones[arbol_expansiones.size() - 1] ) << std::endl;


    std::chrono::duration<double> duracion_algoritmo = fin - inicio;
    std::cout << "Duración del algoritmo: "
              << duracion_algoritmo.count() << "s" << std::endl;

    return acciones;
            
};

std::vector < std::string > Controlador_busqueda::jugar_busqueda_no_informada_costo_uniforme( Entorno entorno, Agente agente ){

    bool tiene_flor = false;

    std::map < std::string, int > pesos;
    pesos["0"] = 1; // Camino libre
    pesos["1"] = std::numeric_limits < int >::max(); // Muro
    pesos["2"] = 1; // Punto de partida
    pesos["3"] = 1; // Flor
    pesos["4"] = 7; // Tortuga
    pesos["5"] = 1; // Meta
    
    int pos_actual[2];
    pos_actual[0] = entorno.get_posicion_inicial()[0]; 
    pos_actual[1] = entorno.get_posicion_inicial()[1]; 

    std::tuple < int, int*, std::string, std::string, int, int, int, bool > ultima_tupla;
    std::vector < std::tuple < int, int*, std::string, std::string, int, int, int, bool > > arbol_expansiones;

    std::vector < std::string > info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual, false );
    std::string info_casilla = info_entorno[4];

    int indice_controlador = -1;
    int pos_meta_vector = -1;
    int numero_nodos_expandidos = 0;

    auto inicio = std::chrono::system_clock::now();
    std::time_t tiempo_inicio = std::chrono::system_clock::to_time_t( inicio );
    std::cout << std::endl << "Inició: " << std::ctime(&tiempo_inicio) << std::endl;

    while( info_casilla != "5" ){

        if( indice_controlador == -1 ){
            // index, posicion, información de la casilla, operador aplicado( nodo root, operador root ), ..., peso, expandido?
            std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion;
            int *pos_apuntada = new int[2]();

            pos_apuntada[0] = pos_actual[0];
            pos_apuntada[1] = pos_actual[1];

            expansion = std::make_tuple( 0, pos_apuntada, info_casilla, "root", 0, 0, pesos[ info_casilla ], false );

            arbol_expansiones.push_back( expansion ); 
            ultima_tupla = expansion;
            indice_controlador++;
        }else{
            
            int tmp_peso = std::numeric_limits< int >::max();
            
            for ( int p = 0; p < arbol_expansiones.size(); p++ ){
                if( !( std::get<7>( arbol_expansiones[ p ] ) ) && ((int) std::get<6>( arbol_expansiones[ p ]) < tmp_peso ) ){
                    tmp_peso = std::get<7>( arbol_expansiones[ p ] );
                    indice_controlador = p;
                }
            }

            ultima_tupla = arbol_expansiones[ indice_controlador ];

            int pos_tupla_controladora[2];

            pos_tupla_controladora[0] = std::get<1>( arbol_expansiones[ indice_controlador ] )[0];
            pos_tupla_controladora[1] = std::get<1>( arbol_expansiones[ indice_controlador ] )[1];

            info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_tupla_controladora, false );
            
            info_casilla = info_entorno[4];

            if( info_casilla == "5" ){
                pos_meta_vector = indice_controlador;
            }

            numero_nodos_expandidos++;

            //std::cout << std::to_string( pos_tupla_controladora[0] ) << " <> " << std::to_string( pos_tupla_controladora[1] ) << " [" << info_entorno[4] << "]" << " [ Estado: " << std::to_string( std::get<7>( ultima_tupla ) ) << " ] " << " [ Peso " << std::to_string( std::get<6>( ultima_tupla ) )  << " ] " << std::endl;
            //std::cout << "Información del entorno: A:" << info_entorno[0] << " I:" << info_entorno[1] << " X:" << info_entorno[2] << " D:" << info_entorno[3] << std::endl;
            
           
            std::get<7>( ultima_tupla ) = true;
            arbol_expansiones[ indice_controlador ] = ultima_tupla;

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

            std::vector < std::string > info_entorno_casilla_superior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_superior, false );
            std::vector < std::string > info_entorno_casilla_lateral_izquierda = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_izquierda, false );
            std::vector < std::string > info_entorno_casilla_inferior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_inferior, false );
            std::vector < std::string > info_entorno_casilla_lateral_derecha = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_derecha, false );
            
            if( !info_entorno_casilla_superior.empty() ){
                if( info_entorno_casilla_superior[4] != "1" ){
                    if( info_entorno_casilla_superior[4] == "3" ){
                        tiene_flor = true;
                        pesos["4"] = 1;
                    }
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_superior[0];
                    pos_apuntada[1] = pos_superior[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;
                    int peso_nodo = std::get<6>( ultima_tupla ) + pesos[ info_entorno_casilla_superior[4] ];

                    std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba", indice_controlador, profundidad_tupla_padre, peso_nodo, false );
                    arbol_expansiones.push_back( expansion );
                }
            }

            if( !info_entorno_casilla_lateral_izquierda.empty() ){
                if( info_entorno_casilla_lateral_izquierda[4] != "1" ){
                    if( info_entorno_casilla_lateral_izquierda[4] == "3" ){
                        tiene_flor = true;
                        pesos["4"] = 1;
                    }
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_izquierda[0];
                    pos_apuntada[1] = pos_lateral_izquierda[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;
                    int peso_nodo = std::get<6>( ultima_tupla ) + pesos[ info_entorno_casilla_lateral_izquierda[4] ];

                    std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda", indice_controlador, profundidad_tupla_padre, peso_nodo, false );
                    arbol_expansiones.push_back( expansion );
                }
            }
            
            if( !info_entorno_casilla_inferior.empty() ){
                if( info_entorno_casilla_inferior[4] != "1" ){
                    if( info_entorno_casilla_inferior[4] == "3" ){
                        tiene_flor = true;
                        pesos["4"] = 1;
                    }
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_inferior[0];
                    pos_apuntada[1] = pos_inferior[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;
                    int peso_nodo = std::get<6>( ultima_tupla ) + pesos[ info_entorno_casilla_inferior[4] ];

                    std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo", indice_controlador, profundidad_tupla_padre, peso_nodo, false );
                    arbol_expansiones.push_back( expansion );
                }
            }
            
            if( !info_entorno_casilla_lateral_derecha.empty() ){
                if( info_entorno_casilla_lateral_derecha[4] != "1" ){
                    if( info_entorno_casilla_lateral_derecha[4] == "3" ){
                        tiene_flor = true;
                        pesos["4"] = 1;
                    }
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_derecha[0];
                    pos_apuntada[1] = pos_lateral_derecha[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;
                    int peso_nodo = std::get<6>( ultima_tupla ) + pesos[ info_entorno_casilla_lateral_derecha[4] ];

                    std::tuple  < int, int*, std::string, std::string, int, int, int, bool > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha", indice_controlador, profundidad_tupla_padre, peso_nodo, false );
                    arbol_expansiones.push_back( expansion );
                }
            }
            
            if( info_casilla == "5" ){
                break;
            }
        }
    };    

    auto fin = std::chrono::system_clock::now();
    std::time_t tiempo_fin = std::chrono::system_clock::to_time_t( fin );
    std::cout << "Finalizó: " << std::ctime(&tiempo_fin) << std::endl;

    std::tuple  < int, int*, std::string, std::string, int, int, int, bool > *tupla_regresion = &arbol_expansiones[ pos_meta_vector ];
    int *pos_regresion = std::get<1>( *tupla_regresion );
    std::string val_tupla_regresion = std::get<2>( *tupla_regresion );
    std::string accion_tupla_regresion = std::get<3>( *tupla_regresion );
    int indice_padre =  std::get<4>( *tupla_regresion );
    int peso = std::get<6>( *tupla_regresion ); 

    bool nodo_error = true;
    std::string mensaje_error = " [Nodo error]";

    std::vector < std::string > acciones;

    do{
        
        std::cout << " Pos: "
                  << "[" << pos_regresion[0] << "," << pos_regresion[1] << "]" 
                  << " Val: " << val_tupla_regresion 
                  << " Acción previa: " 
                  << accion_tupla_regresion 
                  << " Indice padre: " << indice_padre 
                  << " Peso: " << peso 
                  << mensaje_error << std::endl;
        tupla_regresion = &arbol_expansiones[std::get<4>( *tupla_regresion )];
                
        pos_regresion = std::get<1>( *tupla_regresion );
        val_tupla_regresion = std::get<2>( *tupla_regresion );
        accion_tupla_regresion = std::get<3>( *tupla_regresion );
        indice_padre = std::get<4>( *tupla_regresion );
        peso = std::get<6>( *tupla_regresion );

        acciones.push_back( accion_tupla_regresion );

        if( nodo_error ){
            nodo_error = false;
            mensaje_error = "";
        }
       
    }while( val_tupla_regresion != "2" );

    std::cout << std::endl 
              << "Tamaño del arbol: " << arbol_expansiones.size() << std::endl;

    std::cout << "Pos de la meta en el vector: " 
              << pos_meta_vector << std::endl;

    std::cout << "Número de nodos expandidos: " 
              << numero_nodos_expandidos << std::endl;

    std::cout << "Profundidad del árbol: " 
              << std::get<5>( arbol_expansiones[arbol_expansiones.size() - 1] ) << std::endl;


    std::chrono::duration<double> duracion_algoritmo = fin - inicio;
    std::cout << "Duración del algoritmo: "
              << duracion_algoritmo.count() << "s" << std::endl;

    return acciones;
            
};

std::vector < std::string > Controlador_busqueda::jugar_busqueda_no_informada_profundidad( Entorno entorno, Agente agente ){
    std::vector < std::string > acciones;
    
    int pos_actual[2];
    pos_actual[0] = entorno.get_posicion_inicial()[0]; 
    pos_actual[1] = entorno.get_posicion_inicial()[1]; 

    std::tuple < int, int*, std::string, std::string, int, int > ultima_tupla;
    std::vector < std::tuple < int, int*, std::string, std::string, int, int > > arbol_expansiones;
    std::vector < std::tuple < int, int > > posiciones_visitadas;

    std::vector < std::string > info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual, true );
    std::string info_casilla = info_entorno[4];

    int indice_controlador = -1;
    int pos_meta_vector = -1;
    int numero_nodos_expandidos = 0;

    auto inicio = std::chrono::system_clock::now();
    std::time_t tiempo_inicio = std::chrono::system_clock::to_time_t( inicio );
    std::cout << std::endl << "Inició: " << std::ctime(&tiempo_inicio) << std::endl;

    while( info_casilla != "5" ){

        if( indice_controlador == -1 ){
            // index, posicion, información de la casilla, operador aplicado( nodo root, operador root )
            std::tuple  < int, int*, std::string, std::string, int, int > expansion;
            int *pos_apuntada = new int[2]();

            pos_apuntada[0] = pos_actual[0];
            pos_apuntada[1] = pos_actual[1];

            expansion = std::make_tuple( 0, pos_apuntada, info_casilla, "root", 0, 0 );

            arbol_expansiones.push_back( expansion );
            ultima_tupla = expansion;
            indice_controlador++;
        }else{

            int pos_tupla_controladora[2];

            pos_tupla_controladora[0] = std::get<1>( arbol_expansiones[0] )[0];
            pos_tupla_controladora[1] = std::get<1>( arbol_expansiones[0] )[1];

            posiciones_visitadas.push_back( std::make_tuple( pos_tupla_controladora[0], pos_tupla_controladora[1] ) );

            info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_tupla_controladora, true );
            info_casilla = info_entorno[4];

            if( info_casilla == "5" ){
                pos_meta_vector = arbol_expansiones.size();
            }

            numero_nodos_expandidos++;

            std::cout << std::to_string( pos_tupla_controladora[0] ) << " <> " << std::to_string( pos_tupla_controladora[1] ) 
                      << " Info: [" << info_entorno[4] << "] " 
                      << "Información del entorno: A:" << info_entorno[0] 
                      << " I:" << info_entorno[1] 
                      << " X:" << info_entorno[2] 
                      << " D:" << info_entorno[3] 
                      << " Tamaño del arbol: " << arbol_expansiones.size() << std::endl;
            
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

            std::vector < std::string > info_entorno_casilla_superior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_superior, true );
            std::vector < std::string > info_entorno_casilla_lateral_izquierda = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_izquierda, true );
            std::vector < std::string > info_entorno_casilla_inferior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_inferior, true );
            std::vector < std::string > info_entorno_casilla_lateral_derecha = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_derecha, true );

            if( !info_entorno_casilla_superior.empty() ){
                if( ( info_entorno_casilla_superior[4] != "1" ) && ( info_entorno_casilla_superior[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_superior[0];
                    pos_apuntada[1] = pos_superior[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                            arbol_expansiones.insert( arbol_expansiones.begin(), expansion );
                            ultima_tupla = expansion;
                        }
                    }
                }
            }

            if( !info_entorno_casilla_lateral_izquierda.empty() ){
                if( ( info_entorno_casilla_lateral_izquierda[4] != "1" ) && ( info_entorno_casilla_lateral_izquierda[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_izquierda[0];
                    pos_apuntada[1] = pos_lateral_izquierda[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                            arbol_expansiones.insert( arbol_expansiones.begin(), expansion );
                            ultima_tupla = expansion;
                        }
                    }
                }
            }

            if( !info_entorno_casilla_inferior.empty() ){
                if( ( info_entorno_casilla_inferior[4] != "1" ) && ( info_entorno_casilla_inferior[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_inferior[0];
                    pos_apuntada[1] = pos_inferior[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                            arbol_expansiones.insert( arbol_expansiones.begin(), expansion );
                            ultima_tupla = expansion;
                        }
                    }
                }
            }

            if( !info_entorno_casilla_lateral_derecha.empty() ){
                if( ( info_entorno_casilla_lateral_derecha[4] != "1" ) && ( info_entorno_casilla_lateral_derecha[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_derecha[0];
                    pos_apuntada[1] = pos_lateral_derecha[1];

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha", indice_controlador, profundidad_tupla_padre );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        if ( std::find( posiciones_visitadas.begin(), posiciones_visitadas.end(), pos_actual_visitada ) == posiciones_visitadas.end() ){
                            arbol_expansiones.insert( arbol_expansiones.begin(), expansion );
                            ultima_tupla = expansion;
                        }
                    }
                }
            }

            if( info_casilla == "5" ){
                break;
            }
        }
    };    

    auto fin = std::chrono::system_clock::now();
    std::time_t tiempo_fin = std::chrono::system_clock::to_time_t( fin );
    std::cout << "Finalizó: " << std::ctime(&tiempo_fin) << std::endl;

    std::cout << "Tamaño del arbol: " << arbol_expansiones.size() << std::endl;

    std::cout << "Número de nodos expandidos: " 
              << numero_nodos_expandidos << std::endl;

    std::chrono::duration<double> duracion_algoritmo = fin - inicio;
    std::cout << "Duración del algoritmo: "
              << duracion_algoritmo.count() << "s" << std::endl;

    return acciones;
};

std::vector < std::string > Controlador_busqueda::jugar_busqueda_informada_avara( Entorno entorno, Agente agente ){
    
    std::vector < std::string > acciones;

    int pos_actual[2];
    pos_actual[0] = entorno.get_posicion_inicial()[0]; 
    pos_actual[1] = entorno.get_posicion_inicial()[1]; 

    std::tuple < int, int*, std::string, std::string, int, int, double > ultima_tupla;
    std::vector < std::tuple < int, int*, std::string, std::string, int, int, double > > arbol_expansiones;
    std::vector < std::tuple < int, int > > posiciones_visitadas;

    std::vector < std::string > info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_actual, true );
    std::string info_casilla = info_entorno[4];

    int indice_controlador = -1;
    int pos_meta_vector = -1;
    int numero_nodos_expandidos = 0;

    auto inicio = std::chrono::system_clock::now();
    std::time_t tiempo_inicio = std::chrono::system_clock::to_time_t( inicio );
    std::cout << std::endl << "Inició: " << std::ctime(&tiempo_inicio) << std::endl;

    while( info_casilla != "5" ){

        if( indice_controlador == -1 ){
            // index, posicion, información de la casilla, operador aplicado( nodo root, operador root ), numero, profundidad, valor_heuristica 
            std::tuple  < int, int*, std::string, std::string, int, int, double > expansion;
            int *pos_apuntada = new int[2]();

            pos_apuntada[0] = pos_actual[0];
            pos_apuntada[1] = pos_actual[1];

            //Asumimos una sola meta para Avara;
            std::tuple < int, int > meta = entorno.get_metas()[0];
            int pos_meta[2];
            pos_meta[0] = (int) std::get < 0 > ( meta );
            pos_meta[1] = (int) std::get < 1 > ( meta ); 
            double valor_heuristica = sqrt( 
                                            pow( pos_meta[0] - pos_apuntada[0] ,2) + 
                                            pow( pos_meta[1] - pos_apuntada[1] ,2 ) 
                                        );

            expansion = std::make_tuple( 0, pos_apuntada, info_casilla, "root", 0, 0, valor_heuristica );

            arbol_expansiones.push_back( expansion );
            ultima_tupla = expansion;
            indice_controlador++;
        }else{

            int pos_tupla_controladora[2];

            pos_tupla_controladora[0] = std::get<1>( arbol_expansiones[0] )[0];
            pos_tupla_controladora[1] = std::get<1>( arbol_expansiones[0] )[1];

            posiciones_visitadas.push_back( std::make_tuple( pos_tupla_controladora[0], pos_tupla_controladora[1] ) );

            info_entorno = this->c_entorno.get_informacion_entorno_pos( entorno, pos_tupla_controladora, true );
            info_casilla = info_entorno[4];

            if( info_casilla == "5" ){
                pos_meta_vector = arbol_expansiones.size();
            }

            numero_nodos_expandidos++;

            std::cout << std::to_string( pos_tupla_controladora[0] ) << " <> " << std::to_string( pos_tupla_controladora[1] ) 
                      << " Info: [" << info_entorno[4] << "] " 
                      << "Información del entorno: A:" << info_entorno[0] 
                      << " I:" << info_entorno[1] 
                      << " X:" << info_entorno[2] 
                      << " D:" << info_entorno[3] 
                      << " h(n):" << std::get<6>( arbol_expansiones[ 0 ] ) 
                      << " Tamaño del arbol: " << arbol_expansiones.size() << std::endl;
            
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

            std::vector < std::string > info_entorno_casilla_superior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_superior, true );
            std::vector < std::string > info_entorno_casilla_lateral_izquierda = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_izquierda, true );
            std::vector < std::string > info_entorno_casilla_inferior = this->c_entorno.get_informacion_entorno_pos( entorno, pos_inferior, true );
            std::vector < std::string > info_entorno_casilla_lateral_derecha = this->c_entorno.get_informacion_entorno_pos( entorno, pos_lateral_derecha, true );

            std::vector < std::tuple  < int, int*, std::string, std::string, int, int, double > > tuplas_pendientes;

            if( !info_entorno_casilla_superior.empty() ){
                if( ( info_entorno_casilla_superior[4] != "1" ) && ( info_entorno_casilla_superior[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_superior[0];
                    pos_apuntada[1] = pos_superior[1];

                    //Asumimos una sola meta para Avara;
                    std::tuple < int, int > meta = entorno.get_metas()[0];
                    int pos_meta[2];
                    pos_meta[0] = (int) std::get < 0 > ( meta );
                    pos_meta[1] = (int) std::get < 1 > ( meta ); 
                    double valor_heuristica = sqrt( 
                                                    pow( pos_meta[0] - pos_apuntada[0] ,2) + 
                                                    pow( pos_meta[1] - pos_apuntada[1] ,2 ) 
                                                );

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int, double > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_superior[4], "arriba", indice_controlador, profundidad_tupla_padre, valor_heuristica );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        tuplas_pendientes.push_back( expansion );
                    }
                }
            }

            if( !info_entorno_casilla_lateral_izquierda.empty() ){
                if( ( info_entorno_casilla_lateral_izquierda[4] != "1" ) && ( info_entorno_casilla_lateral_izquierda[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_izquierda[0];
                    pos_apuntada[1] = pos_lateral_izquierda[1];

                    //Asumimos una sola meta para Avara;
                    std::tuple < int, int > meta = entorno.get_metas()[0];
                    int pos_meta[2];
                    pos_meta[0] = (int) std::get < 0 > ( meta );
                    pos_meta[1] = (int) std::get < 1 > ( meta ); 
                    double valor_heuristica = sqrt( 
                                                    pow( pos_meta[0] - pos_apuntada[0] ,2) + 
                                                    pow( pos_meta[1] - pos_apuntada[1] ,2 ) 
                                                );

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int, double > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_izquierda[4], "izquierda", indice_controlador, profundidad_tupla_padre, valor_heuristica );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        tuplas_pendientes.push_back( expansion );
                    }
                }
            }

            if( !info_entorno_casilla_inferior.empty() ){
                if( ( info_entorno_casilla_inferior[4] != "1" ) && ( info_entorno_casilla_inferior[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_inferior[0];
                    pos_apuntada[1] = pos_inferior[1];

                    //Asumimos una sola meta para Avara;
                    std::tuple < int, int > meta = entorno.get_metas()[0];
                    int pos_meta[2];
                    pos_meta[0] = (int) std::get < 0 > ( meta );
                    pos_meta[1] = (int) std::get < 1 > ( meta ); 
                    double valor_heuristica = sqrt( 
                                                    pow( pos_meta[0] - pos_apuntada[0] ,2) + 
                                                    pow( pos_meta[1] - pos_apuntada[1] ,2 ) 
                                                );

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int, double > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_inferior[4], "abajo", indice_controlador, profundidad_tupla_padre, valor_heuristica );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        tuplas_pendientes.push_back( expansion );
                    }
                }
            }

            if( !info_entorno_casilla_lateral_derecha.empty() ){
                if( ( info_entorno_casilla_lateral_derecha[4] != "1" ) && ( info_entorno_casilla_lateral_derecha[4] != "F" ) ){
                    int *pos_apuntada = new int[2]();

                    pos_apuntada[0] = pos_lateral_derecha[0];
                    pos_apuntada[1] = pos_lateral_derecha[1];

                    //Asumimos una sola meta para Avara;
                    std::tuple < int, int > meta = entorno.get_metas()[0];
                    int pos_meta[2];
                    pos_meta[0] = (int) std::get < 0 > ( meta );
                    pos_meta[1] = (int) std::get < 1 > ( meta ); 
                    double valor_heuristica = sqrt( 
                                                    pow( pos_meta[0] - pos_apuntada[0] ,2) + 
                                                    pow( pos_meta[1] - pos_apuntada[1] ,2 ) 
                                                );

                    int profundidad_tupla_padre = std::get<5>( ultima_tupla ) + 1;

                    std::tuple  < int, int*, std::string, std::string, int, int, double > expansion = std::make_tuple( 0, pos_apuntada, info_entorno_casilla_lateral_derecha[4], "derecha", indice_controlador, profundidad_tupla_padre, valor_heuristica );
                    if ( ultima_tupla != expansion ){
                        std::tuple < int, int > pos_actual_visitada = std::make_tuple( pos_apuntada[0], pos_apuntada[1] );
                        tuplas_pendientes.push_back( expansion );
                    }
                }
            }

            //ASC
            std::vector < std::tuple  < int, int*, std::string, std::string, int, int, double > > tuplas_ordenadas;

            for( int x = 0; x < tuplas_pendientes.size(); x++ ){
                tuplas_ordenadas.push_back( tuplas_pendientes[ x ] );
                for( int y = 0; y < tuplas_pendientes.size(); y++ ){
                    if( ( double ) std::get < 6 > ( tuplas_pendientes[ y ] ) < ( double ) std::get < 6 > ( tuplas_ordenadas[ x ] )  ){
                        tuplas_ordenadas.at( x ) = tuplas_pendientes[ y ];
                    }
                }
            }

           
            arbol_expansiones.erase( arbol_expansiones.begin() );

            for( int y = ( tuplas_ordenadas.size() - 1 ) ; y > -1; y-- ){
                arbol_expansiones.insert( arbol_expansiones.begin(), tuplas_ordenadas[ y ] );
                ultima_tupla = tuplas_ordenadas[ y ];
            }

            if( info_casilla == "5" ){
                break;
            }
        }
    };    

    auto fin = std::chrono::system_clock::now();
    std::time_t tiempo_fin = std::chrono::system_clock::to_time_t( fin );
    std::cout << "Finalizó: " << std::ctime(&tiempo_fin) << std::endl;

    std::cout << "Tamaño del arbol: " << arbol_expansiones.size() << std::endl;

    std::cout << "Número de nodos expandidos: " 
              << numero_nodos_expandidos << std::endl;

    std::chrono::duration<double> duracion_algoritmo = fin - inicio;
    std::cout << "Duración del algoritmo: "
              << duracion_algoritmo.count() << "s" << std::endl;

    return acciones;
};

void Controlador_busqueda::escribir_trayecto( std::vector < std::string > acciones, Entorno entorno, Agente agente ){
    
    std::string cabezera = "{\n";
    
    cabezera += "    \"punto_partida\":[ " + std::to_string( entorno.get_posicion_inicial()[0] ) + ", " + std::to_string( entorno.get_posicion_inicial()[1] ) + " ],\n";
    
    std::string movimientos = "    \"movimientos\":[\n";
    for( int x = acciones.size() - 1; x >= 0 ; x-- ){
        if( x == 0  ){
            movimientos += "        { \"accion\":\"" + acciones[x] + "\" }\n    ],";
        }else{
            movimientos += "        { \"accion\":\"" + acciones[x] + "\" },\n";
        }
    }

    std::string mapa = "\n    \"mapa\":[\n";
    for( int x = 0; x < entorno.get_mapa().size(); x++ ){
        std::string fila = "        [ ";
        for( int y = 0; y < entorno.get_mapa()[0].size(); y++ ){
            if( y == ( entorno.get_mapa()[0].size() -1 ) ){
                if( x == ( entorno.get_mapa().size() -1 ) ){
                    fila += entorno.get_mapa()[x][y] + " ]\n";
                }else{
                    fila += entorno.get_mapa()[x][y] + " ],\n";
                }
                
            }else{
                fila += entorno.get_mapa()[x][y] + ", ";
            }
        }
        
        mapa += fila;
    }
    mapa += "    ]";

    std::string pie = "\n}";

    std::string json = cabezera + movimientos + mapa + pie;

    std::ofstream archivo_json_text( "json.txt" );
    archivo_json_text << json;
    archivo_json_text.close();

    std::ofstream archivo_json_json( "json.json" );
    archivo_json_json << json;
    archivo_json_json.close();

    std::cout << "Salida almacenada en json.txt y json.json" << std::endl;
    
};

void Controlador_busqueda::escribir_trayecto( std::vector < std::string > acciones ){
    this->escribir_trayecto( acciones, this->entorno, this->agente );
};