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
                            img = "<img id = '" + i + "-" + j + "' style = 'height: 100% !important; width: 100% !important' class='img' src=''></img>";
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
});

$('#jugar_amplitud').click(function(){
    movimiento(datos, posicion)
});

function sleep(milliseconds) {
    var start = new Date().getTime();
    for (var i = 0; i < 1e7; i++) {
        if ((new Date().getTime() - start) > milliseconds) {
            break;
        }
    }
}

//FUNCION DE MOVIMIENTO
function movimiento(datos_, posicion_inicial) {

    console.log( datos_ );

    var id_pos;
    var nuevaPosicion;
    var id_nueva;

    for (var x = 0; x < datos_.length; x++) {

        var mov = datos_[x];
        
        console.log( "POS:" + posicion_inicial )
        console.log( mov );

        nuevaPosicion = posicion_inicial;

        switch ( mov.accion ) {
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

        console.log("Nuev: " + nuevaPosicion);
        console.log( "--" );

        id_pos = "#" + posicion_inicial[0] + "-" + posicion_inicial[1];
        id_nueva = "#" + nuevaPosicion[0] + "-" + nuevaPosicion[1];

        posicion_inicial = nuevaPosicion;
        $(id_nueva).css('background-color','green');
    }
}

