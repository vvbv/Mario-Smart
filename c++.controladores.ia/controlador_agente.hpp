#ifndef CONTROLADOR_AGENTE_HPP_
#define CONTROLADOR_AGENTE_HPP_
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include "../c++.modelos.ia/c++.agente.ia/agente.cpp"
    class Controlador_agente{
        private:
            Agente agente;
        public:
            Controlador_agente();
            Controlador_agente( Agente agente );
            ~Controlador_agente();
            Agente cargar_agente( std::string ubicacion );
            void pintar_agente( Agente agente );
            void pintar_agente();
    };

#endif