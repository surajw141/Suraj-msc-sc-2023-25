from flask import Flask, request, jsonify

from flask_cors import CORS


app = Flask(__name__)

CORS(app)  # Enable CORS


# Define the messages
messages = {
    "English": "Hello world",
    "French": "Bonjour le monde",
    "Hindi": "Namastey sansar"
}

@app.route('/hello', methods=['GET'])
def hello():
    language = request.args.get('language')
    if language in messages:
        response = {
            "ID": "ABCD12345",  # This could be any unique identifier
            "msgText": messages[language]
        }
        return jsonify(response), 200
    else:
        return jsonify({"error_message": "The requested language is not supported"}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
