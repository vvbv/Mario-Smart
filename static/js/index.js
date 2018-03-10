$(document).ready(function () {

    var URL_MAPA = "/json_salida";
    console.log(URL_MAPA);
    $.ajax
        (
        {
            url: URL_MAPA,
            dataType: "text",
            success: function (data) {
                data = JSON.parse(data);
                console.log(data);
                i = 0;
                data['mapa'].forEach(function(value, index) {
                    $("#resultado").append('<div id = "row_'+i+'" class = "row"> </div>');
                    value.forEach(function(val, index){
                        if(val == 1){
                            img = "<img style = 'width: 100px !important' class='img' src='static/images/wall.png'></img>";
                        }else if(val == 2){
                            img = "<img style = 'width: 100px !important' class='img' src='static/images/mario.png'></img>";
                        }else if(val == 3){
                            img = "<img style = 'width: 100px !important' class='img' src='static/images/flor.png'></img>";                            
                        }else if(val == 4){
                            img = "<img style = 'width: 100px !important' class='img' src='static/images/tortuga.png'></img>";                            
                        }else if(val == 5){
                            img = "<img style = 'width: 100px !important' class='img' src='static/images/princesa.png'></img>";                            
                        }else if(val == 0){
                            img = "<img style = 'height:100 %;width: 160px !important' class='img' src='static/images/camino.png'></img>";
                        }
                        $("#row_"+i).append("<div id = 'columna' class = 'col-md-3'>"+img+" </div>")
                    })
                    i++;
                    //console.log("Index: " + index + " | Value: " + value)
                  });

            },
            error: function(msg){
                console.log(msg);
            }
        }
        );
});
