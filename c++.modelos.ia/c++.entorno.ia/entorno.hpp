#ifndef ENTORNO_HPP_
#define ENTORNO_HPP_

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include <tuple>

    class Entorno{

        private:

            std::vector < std::vector< std::string > > mapa; //2D
            std::vector < std::vector< std::vector< std::string > > > mapa3D; // [No implementado]
            int posicion_inicial[2];
            std::vector < std::tuple < int, int > > metas;

        public:
            Entorno();
            ~Entorno();
            void set_mapa( std::vector < std::vector< std::string > > mapa );
            void set_posicion_inicial( int posicion_inicial[2] );
            void set_metas( std::vector < std::tuple < int, int > > metas );
            std::vector < std::vector< std::string > > get_mapa();
            std::vector < int > get_posicion_inicial();
            std::vector < std::tuple < int, int > > get_metas();
    };

#endif