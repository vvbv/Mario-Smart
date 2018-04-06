from flask import Flask, abort, request, render_template
app = Flask(__name__)
import json
import os


@app.route('/',methods=['POST','GET'])
@app.route('/index',methods=['POST','GET'])
def index():
    hidden = "hidden"
    if request.method == "POST":
        files = request.files['file']
        files.save('./entorno.txt')
        hidden = ""
    return render_template("index.html", escondido=hidden)

@app.route('/json_salida')
def json_salida():
    archivo = open('json.txt','r')
    arc = archivo.read()
    archivo.close()
    return arc


@app.route('/amplitud')
def amplitud():
    os.system("./main amplitud entorno.txt")    
    return render_template("amplitud.html")

@app.route('/costo')
def costo():
    os.system("./main costo entorno.txt")    
    return render_template("costo.html")

@app.route('/profundidad')
def profundidad():
    os.system("./main profundidad entorno.txt")    
    return render_template("profundidad.html")

@app.route('/avara')
def avara():
    os.system("./main avara entorno.txt")    
    return render_template("avara.html")

@app.route('/a_estrella')
def a_estrella():
    os.system("./main a_estrella entorno.txt")
    return render_template("a_estrella.html")

@app.route('/entorno',methods=['POST','GET'])
def entorno():
    if request.method == "POST":
        files = request.files['file']
        files.save('./entorno.txt')
        os.system("./main profundidad entorno.txt")
    
    return render_template("entorno.html")

if __name__ == '__main__':
    app.run(debug = True, host='0.0.0.0')
