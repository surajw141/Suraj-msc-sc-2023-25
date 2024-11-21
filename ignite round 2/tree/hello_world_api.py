from flask import Flask, request, jsonify
from flask_cors import CORS
import json

app = Flask(__name__)
CORS(app)

# Load language mappings from the JSON file
with open('languages.json', 'r') as file:
    messages = json.load(file)

@app.route('/hello', methods=['GET'])
def hello():
    language = request.args.get('language')
    if language in messages:
        response = {
            "ID": "ABCD12345",  # Any unique identifier
            "msgText": messages[language]
        }
        return jsonify(response), 200
    else:
        return jsonify({"error_message": "The requested language is not supported"}), 400

# Add this endpoint to provide a list of available languages
@app.route('/languages', methods=['GET'])
def get_languages():
    return jsonify(list(messages.keys())), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
