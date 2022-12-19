# Лабораторная работа 2 - Dynamic Array

В ходе выполнения данной лабораторной работы был релизован АТД динамического массива:
  <br /><br />
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
