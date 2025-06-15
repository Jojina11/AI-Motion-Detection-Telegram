from flask import Flask, send_file
import datetime

app = Flask(__name__)

@app.route('/photo')
def send_photo():
    try:
        return send_file("captured.jpg", mimetype='image/jpeg')
    except:
        return "No photo found", 404

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
