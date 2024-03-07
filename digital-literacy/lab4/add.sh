#!/bin/bash

# Напишите, сценарий, принимающий нечётное целое число N и выводящий на экран треугольник,
#   выполненный в псевдографике с помощью N строк. Число символов в строке равно номеру строки.
# Для N = 5:
#       *
#      **
#     ***
#    ****
#   *****

N=$1
# Проверка числа N на нечётность и положительность.
if [[ $N -ge 1 ]] && (( $N % 2 )); then
    for i in $(eval echo {$N..1} {2..$N}); do
        shuf -e ' ' -zrn $((N-i))
        shuf -e ' *' -zrn $i
        echo
    done
fi
