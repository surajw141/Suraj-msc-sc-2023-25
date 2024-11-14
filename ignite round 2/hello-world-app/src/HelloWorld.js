import React, { useState } from 'react';

const HelloWorld = () => {
    const [language, setLanguage] = useState('English');
    const [message, setMessage] = useState('');
    const [messageId, setMessageId] = useState('');
    const [error, setError] = useState('');

    // Function to fetch data from API
    const fetchMessage = async () => {
        try {
            const response = await fetch(`http://192.168.6.5:5000/hello?language=${language}`);
            const data = await response.json();
            
            if (data.msgText) {
                setMessage(data.msgText);
                setMessageId(data.ID);
                setError('');
            } else {
                setError(data.error_message);
                setMessage('');
                setMessageId('');
            }
        } catch (err) {
            setError("Error fetching the message.");
            setMessage('');
            setMessageId('');
            console.error("Error:", err);
        }
    };

    return (
        <div style={styles.container}>
            <h1>Hello World API</h1>
            <div>
                <label style={styles.label} htmlFor="language">Choose a language:</label>
                <select 
                    id="language" 
                    value={language} 
                    onChange={(e) => setLanguage(e.target.value)} 
                    style={styles.select}
                >
                    <option value="English">English</option>
                    <option value="French">French</option>
                    <option value="Hindi">Hindi</option>
                </select>
                <button onClick={fetchMessage} style={styles.button}>Get Message</button>
            </div>

            <div style={styles.messageContainer}>
                {error && <p style={styles.error}>{error}</p>}
                {message && <p style={styles.message}>{message}</p>}
                {messageId && <p style={styles.messageId}>Message ID: {messageId}</p>}
            </div>
        </div>
    );
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
    messageId: {
        fontSize: '16px',
        color: '#555',
    },
    error: {
        color: 'red',
        fontWeight: 'bold',
    }
};

export default HelloWorld;
