from flask import Flask, abort, request, render_template 
app = Flask(__name__)
import json

@app.route('/')
@app.route('/index')
def index():
    return render_template("index.html")

@app.route('/json_salida')
def json_salida():
    archivo = open('json.txt','r')
    arc = archivo.read()
    archivo.close()
    return arc


@app.route('/amplitud')
def amplitud():
    return render_template("amplitud.html")

@app.route('/costo')
def costo():
    return render_template("costo.html")

@app.route('/profundidad')
def profundidad():
    return render_template("profundidad.html")

@app.route('/avara')
def avara():
    return render_template("avara.html")

@app.route('/a_estrella')
def a_estrella():
    return render_template("a_estrella.html")


if __name__ == '__main__':
    app.run(debug = True, host='0.0.0.0')