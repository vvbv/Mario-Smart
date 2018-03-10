var datos = [];
var posicion = [];

$(document).ready(function () {


    var URL_MAPA = "/json_salida";
    $.ajax
        (
        {
            url: URL_MAPA,
            async: false,
            dataType: "text",
            success: function (data) {
                data = JSON.parse(data);
                datos = data["movimientos"];
                //console.log(datos);
                var i = 0;
                data['mapa'].forEach(function (value, index) {
                    $("#resultado").append('<div id = "row_' + i + '" class = "row"> </div>');
                    var j = 0;
                    value.forEach(function (val, index) {
                        if (val == 1) {
                            img = "<img id = '" + i + "-" + j + "' style = 'width: 100% !important' class='img' src='static/images/wall.png'></img>";
                        } else if (val == 2) {
                            posicion.push(i);
                            posicion.push(j);
                            img = "<img id = '" + i + "-" + j + "' style = 'width: 100% !important' class='img' src='static/images/mario.png'></img>";
                        } else if (val == 3) {
                            img = "<img id = '" + i + "-" + j + "' style = 'width: 100% !important' class='img' src='static/images/flor.png'></img>";
                        } else if (val == 4) {
                            img = "<img id = '" + i + "-" + j + "' style = 'width: 100% !important' class='img' src='static/images/tortuga.png'></img>";
                        } else if (val == 5) {
                            img = "<img id = '" + i + "-" + j + "' style = 'width: 100% !important' class='img' src='static/images/princesa.png'></img>";
                        } else if (val == 0) {
                            img = "<img id = '" + i + "-" + j + "' style = 'height:100 %;width: 100% !important' class='img' src='static/images/camino.png'></img>";
                        }
                        $("#row_" + i).append("<div id = 'columna' class = 'col-md-1'>" + img + " </div>");
                        j++;
                    })
                    i++;
                });

            },
            error: function (msg) {
                console.log(msg);
            }
        }
        );


    //FUNCION DE MOVIMIENTO
    $(window).on('load', function () {
        for (var x = 1; x < datos.length; x++) {
            console.log("POS:")
            console.log(posicion);
            console.log(datos[x]);
            nuevaPosicion = posicion;
            switch (datos[x].accion) {
                case "arriba":
                    nuevaPosicion[0]--;
                    break;
                case "abajo":
                    nuevaPosicion[0]++;
                    break;
                case "derecha":
                    nuevaPosicion[1]++;
                    break;
                case "izquierda":
                    nuevaPosicion[1]--;
                    break;

                default:
                    break;
            }

            console.log("Nuev:");
            console.log(nuevaPosicion);

            id_pos = "#" + posicion[0] + "-" + posicion[1];
            $(id_pos).attr('src', 'static/images/camino_recorrido.png').delay(2000);
            id_nueva = "#" + nuevaPosicion[0] + "-" + nuevaPosicion[1];
            $(id_nueva).attr('src', 'static/images/mario.png').delay(2000);
            posicion = nuevaPosicion;
   
            // window.setTimeout(function () {
            //     id_pos = "#" + posicion[0] + "-" + posicion[1];
            //     $(id_pos).attr('src', 'static/images/camino_recorrido.png');
            //     id_nueva = "#" + nuevaPosicion[0] + "-" + nuevaPosicion[1];
            //     $(id_nueva).attr('src', 'static/images/mario.png');
            //     posicion = nuevaPosicion;

            // }, 2000)
        }
    })




    // datos.forEach(function(value, key){


    //         console.log(posicion);
    //         id_pos = "#"+posicion[0]+"-"+posicion[1];
    //         $(id_pos).attr('src', 'static/images/camino_recorrido.png').delay(200);

    //         nuevaPosicion = value['llegada'];

    //         posicion = nuevaPosicion;



    // })
});

function sleep(milliseconds) {
    var start = new Date().getTime();
    for (var i = 0; i < 1e7; i++) {
        if ((new Date().getTime() - start) > milliseconds) {
            break;
        }
    }
}