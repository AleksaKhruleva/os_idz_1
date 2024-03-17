# Хрулева Александра Денисовна БПИ 229

## Вариант - 9

## Целевая оценка - 9

## Общая структура проекта ИДЗ №1 - "Применение каналов при обработке строк символов"
<pre>
idz_1/
|- README.md - этот файл
|- pictures - набор картинок для README.md
|- idz1_4/ - проект решения на 4 балла
|- idz1_5/ - проект решения на 5 баллов
|- idz1_6/ - проект решения на 6 баллов
|- idz1_7/ - проект решения на 7 баллов
|- idz1_8_1/ - проект решения на 8 баллов (модуль №1)
|- idz1_8_2/ - проект решения на 8 баллов (модуль №2)
|- idz1_9_1/ - проект решения на 9 баллов (модуль №1)
|- idz1_9_2/ - проект решения на 9 баллов (модуль №2)
|- case1i.txt - тестовый набор №1
|- case2i.txt - тестовый набор №2
|- case3i.txt - тестовый набор №3
|- case4i.txt - тестовый набор №4
|- case5i.txt - тестовый набор №5
|- idz1_4.sh - bash-скрипт - сборка и запуск проекта idz1_4
|- idz1_5.sh - bash-скрипт - сборка и запуск проекта idz1_5
|- idz1_6.sh - bash-скрипт - сборка и запуск проекта idz1_6
|- idz1_7.sh - bash-скрипт - сборка и запуск проекта idz1_7
|- idz1_8_1.sh - bash-скрипт - сборка и запуск проекта idz1_8_1
|- idz1_8_2.sh - bash-скрипт - сборка и запуск проекта idz1_8_2
|- idz1_9_1.sh - bash-скрипт - сборка и запуск проекта idz1_9_1
|- idz1_9_2.sh - bash-скрипт - сборка и запуск проекта idz1_9_2
\- rm_output_files.sh - bash-скрипт - удалить файлы результатов по маске "case?o.txt"
</pre>

## Общее условие
Разработать программы, состоящие из нескольких параллельных процессов, взаимодействующих между собой через каналы. Количество программ в задании из их характеристики определяются в соответствии с требованиями выполнения на соответствующую оценку.

## Индивидуальное условие №9
Разработать программу, которая «переворачивает на месте» заданную ASCII–строку символов после ее полной записи в буфер процесса, осуществляющего обработку (не копируя строку в другой буфер). Формирование требуемого буфера в случае чтения строки по частям осуществлять динамически. То есть, представлять его либо как список динамически формируемых частичных строк, либо при добавлении очередного фрагмента выделять более длинный участок, делая перенос данных из ранее выделенного. При этом допускается выделять память под строку фрагментами размер которох в 10 раз превышает размер буфера, используемого для передачи данных через канал.

## Входные тестовые файлы
Общий набор для всех вариантов решений:
<pre>
idz_1/case1i.txt
idz_1/case2i.txt
idz_1/case3i.txt
idz_1/case4i.txt
idz_1/case5i.txt
</pre>

## Выходные результирующие файлы
Имена результирующих файлов:
<pre>
case1o.txt
case2o.txt
case3o.txt
case4o.txt
case5o.txt
</pre>
Для каждого решения создаются в каталоге проекта.

## Решение на 4 балла (idz1_4/)
Разработать программу, осуществляющую взаимодействие между тремя родственными процессами одной программы с использованием неименованных каналов.
Консольное приложение, использующее неименованные каналы, обеспечивающее взаимодействие по следующей схеме:
- первый процесс читает текстовые данные из заданного файла и через неименованный канал передает их второму процессу 
- второй процесс осуществляет обработку данных в соответствии с вариантом задания и передает результат обработки через неименованный канал третьему процессу 
- третий процесс осуществляет вывод данных в заданный файл

<img src="pictures/pic4.png" alt="pic4" width="70%">

Командная строка:
<pre>
idz1_4 -i input_file_name -o output_file_name
</pre>

