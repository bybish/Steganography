import React, { useState } from 'react';

function App() {
    const [inputText, setInputText] = useState('');
    const [result, setResult] = useState('');

    const handleEncode = async () => {
        try {
            const response = await fetch('/api/encode', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ text: inputText }), // оборачиваем текст в JSON
            });

            if (!response.ok) {
                throw new Error(`Ошибка ${response.status}`);
            }

            const text = await response.text();
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
        </div>
    );
}

export default App;