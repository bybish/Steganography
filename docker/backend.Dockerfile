FROM debian:bullseye

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    g++ cmake git libboost-all-dev \
    libpthread-stubs0-dev  # добавляем зависимости для pthread \

# Создаем директории
WORKDIR /build

# Копируем исходники
COPY ./backend /src

# Сборка
RUN cmake /src && make

#CMD ["./steganography-server"]
CMD ["/bin/bash"]