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
});
