#include "controlador_entorno.hpp"

Controlador_entorno::Controlador_entorno(){}
Controlador_entorno::Controlador_entorno( Entorno entorno ){
    this->entorno = entorno;
}
Controlador_entorno::~Controlador_entorno(){}
Entorno Controlador_entorno::cargar_entorno( std::string ubicacion ){

    std::vector< std::vector< std::string > > mapa; //2D
    std::vector< std::vector< std::vector< std::string > > > mapa3D; // [No implementado]
    std::vector < std::tuple < int, int > > metas;

    std::vector < std::string > lineas;
    std::ifstream flujo_entrada( ubicacion.c_str() );
    std::string linea = "";

    while( std::getline( flujo_entrada, linea ) ){
        if( ( linea[0] != '#' ) || ( linea[0] != ' ' ) ){
            lineas.push_back( linea );
        }
    }

    flujo_entrada.close();

    std::vector < std::vector < std::string > > mapa_tmp;
    int posicion_inicial_tmp[2];

    for(int i = 0; i < lineas.size(); i++){

        std::stringstream ss_linea_mapa( lineas[i] );
        std::vector < std::string > substrings_definicion_mapa;
        std::string substring = "";

        while( ss_linea_mapa >> substring ){
            
            if( ( substring == "0" ) || ( substring == "1" ) || 
                ( substring == "3" ) || ( substring == "4" ) || 
                ( substring == "5" ) 
            ){
                substrings_definicion_mapa.push_back( substring );
                if( substring == "5" ){
                    std::tuple < int, int > meta; 
                    meta = std::make_tuple( i, substrings_definicion_mapa.size() - 1 );
                    metas.push_back( meta );
                }
            }else if( substring == "2" ){
                substrings_definicion_mapa.push_back( substring );
                posicion_inicial_tmp[0] = ( i );
                posicion_inicial_tmp[1] = ( substrings_definicion_mapa.size() - 1 );
            }
        }
        mapa_tmp.push_back( substrings_definicion_mapa );
    }

    for(int i = 0; i < mapa_tmp.size(); i++){
        mapa.push_back( mapa_tmp[i] );
    }
    
    Entorno entorno;
    entorno.set_mapa( mapa );
    entorno.set_posicion_inicial( posicion_inicial_tmp );
    entorno.set_metas( metas );

    return entorno;
}

void Controlador_entorno::pintar_entorno( Entorno entorno ){    
    this->entorno = entorno;
    this->pintar_entorno();
}

void Controlador_entorno::pintar_pos_inicial( Entorno entorno ){    
    this->entorno = entorno;
    this->pintar_pos_inicial();
}
 
std::vector < std::string > Controlador_entorno::get_informacion_entorno_pos( Entorno entorno, int pos[2], bool frontera ){
    this->entorno = entorno;
    return this->get_informacion_entorno_pos( pos, frontera );
};

std::vector<int> Controlador_entorno::get_pos_entorno_arriba( int pos_actual[2] ){
    std::vector <int> pos;
    pos.push_back( pos_actual[0] - 1);
    pos.push_back( pos_actual[1] );
    return pos;
};

std::vector<int> Controlador_entorno::get_pos_entorno_izquierda( int pos_actual[2] ){
    std::vector <int> pos;
    pos.push_back( pos_actual[0] );
    pos.push_back( pos_actual[1] - 1 );
    return pos;
};

std::vector<int> Controlador_entorno::get_pos_entorno_abajo( int pos_actual[2] ){
    std::vector <int> pos;
    pos.push_back( pos_actual[0] + 1 );
    pos.push_back( pos_actual[1] );
    return pos;
};

std::vector<int> Controlador_entorno::get_pos_entorno_derecha( int pos_actual[2] ){
    std::vector <int> pos;
    pos.push_back( pos_actual[0] );
    pos.push_back( pos_actual[1] + 1 );
    return pos;
};