## Решение на 5 баллов (idz1_5/)
Разработать программу, в которой взаимодействие между тремя родственными процессами одной программы осуществляется через именованные каналы. 
Консольное приложение, использующее именованные каналы, обеспечивающее взаимодействие по следующей схеме:
- первый процесс читает текстовые данные из заданного файла и через именованный канал передает их второму процессу 
- второй процесс осуществляет обработку данных в соответствии с заданием и передает результат обработки через именованный канал третьему процессу 
- третий процесс осуществляет вывод данных в заданный файл

<img src="pictures/pic5.png" alt="pic5" width="70%">

Командная строка:
<pre>
idz1_5 -i input_file_name -o output_file_name
</pre>

## Решение на 6 баллов (idz1_6/)
Разработать программу, которая осуществляет взаимодействие между двумя родственными процессами одной программы с использованием неименованных каналов.
Консольное приложение, использующее неименованные каналы, обеспечивающее взаимодействие по следующей схеме:
- первый процесс читает текстовые данные из заданного файла и через неименованный канал передает их второму процессу 
- второй процесс осуществляет обработку данных в соответствии с заданием и передает результат обработки через неименованный канал обратно первому процессу 
- первый процесс осуществляет вывод данных в заданный файл

<img src="pictures/pic6.png" alt="pic6" width="70%">

Командная строка:
<pre>
idz1_6 -i input_file_name -o output_file_name
</pre>

## Решение на 7 баллов (idz1_7/)
Разработать программу, которая осуществляет взаимодействие между двумя родственными процессами одной программы с использованием именованных каналов.
Консольное приложение, использующее именованные каналы, обеспечивающее взаимодействие по следующей схеме:
- первый процесс читает текстовые данные из заданного файла и через именованный канал передает их второму процессу
- второй процесс осуществляет обработку данных в соответствии с заданием и передает результат обработки через именованный канал обратно первому процессу
- первый процесс осуществляет вывод данных в заданный файл

<img src="pictures/pic7.png" alt="pic7" width="70%">

Командная строка:
<pre>
idz1_7 -i input_file_name -o output_file_name
</pre>

## Решение на 8 баллов (idz1_8_1/ + idz1_8_2/)
Разработать программный продукт, в котором осуществляется взаимодействие между двумя независимыми процессами разных программ с использованием именованных каналов.
Консольное приложение, использующее именованные каналы, обеспечивающее взаимодействие по следующей схеме:
- первый процесс читает текстовые данные из заданного файла и через именованный канал передает их второму процессу 
- второй процесс осуществляет обработку данных в соответствии с заданием и передает результат обработки через именованный канал обратно первому процессу 
- первый процесс осуществляет вывод данных в заданный файл

<img src="pictures/pic8.png" alt="pic8" width="70%">

Командная строка:
<pre>
idz1_8_1 -i input_file_name -o output_file_name
idz1_8_2
</pre>

## Решение на 9 баллов (idz1_9_1/ + idz1_9_2/)
Разработать программный продукт, в котором осуществляется взаимодействие между двумя независимыми процессами разных программ с использованием именованных каналов. Обмен данными ведется за счет многократной передачи текста через ограниченные по размеру буферы.
Консольное приложение, использующее именованные каналы, обеспечивающее взаимодействие по следующей схеме:
- первый процесс читает ограниченную порцию текстовых данных из заданного файла и через именованный канал передает их второму процессу
- второй процесс осуществляет обработку части данных в соответствии с заданием и при необходимости передает результат обработки (если он при этом сформировался) через именованный канал обратно первому процессу или получает от него следующую порцию
- первый процесс осуществляет вывод результата в заданный файл или сразу, или по частям в зависимости от условия задачи и размера буфера, используемого для пересылки данных
  
<img src="pictures/pic9.png" alt="pic9" width="70%">

Командная строка:
<pre>
idz1_9_1 -i input_file_name -o output_file_name
idz1_9_2
</pre>