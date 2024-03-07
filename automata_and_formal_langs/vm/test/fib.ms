; Вычисление N-го числа Фибоначчи

SET     0               0       ; Константа 0
SET     1               1       ; Константа 1

SET     1000            0       ; Переменная n
SET     1001            1       ; Переменная a
SET     1002            1       ; Переменная b

; Программа

 0:     INPUT
 1:     STORE           1000    ; n := READ

 2:     LOAD            1000
 3:     LOAD            1
 4:     COMPARE         3       ; IF n > 1
 5:     JUMP_NO         17

 6:     LOAD            1002    ; STACK <- b
 7:     LOAD            1001    ; STACK <- a
 8:     LOAD            1002
 9:     STORE           1001    ; a := b
10:     ADD 
11:     STORE           1002    ; b := старое_значение_a + b

12:     LOAD            1000
13:     LOAD            1
14:     SUB 
15:     STORE           1000    ; n := n - 1
16:     JUMP            2

17:     LOAD            1001    ; WRITE(a)
18:     PRINT 

19:     STOP 

