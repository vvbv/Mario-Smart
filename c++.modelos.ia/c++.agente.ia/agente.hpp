#ifndef AGENTE_HPP_
#define AGENTE_HPP_

    #include <string>
    #include <map>

    class Agente{
        private:
            std::string nombre;
            std::map < int, std::map < int, std::map< int, std::map< int, std::map< int, std::map< int, std::string > > > > > > percepciones_acciones;
        public:
            Agente();
            ~Agente();
            void set_nombre(std::string nombre);
            std::string get_nombre();
            std::map < int, std::map < int, std::map< int, std::map< int, std::map< int, std::map< int, std::string > > > > > > get_percepciones();
            void adicionar_percepcion_accion( 
                std::string condicion_arriba, 
                std::string condicion_izquierda, 
                std::string condicion_abajo, 
                std::string condicion_derecha, 
                std::string condicion_objetivo, 
                std::string accion 
            );
    };

#endif