std::vector < std::string > Controlador_entorno::get_informacion_entorno_pos( int pos[2], bool frontera ){

    std::vector < std::string > informacion;
    if( ( pos[0] == -1 ) || ( pos[1] == -1 ) || ( pos[0] == ( this->entorno.get_mapa().size() ) ) || ( pos[1] == ( this->entorno.get_mapa()[0].size() ) ) ){
        return informacion;
    }
    
    std::string arriba, izquierda, abajo, derecha, actual = "";
        
        if( ( ( pos[0] - 1 ) > -1 ) && ( pos[0] > -1 ) && ( pos[1] > -1 ) ){
            arriba = this->entorno.get_mapa()[ pos[0] - 1 ][ pos[1] ] ;
        }else{
            if ( frontera ){
                arriba = "F";
            }else{
                arriba = "1";
            }
        }
        
        if( ( ( pos[1] - 1 ) > -1 ) && ( pos[0] > -1 ) && ( pos[1] > -1 ) ){
            izquierda = this->entorno.get_mapa()[ pos[0] ][ pos[1] - 1 ] ;
        }else{
            if ( frontera ){
                izquierda = "F";
            }else{
                izquierda = "1";
            }
        }

        if( ( ( pos[0] + 1  ) < ( this->entorno.get_mapa().size() ) ) && ( pos[0] > -1 ) && ( pos[1] > -1 ) ){
            abajo = this->entorno.get_mapa()[ pos[0] + 1 ][ pos[1] ] ;
        }else{
            if ( frontera ){
                abajo = "F";
            }else{
                abajo = "1";
            }
        }

        if( ( ( pos[1] + 1 ) < ( this->entorno.get_mapa()[0].size() ) ) && ( pos[0] > -1 ) && ( pos[1] > -1 ) ){
            derecha = this->entorno.get_mapa()[ pos[0] ][ pos[1] + 1 ] ;
        }else{
            if ( frontera ){
                derecha = "F";
            }else{
                derecha = "1";
            }
        }

        if( ( pos[0] > -1 ) && ( pos[1] > -1 ) && ( pos[0] < ( this->entorno.get_mapa().size() ) ) && ( pos[1] < ( this->entorno.get_mapa()[0].size() ) ) ){
            actual = this->entorno.get_mapa()[ pos[0] ][ pos[1] ];
            informacion.push_back( arriba );
            informacion.push_back( izquierda );
            informacion.push_back( abajo );
            informacion.push_back( derecha );
            informacion.push_back( actual );
        }

    return informacion;
};

bool Controlador_entorno::es_meta( Entorno entorno, int pos[2] ){

    std::vector < std::tuple < int, int > > metas = entorno.get_metas();
    std::cout << metas.size() << std::endl;
    for( int x = 0; x < metas.size(); x++ ){
        std::cout << std::get<0>( metas[x] ) << "  " << std::get<1>( metas[x] ) << std::endl;
        if( ( ( int ) std::get<0>( metas[x] ) == pos[0] ) && ( ( int ) std::get<1>( metas[x] ) == pos[1] ) ){
            std::cout << std::get<0>( metas[x] ) << "  " << std::get<1>( metas[x] ) << std::endl;
            return true;
        }
    }

    return false;
};

bool Controlador_entorno::es_meta( int pos[2] ){
    return es_meta( this->entorno, pos );
};

void Controlador_entorno::pintar_pos_inicial(){    
    Entorno entorno = this->entorno;
    std::vector<int> posicion_inicial = entorno.get_posicion_inicial();
    std::cout << "Punto de partida: Fila => " << ( posicion_inicial[0] ); 
    std::cout << " :: Columna => " << posicion_inicial[1] << std::endl << std::endl;
}

void Controlador_entorno::pintar_entorno(){    
    Entorno entorno = this->entorno;
    for(int i = 0; i < entorno.get_mapa().size(); i++){
        for(int j = 0; j < entorno.get_mapa()[i].size(); j++){
            std::cout << '|' << entorno.get_mapa()[i][j];
            if( j == ( entorno.get_mapa()[i].size() - 1 ) ){
                std::cout << '|' << std::endl;;
            }
        }
    }
}