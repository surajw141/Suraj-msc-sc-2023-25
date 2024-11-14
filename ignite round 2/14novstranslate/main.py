import os
import json
import requests
from dotenv import load_dotenv
from flask import Flask, jsonify, render_template, request
from flask_cors import CORS

# Load environment variables
load_dotenv()
OPEN_AI_KEY = os.getenv("OPEN_AI_KEY")

# Initialize Flask app and enable CORS
app = Flask(__name__)
CORS(app)

# Function to make a request to OpenAI's API for translation
def translate_openai(inp, target):
    messages = [
        {"role": "system", "content": "You are a helpful translator. Translate the input into the target language. Supported languages are English, German, French, Italian, Spanish."},
        {"role": "user", "content": f'{{"input": "{inp}", "target": "{target}"}}'}
    ]

    headers = {
        "Content-Type": "application/json",
        "Authorization": f"Bearer {OPEN_AI_KEY}"
    }

    data = {
        "model": "gpt-3.5-turbo-0613",
        "messages": messages
    }

    url = "https://api.openai.com/v1/chat/completions"
    try:
        response = requests.post(url, headers=headers, data=json.dumps(data))
        response.raise_for_status()
        result = response.json()
        return result["choices"][0]["message"]["content"]
    except requests.exceptions.RequestException as e:
        print(f"Error during translation request: {e}")
        return "Translation error"

# Define routes for the Flask app
@app.route('/')
def hello():
    return render_template("index.html")

@app.route('/api/translate/', methods=["POST"])
def translate():
    inp = request.json.get("input")
    target = request.json.get("target")
    translated_text = translate_openai(inp, target)

    return jsonify({
        "success": True,
        "data": {
            "text": translated_text,
            "target": target
        }
    })

if __name__ == "__main__":
    app.run(debug=True, port=8001)
