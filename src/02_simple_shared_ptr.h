#ifndef MINIMAL_SHARED_PTR_H  // Защита от повторного включения заголовка
#define MINIMAL_SHARED_PTR_H  // Определяем макрос для защиты

template <typename T>  // Шаблонный класс (работает с любым типом T)
class MinimalSharedPtr {
    T* obj;        // Сырой указатель на управляемый объект
    int* cnt;      // Указатель на счётчик ссылок (сколько shared_ptr владеют объектом)
    
public:
    // Конструктор, принимающий сырой указатель
    MinimalSharedPtr(T* p) : obj(p), cnt(new int(1)) {}  // создаём новый счётчик = 1
    
    // Конструктор копирования (создаёт новый shared_ptr на тот же объект)
    MinimalSharedPtr(const MinimalSharedPtr& o) 
        : obj(o.obj),       // копируем указатель на объект
          cnt(o.cnt)        // и указатель на счётчик
    { 
        ++*cnt;             // увеличиваем счётчик ссылок
    }
    
    // Перегрузка оператора -> (даёт доступ к полям объекта)
    T* operator->() { return obj; }  // возвращаем сырой указатель
    
    // Метод для получения текущего значения счётчика
    int count() { return *cnt; }  // разыменовываем cnt и возвращаем значение
    
    // Деструктор
    ~MinimalSharedPtr() { 
        if (--*cnt == 0) {  // уменьшаем счётчик и проверяем на 0
            delete obj;      // если это последний shared_ptr - удаляем объект
            delete cnt;      // и счётчик тоже
        } 
    }
};

// Вспомогательная функция для удобного создания shared_ptr
template <typename T>
MinimalSharedPtr<T> makeShared(const char* arg) {
    return MinimalSharedPtr<T>(new T(arg));  // создаём объект T и сразу оборачиваем
}

#endif  // Конец заголовочного файла
