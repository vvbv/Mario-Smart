var datos = [];
var posicion = [];
var iterador = 0;
var llego = false;

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
                console.log(data);
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
                            img = "<img id = '" + i + "-" + j + "' style = 'height: 100% !important; width: 100% !important' class='img' src='static/images/mario.png'></img>";
                        } else if (val == 3) {
                            img = "<img id = '" + i + "-" + j + "' style = 'height: 100% !important; width: 100% !important' class='img' src='static/images/flor.png'></img>";
                        } else if (val == 4) {
                            img = "<img id = '" + i + "-" + j + "' style = 'height: 100% !important; width: 100% !important' class='img' src='static/images/tortuga.png'></img>";
                        } else if (val == 5) {
                            
                            img = "<img id = '" + i + "-" + j + "' style = 'height: 100% !important; width: 100% !important' class='img' src='static/images/princesa.png'></img>";
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
    iterador = 0;
    renderLoop();
});


function renderLoop() {
    if(!llego){
        movimiento();
        setTimeout(renderLoop, 500);    
    }
}


//FUNCION DE MOVIMIENTO

function movimiento() {

    var mov = datos[iterador];
    var nuevaPosicion = posicion;
    var id_pos;
    var id_nueva;

    if(iterador == datos.length -1){
        llego = true;
        console.log("LLEGO :3");
    }
    id_pos = "#" + posicion[0] + "-" + posicion[1];
    $(id_pos).attr('src','static/images/camino_recorrido.png');


    switch (mov.accion) {
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
    
    iterador++;

    id_nueva = "#" + nuevaPosicion[0] + "-" + nuevaPosicion[1];
    posicion = nuevaPosicion;
    $(id_nueva).attr('src','static/images/mario.png');

}