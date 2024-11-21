import React, { useState, useEffect } from 'react';

const HelloWorld = () => {
    const [apiBaseUrl, setApiBaseUrl] = useState('');
    const [languages, setLanguages] = useState([]);
    const [language, setLanguage] = useState('');
    const [message, setMessage] = useState('');

    // Fetch the API base URL from config.json
    useEffect(() => {
        fetch('/config.json')
            .then(response => response.json())
            .then(config => {
                setApiBaseUrl(config.api_base_url);
                console.log(`API Base URL loaded: ${config.api_base_url}`);
            })
            .catch(err => console.error('Error loading config.json:', err));
    }, []);

    // Fetch the available languages
    useEffect(() => {
        if (apiBaseUrl) {
            fetch(`${apiBaseUrl}/languages`)
                .then(response => response.json())
                .then(data => setLanguages(data))
                .catch(err => console.error('Error fetching languages:', err));
        }
    }, [apiBaseUrl]);

    const fetchMessage = async () => {
        try {
            const response = await fetch(`${apiBaseUrl}/hello?language=${language}`);
            const data = await response.json();
            setMessage(data.msgText || data.error_message);
        } catch (err) {
            setMessage('Error fetching the message.');
            console.error('Error:', err);
        }
    };

    // Basic styling
    const styles = {
        container: {
            fontFamily: 'Arial, sans-serif',
            textAlign: 'center',
            marginTop: '50px',
            maxWidth: '600px',
            margin: '0 auto',
            padding: '20px',
            border: '1px solid #ccc',
            borderRadius: '8px',
            boxShadow: '0 4px 8px rgba(0,0,0,0.1)',
        },
        label: {
            fontSize: '16px',
            marginRight: '10px',
        },
        select: {
            fontSize: '16px',
            padding: '8px',
            marginRight: '10px',
        },
        button: {
            fontSize: '16px',
            padding: '8px',
        },
        messageContainer: {
            marginTop: '30px',
            padding: '15px',
            fontSize: '18px',
            color: '#333',
            backgroundColor: '#f9f9f9',
            borderRadius: '6px',
            boxShadow: '0 2px 4px rgba(0,0,0,0.1)',
        },
        message: {
            fontWeight: 'bold',
            fontSize: '24px',
            color: '#2c3e50',
        },
        error: {
            color: 'red',
            fontWeight: 'bold',
        },
    };

    return (
        <div style={styles.container}>
            <label style={styles.label}>Select a Language:</label>
            <select style={styles.select} onChange={(e) => setLanguage(e.target.value)}>
                {languages.map((lang, index) => (
                    <option key={index} value={lang}>{lang}</option>
                ))}
            </select>
            <button style={styles.button} onClick={fetchMessage}>Get Message</button>
            {message && (
                <div style={styles.messageContainer}>
                    <p style={styles.message}>{message}</p>
                </div>
            )}
        </div>
    );
};

export default HelloWorld;
