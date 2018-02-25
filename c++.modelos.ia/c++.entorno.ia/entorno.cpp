#include "entorno.hpp"

Entorno::Entorno(){
    this->posicion_inicial[0] = -1;
    this->posicion_inicial[1] = -1;
};
Entorno::~Entorno(){};

void Entorno::set_mapa( std::vector< std::vector< std::string > > mapa ){
    this->mapa = mapa;
}

void Entorno::set_posicion_inicial( int posicion_inicial[2] ){
    this->posicion_inicial[0] = posicion_inicial[0];
    this->posicion_inicial[1] = posicion_inicial[1];
}

std::vector< std::vector< std::string > > Entorno::get_mapa(){
    return this->mapa;
}

std::vector<int> Entorno::get_posicion_inicial(){
    std::vector < int > pos_ini;
    pos_ini.push_back( this->posicion_inicial[0] );
    pos_ini.push_back( this->posicion_inicial[1] );
    return pos_ini;
}