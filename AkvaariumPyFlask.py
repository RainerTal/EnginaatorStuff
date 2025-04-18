

from flask import Flask, request, jsonify
import threading
import bluetooth

app = Flask(__name__)

received_bt_data = []

@app.route('/data', methods=['POST'])

def data():
    content = request.json
    print("Received (Wifi):", content)
    return 'OK', 200

#Bluetooth Start
def bluetooth_listener():
    server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    server_sock.bind(("", bluetooth.PORT_ANY))
    server_sock.listen(1)

    port = server_sock.getsockname()[1]
    bluetooth.advertise_service(server_sock, "ESP32Server",
                                service_classes=[bluetooth.SERIAL_PORT_CLASS],
                                profiles=[bluetooth.SERIAL_PORT_PROFILE])
    print("Bluetooth listening on RFCOMM channel", port)

    while True:
        print("Waiting for BT connection...")
        client_sock, client_info = server_sock.accept()
        print("Connected to", client_info)

        try:
            while True:
                data = client_sock.recv(1024)
                if not data:
                    break
                decoded = data.decode()
                print("Received via Bluetooth:", decoded)

                # OPTIONAL: Process it like a request
                received_bt_data.append(decoded)

                # If you want to simulate a POST to your Flask route:
                # with app.test_request_context('/data', method='POST', json={'data': decoded}):
                #     data()  # call the same function as Flask would

        except Exception as e:
            print("Bluetooth error:", e)
        finally:
            client_sock.close()
#Bluetooth End

if __name__ == '__main__':
    #Start bluetooth
    bt_thread = threading.Thread(target=bluetooth_listener, daemon=True)
    bt_thread.start()
    
    app.run(host='0.0.0.0', port=5000) #Start flask app
