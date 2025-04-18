from flask import Flask, request, jsonify
# valgus, temp, niiskus, muld
app = Flask(__name__)

andmed = {"temp": 0, "valgus": 0, "niiskus": 0, "muld": 0}

@app.route('/data', methods=['POST'])
def data():
    content = request.json
    print("Received (Wifi):", content)
    for key in content.keys():
        if (key in {'Humidity', 'Temperature'}):
            andmed['niiskus'] = content['Humidity']
            andmed['temp'] = content['Temperature']
        elif (key == 'Lux'):
            andmed['valgus'] = content['Lux']
        elif (key == 'Soil'):
            andmed['muld'] = content['Soil']
    return 'OK', 200

@app.route('/data', methods=['GET'])
def get_data():
    return jsonify(andmed), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000) #Start flask app
