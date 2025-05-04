FROM debian:bullseye

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    g++ cmake git libboost-all-dev

# Копируем исходники и собираем
WORKDIR /app
COPY . .
RUN cmake . && make

#CMD ["./steganography-server"]
CMD ["/bin/bash"]