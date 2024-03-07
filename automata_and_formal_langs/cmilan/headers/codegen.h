#ifndef CMILAN_CODEGEN_H
#define CMILAN_CODEGEN_H

#include <vector>
#include <iostream>

using namespace std;

// Инструкции виртуальной машины Милана

enum Instruction {
    NOP,       // отсутствие операции
    STOP,      // остановка машины, завершение работы программы
    LOAD,      // LOAD addr - загрузка слова данных в стек из памяти по адресу addr
    STORE,     // STORE addr - запись слова данных с вершины стека в память по адресу addr
    BLOAD,     // BLOAD addr - загрузка слова данных в стек из памяти по адресу addr + значение на вершине стека
    BSTORE,    // BSTORE addr - запись слова данных по адресу addr + значение на вершине стека
    PUSH,      // PUSH n - загрузка в стек константы n
    POP,       // удаление слова с вершины стека
    DUP,       // копирование слова на вершине стека
    ADD,       // сложение двух слов на вершине стека и запись результата вместо них
    SUB,       // вычитание двух слов на вершине стека и запись результата вместо них
    MULT,      // умножение двух слов на вершине стека и запись результата вместо них
    DIV,       // деление двух слов на вершине стека и запись результата вместо них
    INVERT,    // изменение знака слова на вершине стека
    COMPARE,   // COMPARE cmp - сравнение двух слов на вершине стека с помощью операции сравнения с кодом cmp
    JUMP,      // JUMP addr - безусловный переход по адресу addr
    JUMP_YES,  // JUMP_YES addr - переход по адресу addr, если на вершине стека значение 1
    JUMP_NO,   // JUMP_NO addr - переход по адресу addr, если на вершине стека значение 0
    INPUT,     // чтение целого числа со стандартного ввода и загрузка его в стек
    PRINT      // печать на стандартный вывод числа с вершины стека
};

// Класс Command представляет машинные инструкции.

class Command {
public:
    // Конструктор для инструкций без аргументов
    Command(Instruction instruction)
        : instruction_(instruction), arg_(0) {}

    // Конструктор для инструкций с одним аргументом
    Command(Instruction instruction, int arg)
        : instruction_(instruction), arg_(arg) {}

    // Печать инструкции
    //     int address - адрес инструкции
    //     ostream& os - поток вывода, куда будет напечатана инструкция
    void print(int address, ostream& os);

private:
    Instruction instruction_;  // Код инструкции
    int arg_;                  // Аргумент инструкции
};

// Кодогенератор.
// Назначение кодогенератора:
// - Формировать программу для виртуальной машины Милана
// - Отслеживать адрес последней инструкции
// - Буферизовать программу и печатать ее в указанный поток вывода

class CodeGen {
public:
    explicit CodeGen(ostream& output)
        : output_(output) {
    }

    // Добавление инструкции без аргументов в конец программы
    void emit(Instruction instruction);

    // Добавление инструкции с одним аргументом в конец программы
    void emit(Instruction instruction, int arg);

    // Запись инструкции без аргументов по указанному адресу
    void emitAt(int address, Instruction instruction);

    // Запись инструкции с одним аргументом по указанному адресу
    void emitAt(int address, Instruction instruction, int arg);

    // Получение адреса, непосредственно следующего за последней инструкцией в программе
    int getCurrentAddress();

    // Формирование "пустой" инструкции (NOP) и возврат ее адреса
    int reserve();

    // Запись последовательности инструкций в выходной поток
    void flush();

private:
    ostream& output_;                // Выходной поток
    vector<Command> commandBuffer_;  // Буфер инструкций
};

#endif
