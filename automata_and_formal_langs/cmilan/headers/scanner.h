#ifndef CMILAN_SCANNER_H
#define CMILAN_SCANNER_H

#include <fstream>
#include <string>
#include <map>

using namespace std;

enum Token {
    T_EOF,         // Конец текстового потока
    T_ILLEGAL,     // Признак недопустимого символа
    T_IDENTIFIER,  // Идентификатор
    T_NUMBER,      // Целочисленный литерал
    T_BEGIN,       // Ключевое слово "begin"
    T_END,         // Ключевое слово "end"
    T_IF,          // Ключевое слово "if"
    T_THEN,        // Ключевое слово "then"
    T_ELSE,        // Ключевое слово "else"
    T_FI,          // Ключевое слово "fi"
    T_WHILE,       // Ключевое слово "while"
    T_DO,          // Ключевое слово "do"
    T_OD,          // Ключевое слово "od"
    T_WRITE,       // Ключевое слово "write"
    T_READ,        // Ключевое слово "read"
    T_ASSIGN,      // Оператор ":="
    T_ADDOP,       // Сводная лексема для "+" и "-" (операция типа сложения)
    T_MULOP,       // Сводная лексема для "*" и "/" (операция типа умножения)
    T_CMP,         // Сводная лексема для операторов отношения
    T_LPAREN,      // Открывающая скобка
    T_RPAREN,      // Закрывающая скобка
    T_SEMICOLON,   // ";"
    T_SKIP         // Пустой оператор "skip", эквивалентен "NOP"
};

// Функция tokenToString возвращает описание лексемы.
// Используется при печати сообщения об ошибке.
const char* tokenToString(Token t);

// Виды операций сравнения
enum Cmp {
    C_EQ,  // Операция сравнения "="
    C_NE,  // Операция сравнения "!="
    C_LT,  // Операция сравнения "<"
    C_LE,  // Операция сравнения "<="
    C_GT,  // Операция сравнения ">"
    C_GE   // Операция сравнения ">="
};

// Виды арифметических операций
enum Arithmetic {
    A_PLUS,      //операция "+"
    A_MINUS,     //операция "-"
    A_MULTIPLY,  //операция "*"
    A_DIVIDE     //операция "/"
};

// Лексический анализатор

class Scanner {
public:
    // Конструктор. В качестве аргумента принимает имя файла и поток,
    // из которого будут читаться символы транслируемой программы.

    explicit Scanner(const string& fileName, istream& input)
        : fileName_(fileName), lineNumber_(1), input_(input) {
        keywords_["begin"] = T_BEGIN;
        keywords_["end"] = T_END;
        keywords_["if"] = T_IF;
        keywords_["then"] = T_THEN;
        keywords_["else"] = T_ELSE;
        keywords_["fi"] = T_FI;
        keywords_["while"] = T_WHILE;
        keywords_["do"] = T_DO;
        keywords_["od"] = T_OD;
        keywords_["write"] = T_WRITE;
        keywords_["read"] = T_READ;
        keywords_["skip"] = T_SKIP;

        nextChar();
    }

    // Деструктор
    virtual ~Scanner() {}

    // getters всех private переменных
    const string& getFileName() const  //не используется
    {
        return fileName_;
    }

    int getLineNumber() const {
        return lineNumber_;
    }

    Token token() const {
        return token_;
    }

    int getIntValue() const {
        return intValue_;
    }

    string getStringValue() const {
        return stringValue_;
    }

    Cmp getCmpValue() const {
        return cmpValue_;
    }

    Arithmetic getArithmeticValue() const {
        return arithmeticValue_;
    }

    // Переход к следующей лексеме.
    // Текущая лексема записывается в token_ и изымается из потока.
    void nextToken();

private:
    // Пропуск всех пробельные символы.
    // Если встречается символ перевода строки, номер текущей строки
    // (lineNumber) увеличивается на единицу.
    void skipSpace();


    void nextChar();  //переходит к следующему символу
    //проверка переменной на первый символ (должен быть буквой латинского алфавита)
    bool isIdentifierStart(char c) {
        return ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z'));
    }
    //проверка на остальные символы переменной (буква или цифра)
    bool isIdentifierBody(char c) {
        return isIdentifierStart(c) || isdigit(c);
    }


    const string fileName_;  //входной файл
    int lineNumber_;         //номер текущей строки кода

    Token token_;                 //текущая лексема
    int intValue_;                //значение текущего целого
    string stringValue_;          //имя переменной
    Cmp cmpValue_;                //значение оператора сравнения (>, <, =, !=, >=, <=)
    Arithmetic arithmeticValue_;  //значение знака (+,-,*,/)

    map<string, Token> keywords_;  //ассоциативный массив с лексемами и
    //соответствующими им зарезервированными словами в качестве индексов

    istream& input_;  //входной поток для чтения из файла.
    char ch_;         //текущий символ
};

#endif
