# Лабораторная работа 2 - Dynamic Array

В ходе выполнения данной лабораторной работы был релизован АТД динамического массива:
  <br />
  ```
  template<typename T>
  class Array final
  ```
  <br />
  
АДТ поддерживает следующие операции:

- Конструктор
  ```
  Array();
  Array(int capacity);
  ```

- Деструктор
  ```
  ~Array();
  ```

- Вставка элементов (с использованием move-семантики)
  ```
  int insert(const T& value);
  int insert(int index, const T& value);
  ```

- Удаление элемента
  ```  
  void remove(int index);
  ```

- Обращение к элементу по индексу
  ```
  const T& operator[](int index) const;
  T& operator[](int index);
  ```
  
  - Возвращение размера массива
  ```
  int size() const;
  ```
  
  - Итератор
  ```
  Iterator iterator();
  ConstIterator iterator() const;
  ```
  
  - Реверсивный итератор
  ```
  Iterator reverseIterator();
  ConstIterator reverseIterator() const;
  ```
  
   Итератор реализован, как класс, и ему также доступны следующие операции:
  - Получение значения массива в текущей позиции итератора
    ```
    const T& get() const;
    ```
   - Установление значения в текущей позиции итератора
    ```
    void set(const T& value);
    ```
   - Перемещение текущей позиции итератора на следующий элемент
    ```
    void next();
    ```
   - Определение возможности перехода к следующему элементу (true/false)
    ```
    bool hasNext() const;
    ```

