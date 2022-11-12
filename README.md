## План

- [x] Спланировать и реализовать фреймворк для трассировки алгоритмов/структур данных
- [ ] Реализовать желаемый набор алгоритмов:
	- [x] Бинарное дерево
	- [x] Красно-черное дерево
	- [x] Алгоритм Дейкстры
	- [x] Поиск в ширину
	- [x] Поиск в глубину
	- [x] Хеш-функция
	- [ ] Хеш-таблица
	- [x] Связный список
	- [x] Стек
	- [ ] Очередь с приоритетом (?)
	- [x] Пирамидальная сортировка
	- [ ] Поиск с возвратом
	- [ ] Подмножества (?)
	- [ ] Перестановки (?)
	- [ ] Ферзи (?)
- [ ] Спроектировать и спланировать приложение-визуализатор
	- [ ] Описать экраны и предполагаемые сценарии использования приложения
	- [ ] Определиться с фреймворками и инструментами
	- [ ] Спланировать архитектуру приложения
- [ ] Реализовать приложение

## Структура

Фреймворк трассировки реализует паттерн "Наблюдатель": в объект, реализующий алгоритм, внедряется наблюдатель, с помощью которого алгоритм может оповещать подписчиков наблюдателя о всех совершаемых шагах, отправляя наблюдателю команды. Предполагается, что визуализатор подпишется на обновления алгоритма и будет изменять отображение в ответ на отправляемые алгоритмом сообщения. Один из вариантов реализации трассировки можно [посмотреть](/Project/Algorithms/Util/Hash/Test.h) на примере теста хеш-функции.

### Подробнее:

- [Алгоритмы](/Project/Algorithms/README.md)
- [Трассировка и интерфейсы](/Project/CommandFramework/README.md)
