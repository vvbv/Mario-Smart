#ifndef CONTROLADOR_ENTORNO_HPP_
#define CONTROLADOR_ENTORNO_HPP_

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include "../c++.modelos.ia/c++.entorno.ia/entorno.cpp"

    class Controlador_entorno{
        private:
            Entorno entorno;
        public:
            Controlador_entorno();
            Controlador_entorno( Entorno entorno );
            ~Controlador_entorno();
            Entorno cargar_entorno( std::string ubicacion );
            void pintar_entorno( Entorno entorno );
            void pintar_entorno();
            void pintar_pos_inicial( Entorno entorno );
            void pintar_pos_inicial();
            std::vector < std::string > get_informacion_entorno_pos( Entorno entorno, int pos[2], bool frontera );
            std::vector < std::string > get_informacion_entorno_pos( int pos[2], bool frontera );
            std::vector<int> get_pos_entorno_arriba( int pos_actual[2] );
            std::vector<int> get_pos_entorno_izquierda( int pos_actual[2] );
            std::vector<int> get_pos_entorno_abajo( int pos_actual[2] );
            std::vector<int> get_pos_entorno_derecha( int pos_actual[2] );
    };

#endif