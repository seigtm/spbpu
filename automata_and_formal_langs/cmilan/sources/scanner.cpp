#include "scanner.h"
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

static const char* tokenNames_[] = {
    "end of file",
    "illegal token",
    "identifier",
    "number",
    "'BEGIN'",
    "'END'",
    "'IF'",
    "'THEN'",
    "'ELSE'",
    "'FI'",
    "'WHILE'",
    "'DO'",
    "'OD'",
    "'WRITE'",
    "'READ'",
    "':='",
    "'+' or '-'",
    "'*' or '/'",
    "comparison operator",
    "'('",
    "')'",
    "';'",
    // "SKIP"  // NOTE: added skip token.
};

void Scanner::nextToken() {
    skipSpace();

    // Пропускаем комментарии
    // 1. Многострочные комментарии вида /* ... */
    //      Если встречаем "/", то за ним должна идти "*". Если "*" не встречена, считаем, что встретили операцию деления
    //      и лексему - операция типа умножения. Дальше смотрим все символы, пока не находим звездочку или символ конца файла.
    //      Если нашли * - проверяем на наличие "/" после нее. Если "/" не найден - ищем следующую "*".
    // 2. Однострочные комментарии вида //
    //      Если встречаем "/", то за ним должна идти ещё одна "/". Если "/" не встречена, считаем, что встретили операцию деления.
    while(ch_ == '/') {
        nextChar();
        if(ch_ == '*') {
            nextChar();
            bool inside = true;
            while(inside) {
                while(ch_ != '*' && !input_.eof()) {
                    nextChar();
                }

                if(input_.eof()) {
                    token_ = T_EOF;
                    return;
                }

                nextChar();
                if(ch_ == '/') {
                    inside = false;
                    nextChar();
                }
            }
        } else if(ch_ == '/') {
            // Пропускаем все символы до символа конца строки.
            while(ch_ != '\n' && !input_.eof()) {
                nextChar();
            }
        } else {
            token_ = T_MULOP;
            arithmeticValue_ = A_DIVIDE;
            return;
        }

        skipSpace();
    }

    //Если встречен конец файла, считаем за лексему конца файла.
    if(input_.eof()) {
        token_ = T_EOF;
        return;
    }
    //Если встретили цифру, то до тех пока дальше идут цифры - считаем как продолжение числа.
    //Запоминаем полученное целое, а за лексему считаем целочисленный литерал

    if(isdigit(ch_)) {
        int value = 0;
        while(isdigit(ch_)) {
            value = value * 10 + (ch_ - '0');  //поразрядное считывание, преобразуем символьное значение к числу.
            nextChar();
        }
        token_ = T_NUMBER;
        intValue_ = value;
    }
    //Если же следующий символ - буква ЛА - тогда считываем до тех пор, пока дальше буквы ЛА или цифры.
    //Как только считали имя переменной, сравниваем ее со списком зарезервированных слов. Если не совпадает ни с одним из них,
    //считаем, что получили переменную, имя которой запоминаем, а за текущую лексему считаем лексему идентификатора.
    //Если совпадает с каким-либо словом из списка - считаем что получили лексему, соответствующую этому слову.
    else if(isIdentifierStart(ch_)) {
        string buffer;
        while(isIdentifierBody(ch_)) {
            buffer += ch_;
            nextChar();
        }

        transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

        map<string, Token>::iterator kwd = keywords_.find(buffer);
        if(kwd == keywords_.end()) {
            token_ = T_IDENTIFIER;
            stringValue_ = buffer;
        } else {
            token_ = kwd->second;
        }
    }
    //Символ не является буквой, цифрой, "/" или признаком конца файла
    else {
        switch(ch_) {
            //Признак лексемы открывающей скобки - встретили "("
            case '(':
                token_ = T_LPAREN;
                nextChar();
                break;
            //Признак лексемы закрывающей скобки - встретили ")"
            case ')':
                token_ = T_RPAREN;
                nextChar();
                break;
            //Признак лексемы ";" - встретили ";"
            case ';':
                token_ = T_SEMICOLON;
                nextChar();
                break;
            //Если встречаем ":", то дальше смотрим наличие символа "=". Если находим, то считаем что нашли лексему присваивания
            //Иначе - лексема ошибки.
            case ':':
                nextChar();
                if(ch_ == '=') {
                    token_ = T_ASSIGN;
                    nextChar();

                } else {
                    token_ = T_ILLEGAL;
                }
                break;
            //Если встретили символ "<", то либо следующий символ "=", тогда лексема нестрогого сравнения. Иначе - строгого.
            case '<':
                token_ = T_CMP;
                nextChar();
                if(ch_ == '=') {
                    cmpValue_ = C_LE;
                    nextChar();
                } else {
                    cmpValue_ = C_LT;
                }
                break;
            //Аналогично предыдущему случаю
            case '>':
                token_ = T_CMP;
                nextChar();
                if(ch_ == '=') {
                    cmpValue_ = C_GE;
                    nextChar();
                } else {
                    cmpValue_ = C_GT;
                }
                break;
            //Если встретим "!", то дальше должно быть "=", тогда считаем, что получили лексему сравнения
            //и знак "!=" иначе считаем, что у нас лексема ошибки
            case '!':
                nextChar();
                if(ch_ == '=') {
                    nextChar();
                    token_ = T_CMP;
                    cmpValue_ = C_NE;
                } else {
                    token_ = T_ILLEGAL;
                }
                break;
            //Если встретим "=" - лексема сравнения и знак "="
            case '=':
                token_ = T_CMP;
                cmpValue_ = C_EQ;
                nextChar();
                break;
            //Знаки операций. Для "+"/"-" получим лексему операции типа сложнения, и соответствующую операцию.
            //для "*" - лексему операции типа умножения
            case '+':
                token_ = T_ADDOP;
                arithmeticValue_ = A_PLUS;
                nextChar();
                break;

            case '-':
                token_ = T_ADDOP;
                arithmeticValue_ = A_MINUS;
                nextChar();
                break;

            case '*':
                token_ = T_MULOP;
                arithmeticValue_ = A_MULTIPLY;
                nextChar();
                break;
            //Иначе лексема ошибки.
            default:
                token_ = T_ILLEGAL;
                nextChar();
                break;
        }
    }
}

void Scanner::skipSpace() {
    while(isspace(ch_)) {
        if(ch_ == '\n') {
            ++lineNumber_;
        }

        nextChar();
    }
}

void Scanner::nextChar() {
    ch_ = input_.get();
}

const char* tokenToString(Token t) {
    return tokenNames_[t];
}
