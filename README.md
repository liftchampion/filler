# filler

## О проекте
**Дано**: игра для двух игроков, игроки находятся на поле и каждый имеет свою территорию (в примерах: 1 клетка),  
"виртуальная машина" по очереди кидает игрокам рандомные фигурки. Игрок должен прикрепить полученную фигурку к себе так, что:  
+ территтория игрока и фигурки пересекается ровно 1 клеткой  
+ фигурка не пересекается с противником  
+ свободное поле фигурки не выходит за границы игрового поля  
+ если игрок не может положить фигурку или делает это неверно, игра для него заканчивается и ходит только противник  
+ игра кончается, когда оба игрока завершили игру или закончились фигурки (их количество неизвестно и это имеет мало значения)

**Задача**: к концу игры владеть большим количеством территории, чем противник.  
[Полное условие](https://github.com/liftchampion/filler/blob/master/filler.en.pdf)  
**Решение**: для выбора оптимальной подстановки использовался *волновой алгоритм*. Ход выбирался так, чтобы максимально увеличить сумму расстояний до всех клеток поля для противника; и максимально уменьшить её для себя.  
Вручную подбирались оптимальные коэффициенты для этих метрик.  
В дальнейшем были добавлены и другие метрики: повышенный приоритет для узких проходов, которые могут вскоре закрыться;  
повышенный приоритет на совершение таких ходов, что сделают свободные клетки поля недостижимыми для противника.  
**Итог**: дополнительные метрики ухудшили результат, но я всё же решил их оставить, потому что иногда, благодаря им,  
игрок совершает красивые ходы.  
Однако другие игроки, реализованные на схожем алгоритме, делают ходы быстрее и играют лучше.  
При том, что среди известных мне филлеров, игроки сделанные на волновом алгоритме, показывают лучший результат, я не считаю данный алгоритм оптимальным: переодически видно, как игрок ставит фигурку неоптимально.  
Я считаю, что требуется алгоритм, сильнее специализированный на данной задаче.

## Запуск
`make`  
`make -C visualizer`  
`./filler_vm -f maps/map00 -p1 players/bmiklaz.filler -p2 players/ggerardy.filler | ./visualizer/filler_visualizer`  
Вы можете выбрать карту в диапазоне `map00`-`map02` и любых двух игроков из папки `players`  

## Визуализация
Визуализация выполнена на библиотеке minilibx.
![map00](https://raw.githubusercontent.com/liftchampion/filler/master/imgs/Screen%20Shot%202019-05-13%20at%2021.30.27.png)
![map01](https://raw.githubusercontent.com/liftchampion/filler/master/imgs/Screen%20Shot%202019-05-13%20at%2021.29.40.png)
![map02](https://raw.githubusercontent.com/liftchampion/filler/master/imgs/Screen%20Shot%202019-05-13%20at%2021.28.59.png)

*C код написан в Norminette code style*
