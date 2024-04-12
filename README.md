# NASM OSX

## Установка

1. Установить Docker

Homebrew:
```bash
brew install docker
```
Или  Docker Desktop:
https://www.docker.com/products/docker-desktop/

2. Склонировать репозиторий
```bash
git clone https:://github.com/d0gied/nasm-osx.git
```

3. Перейти в папку с проектом
```bash
cd nasm-osx
```

4. Загрузить образ
```bash
docker compose pull
```

## Использование

Все действия выполняются внутри контейнера. Контейнер подключает `./src` и все изменения в этой папке синхронизируются с контейнером.


### bash-скрипты:
build.sh для сборки бинарного файла из .asm кода. Принимает аргумент target (цель сборки)
```bash
sh build.sh main.asm
```

start.sh для сборки и запуска бинарного файла из .asm кода. Принимает 2 флага: в флаге -t указывается цель образа, в флаге -i указывается ввод для бинарника (опциональный флаг) 
```bash
sh start.sh -t main.asm -i "1 2 3 4"
```

### Ручная сборка:

1. Запустить образ
```bash
docker compose run -it --rm nasm-osx
```

2. Скомпилировать файл
```bash
nasm -f elf32 main.asm -o main.o
```

3. Скомпоновать файл
```bash
gcc -no-pie -w main.o macro.c -o main
```

4. Запустить файл
```bash
./main
```
