import React, { useState } from 'react';
import { encodeText } from './api';
import UploadForm from './components/UploadForm';

function App() {
    const [inputText, setInputText] = useState('');
    const [result, setResult] = useState('');

    const handleEncode = async () => {
        try {
            const text = await encodeText(inputText);
            setResult(text);
        } catch (err) {
            console.error(err);
            setResult('Ошибка при отправке запроса');
        }
    };

    return (
        <div style={{ padding: '2rem', fontFamily: 'sans-serif' }}>
            <h1>Стеганография текста</h1>
            <textarea
                rows="6"
                cols="60"
                placeholder="Введите текст..."
                value={inputText}
                onChange={(e) => setInputText(e.target.value)}
            />
            <br />
            <button onClick={handleEncode} style={{ marginTop: '1rem' }}>
                Закодировать
            </button>
            <h3>Результат:</h3>
            <pre>{result}</pre>

            <hr />

            <UploadForm />
        </div>
    );
}

export default App;