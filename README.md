# YADRO_test


## Иструкция к запуску


Программа компилируется в ОС Linux

Склонировать репозиторий





```
git clone https://github.com/Sonya-1/YADRO_test
```



Перейти в папку


```
cd YADRO_test
```



Скомпилировать файлы





```
g++ -o main main.cpp Club.cpp TimeUtility.cpp
```





Запустить с указанием тестового файла





```
./main file.txt
```



## Компиляция и запуск проверочных юнит-тестов


```
cmake -S . -B build
```


```
cmake --build build
```


```
cd build && ctest
```


Тест 1 - Проверка корректности перевода времени в в 24-часовой формат


Тест 2 - Проверка функции состояния клинта в компьютерном клубе (находится или нет)


Тест 3 - Проерка поиска клиента в клубе


Тест 4 - Проверка удаления клиента из вектора всех клиентов (уход из клуба)




## Тестовые файлы и результаты работы программы





`file` - Тестовый файл из задания

Результат:






![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/1.png)





`file1` - Случай, когда клиент поменял стол


Результат:





![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/2.png)





`file2` - Случай, когда клиент пересаживается за стол, который занимает

Результат:



![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/3.png)





`file3` - Проверка формата времени в событии

Результат:



![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/4.png)





`file4` - Случаи, когда:

- клиент уже есть в клубе и пытается зайти снова;

- в очереди ожидания клиентов больше, чем общее число столов;

- клиент не находится в компьютерном клубе, но пытается занять стол.


Результат:

![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/5.png)
 

`file5` - Случай, когда наглядно видна сортировка клиентов в конце рабочего дня


Результат:

![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/6.png)


`file6` - Проверка очередности входящих событий


Результат:

![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/7.png)
