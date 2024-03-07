#!/bin/bash

### Основы разработки программного обеспечения, ИКНТ, Баранов К.П., группа 20021.
### Лабораторная работа #1.

## Подготовительные работы:
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Подготовительные работы (очистка мусора, создание директории temp и перемещение в неё).\n"
rm -rf temp # Удаляем директорию temp, если она осталась после прошлой отработки скрипта.
## P.S.: Флаг `-f`, чтобы не ругался, если она не существует, а `-r`, так как удаляем директорию и всё в ней рекурсивно.
mkdir temp -p # Создаём директорию для последующей работы.
## P.S.: Флаг `-p`, чтобы не ругался, если она уже существует.
printf "Список файлов и директорий в начале работы скрипта (ls -R --color=auto):\n"
ls -R --color=auto
cd temp # Заходим в директорию, в которой будет вестись работа.
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

printf "Задание -> используя find написать команды:\n\n"

## Задание #1.
printf "1. которая будет удалять, из домашнего каталога пользователя, все файлы к которым не было обращений за последние 100 дней:\n"
printf "1.1 Создаём 5 файлов с data access явно старше 100 дней.\n"
printf "Выполняю команду: touch -a -t 2105010000 should-be-deleted{1..5}.jpeg\n"
touch -a -t 2105010000 should-be-deleted{1..5}.jpeg
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

printf "1.2 Создаём 5 файлов с data  access младше 100 дней (они не должны быть удалены).\n"
printf "Выполняю команду: touch stay-here{1..5}.mp4\n"
touch stay-here{1..5}.mp4
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

printf "1.3 Ищем и удаляем файлы, data access которых старше 100 дней.\n"
printf "Выполняю команду: find . -type f -atime +100 -exec rm -f {} \;\n"
find . -type f -atime +100 -exec rm -f {} \;
## либо: find . -type f -atime +100 -delete
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

## Задание #2.
printf "2. которая будет удалять, из домашнего каталога пользователя, все файлы к которым не было обращений за последние 100 дней, выводя запрос удаления.\n"
printf "2.1 В этот раз создаём 3 файла с data access явно старше 100 дней.\n"
printf "Выполняю команду: touch -a -t 2105010000 should-be-deleted-with-prompt{1..3}.mp3\n"
touch -a -t 2105010000 should-be-deleted-with-prompt{1..3}.mp3
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

printf "2.2 Ищем и удаляем файлы, data access которых старше 100 дней в интерактивном режиме (с запросом на удаление).\n\n"
printf "Выполняю команду: find . -type f -atime +100 -exec rm -fi {} \;\n"
find . -type f -atime +100 -exec rm -fi {} \;
## P.S.: Флаг `-i` отвечает за интерактивное удаление.
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

## Задание #3.
printf "3. которая будет копировать в указанный каталог все файлы в формате «png», содержащиеся в домашнем каталоге пользователя.\n"
printf "3.1 Создадим png-шки.\n"
printf "Выполняю команду: touch png{1..10}.png\n"
touch png{1..10}.png
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

printf "3.2 Спрашиваем у пользователя, в какой каталог он хочет скопировать их. Считываем данные от пользователя.\n"
printf "В какой каталог скопировать png-шки?\n"
printf "Выполняю команду: read copy_directory\n"
read copy_directory
printf "3.2.1 Если директории не существует, создадим её перед выполнением следующих команд.\n"
if [ ! -d $"copy_directory" ]; then
    printf "Создаю директорию $copy_directory, так как её не существовало.\n"
    printf "Выполняю команду: mkdir $copy_directory -p\n"
    mkdir $copy_directory -p
    # Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
    printf "Нажмите любую клавишу для продолжения...\n"
    read -n 1
fi

printf "3.3 Копируем, собственно говоря.\n"
printf "Выполняю команду: find . -maxdepth 1 -name "*.png" -type f -exec cp -f {} $copy_directory/ \;\n"
find . -maxdepth 1 -name "*.png" -type f -exec cp -f {} $copy_directory/ \;
# P.S.: Флаг `-maxdepth` у find здесь, чтобы не возникало проблем при копировании в subdirs.
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

## Задание #4.
printf "4. которая будет перемещать в указанный каталог все файлы в формате «png», содержащиеся в домашнем каталоге пользователя.\n"
printf "4.1 Спрашиваем у пользователя, в какой каталог он хочет переместить png-щки. Считываем данные от пользователя.\n"
printf "В какой каталог переместить png-шки?\n"
printf "Выполняю команду: read mv_directory\n"
read mv_directory
printf "4.1.1 Если директории не существует, создадим её перед выполнением следующих команд.\n"
if [ ! -d $"mv_directory" ]; then
    printf "Создаю директорию $mv_directory, так как её не существовало.\n"
    printf "Выполняю команду: mkdir $mv_directory -p\n"
    mkdir $mv_directory -p
fi

printf "4.2 Переносим, собственно говоря.\n"
printf "Выполняю команду: find . -maxdepth 1 -name "*.png" -type f -exec mv -f {} $mv_directory/ \;\n"
find . -maxdepth 1 -name "*.png" -type f -exec mv -f {} $mv_directory/ \;
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Список файлов (ls -R --color=auto) "
ls -R --color=auto
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

## Задание #5.
printf "5. которая будет искать в домашнем каталоге пользователя файлы содержащие фразу «hello» и выводить путь к этим файлам.\n"
printf "5.1. Запишем в файлы hi.mp4 и greetings.mp3 фразу \"hello\", а остальные оставим пустыми.\n"
printf "Выполняю команды: printf \"hello world!\" >>\"hello{1,3}.mp4\"\n и printf \"You wanna play rough? Okay. Say hello to my lil friend!\" >>\"greetings.mp3\"\n"
printf "hello, world!" >>"hi.mp4"
printf "You wanna play rough? Okay. Say hello to my lil friend!" >>"greetings.mp3"

printf "5.2. Найдём файлы, содержащие фразу \"hello\" и выведем их список.\n"
printf "Выполняю команду: find . -type f -exec grep -d skip --exclude=script.sh -l "hello" --color=auto {} \;\n"
find . -type f -exec grep -d skip --exclude=script.sh -l "hello" --color=auto {} \;
# P.S. `-d skip` - чтобы пропустить директории, `--exclude=\script.sh` - чтобы пропустить содержимое скрипта.
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1

## Очистка мусора.
printf "\nОчистка мусора, оставшегося в конце выполнения лабы.\n"
# Ждём подтверждения от пользователя, чтобы приступить к следующему шагу.
printf "Нажмите любую клавишу для продолжения...\n"
read -n 1
cd ..       # Вернёмся в нашу родительскую директорию, откуда мы запускали скрипт.
rm -rf temp # Удаляем директорию temp, если она осталась после прошлой отработки скрипта.
## P.S.: Флаг `-f`, чтобы не ругался, если она не существует, а `-r`, так как удаляем директорию и всё в ней рекурсивно.
printf "Список файлов и директорий в конце работы скрипта (ls -R --color=auto) "
ls -R --color=auto
