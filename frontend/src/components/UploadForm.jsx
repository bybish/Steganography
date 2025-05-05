import React, { useState } from 'react';
import { uploadFile } from '../api';

const UploadForm = () => {
    const [selectedFile, setSelectedFile] = useState(null);
    const [savedFilename, setSavedFilename] = useState('');
    const [error, setError] = useState('');

    const handleFileChange = (e) => {
        const file = e.target.files[0];
        if (file && file.type === 'text/plain') {
            setSelectedFile(file);
            setError('');
        } else {
            setSelectedFile(null);
            setError('Выберите файл формата .txt');
        }
    };

    const handleUpload = async () => {
        if (!selectedFile) {
            setError('Файл не выбран');
            return;
        }

        try {
            const data = await uploadFile(selectedFile); // передаём только файл
            setSavedFilename(data.filename);
            setError('');
        } catch (err) {
            console.error(err);
            setError('Не удалось загрузить файл');
        }
    };


    return (
        <div className="upload-form">
            <h2>Загрузка .txt файла</h2>
            <input type="file" accept=".txt" onChange={handleFileChange} />
            <br />
            <button onClick={handleUpload} style={{ marginTop: '1rem' }}>
                Загрузить
            </button>
            {savedFilename && (
                <p>Файл успешно загружен как: <strong>{savedFilename}</strong></p>
            )}
            {error && <p style={{ color: 'red' }}>{error}</p>}
        </div>
    );
};

export default UploadForm;