import React, { useState, useEffect } from 'react';

const HelloWorld = () => {
    const [apiBaseUrl, setApiBaseUrl] = useState('');
    const [languages, setLanguages] = useState([]);
    const [language, setLanguage] = useState('');
    const [message, setMessage] = useState('');

    useEffect(() => {
        fetch('/config.json')
            .then(response => response.json())
            .then(config => {
                setApiBaseUrl(config.api_base_url);
                console.log(`API Base URL loaded: ${config.api_base_url}`);
            })
            .catch(err => console.error('Error loading config.json:', err));
    }, []);

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

    return (
        <div style={styles.container}>
            <h1 style={styles.title}>Hello World API</h1> {/* Add this line for the title */}
            <select style={styles.select} onChange={(e) => setLanguage(e.target.value)}>
                <option value="">Select a Language</option>
                {languages.map((lang, index) => (
                    <option key={index} value={lang}>{lang}</option>
                ))}
            </select>
            <button style={styles.button} onClick={fetchMessage}>Get Message</button>
            <div style={styles.messageContainer}>
                <p style={styles.message}>{message}</p>
            </div>
        </div>
    );
};

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
    title: { /* Styling for the title */
        fontSize: '28px',
        fontWeight: 'bold',
        marginBottom: '20px',
        color: '#333',
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
};

export default HelloWorld;
