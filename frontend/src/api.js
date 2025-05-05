// Отправка текста на кодирование
export async function encodeText(text) {
    const response = await fetch('/api/encode', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ text }),
    });

    if (!response.ok) {
        throw new Error(`Ошибка ${response.status}`);
    }

    return await response.text();
}

// Загрузка файла на сервер
export async function uploadFile(file) {
    const formData = new FormData();
    formData.append('file', file);

    const response = await fetch('/api/upload', {
        method: 'POST',
        body: formData,
    });

    if (!response.ok) {
        throw new Error(`Ошибка при загрузке: ${response.status}`);
    }

    return await response.json(); // должен быть JSON с filename
}

// Скачивание файла по хешу
export async function downloadFile(hash) {
    const response = await fetch(`/api/download/${hash}`);

    if (!response.ok) {
        throw new Error(`Файл не найден: ${response.status}`);
    }

    const blob = await response.blob();
    const url = window.URL.createObjectURL(blob);
    const link = document.createElement('a');
    link.href = url;
    link.download = `${hash}.txt`;
    link.click();
    window.URL.revokeObjectURL(url);
}