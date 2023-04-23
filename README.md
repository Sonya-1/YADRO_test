# Тестовое задание


## Запуск программы


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

g++ -o main main.cpp

```





Запуск





```

./main file.txt

```





## Тестовые файлы и результаты работы программы





`file` - Тестовый файл из задания

Результат:






![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/1.png)





`file1` - Случай, когда клиент поменял стол





Таблица, для наглядного изменения работы компьютерного клуба:

Время | 1 стол | 2 стол | 3 стол | Выручка | Время работы стола
--- | --- | --- | --- | --- | ---
09:54 | client1 |  | 
10:25 | client1 | client2 | 
10:58 |  | client2 | client1 | (20, 0, 0) | (01:04, 0, 0)
12:33 |  | client2 | client4 | (20, 0, 20) | (01:04, 0, 01:35)
12:43 |  |  | client4 | (20, 30, 20) | (01:04, 02:18, 01:35)
15:52 |  |  |  | (20, 30, 60) | (01:04, 02:18, 04:54)
19:00 |  |  | |(20, 30, 60) | (01:04, 02:18, 04:54)

Результат:





![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/2.png)





`file2` - Случай, когда клиент попытался сесть за стол, который занимает

Результат:



![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/3.png)





`file3` - Проверка входных данных

Результат:



![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/4.png)





`file4` - Случаи, когда:

- клиент уже есть в клубе и пытается зайти снова;

- в очереди ожидания клиентов больше, чем общее число столов;

- клиент не находится в компьютерном клубе, но пытается занять стол.

Таблица, для наглядного изменения работы компьютерного клуба:

Время | 1 стол | 2 стол | 3 стол | Выручка | Время работы стола
--- | --- | --- | --- | --- | ---
09:54 | client1 |  | 
10:25 | client1 | client2 | 
10:59 | client1 | client2 | client3 | 
12:33 | client4 | client2 | client3 | (30, 0, 0) | (2:39, 0, 0)
12:43 | client4 | client5 | client3 | (30, 30, 0) | (2:39, 2:18, 0)
15:52 | client6 | client5 | client3 | (70, 30, 0) | (5:58, 2:18, 0)
19:00 | client6 | client5 | client3 | (110, 100, 90) | (9:06, 08:35, 8:01)

Результат:

![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/5.png)

Пояснение:
Так как размер очереди ожидания задается количеством столов, то размер очереди равен 3. В 10:59 все столы заняты, поэтому client4, client5 и client6 ждут своей очереди, а client7 уходит в 11:48, так как очередь переполнена. 

`file5` 

Таблица, для наглядного изменения работы компьютерного клуба:

Время | 1 стол | 2 стол | 3 стол | 4 стол | Выручка | Время работы стола
--- | --- | --- | --- | --- | --- | ---
10:54 |  | vasya | 
11:25 | kolya | vasya | 
12:05 | kolya | vasya | maksim | 
12:23 |  | vasya | maksim |  | (15, 0, 0, 0) | (00:58, 0, 0, 0)
13:35 |  | vasya | maksim | petya | (45, 0, 0, 0) | (00:58, 0, 0, 0)
13:46 |  | vasya |  | petya | (45, 0, 30, 0) | (00:58, 0, 01:41, 0)
13:59 |  | vasya | petya |  | (45, 0, 30, 15) | (00:58, 0, 01:41, 00:24)
14:43 |  | vasya |  |  | (45, 0, 45, 15) | (00:58, 0, 02:25, 00:24)
19:30 |  | vasya |  |  | (45, 135, 45, 15) | (00:58, 08:36, 02:25, 00:24)


Результат:

![Image alt](https://github.com/Sonya-1/YADRO_test/blob/main/img/6.png)

Пояснение:
Клиенты встают в очередь, только если произошло событие 3, поэтому клиент petya не занимал место до события 2 в 13:35
