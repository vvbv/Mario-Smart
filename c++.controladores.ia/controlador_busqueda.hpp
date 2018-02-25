#ifndef CONTROLADOR_GENERAL_HPP_
#define CONTROLADOR_GENERAL_HPP_

    #include <unistd.h>
    #include "controlador_entorno.cpp"
    #include "controlador_agente.cpp"
    

    class Controlador_busqueda{
        private:
            Entorno entorno;
            Agente agente;
            Controlador_entorno c_entorno;
            Controlador_agente c_agente;
            

        public:
            Controlador_busqueda( std::string ubicacion_entorno );
            Controlador_busqueda( std::string ubicacion_entorno, std::string ubicacion_agente );
            ~Controlador_busqueda();
            Controlador_entorno get_controlador_entorno();
            Controlador_agente get_controlador_agente();
            Entorno get_entorno();
            Agente get_agente();
            void set_entorno( Entorno entorno );
            void set_agente( Agente agente );

            void jugar_busqueda_no_informada_amplitud( Entorno entorno, Agente agente );

            /* Fuera de uso */
            void jugar_agente_simple( Entorno entorno, Agente agente );
            void jugar_agente_simple();
    };

#endif