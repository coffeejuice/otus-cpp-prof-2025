#ifndef MINIMAL_WEAK_PTR_H  // Защита от повторного включения заголовочного файла
#define MINIMAL_WEAK_PTR_H  // Установка макроса для защиты

// Минимальная реализация shared_ptr (умного указателя с подсчетом ссылок)
template <typename T>  // Шаблонный класс для работы с любым типом T
class MinimalSharedPtr {
    T* obj;         // Указатель на управляемый объект
    int* cnt;       // Указатель на счетчик сильных ссылок (shared_ptr)
    int* weak_cnt;  // Указатель на счетчик слабых ссылок (weak_ptr)

public:
    // Конструктор, принимающий сырой указатель
    MinimalSharedPtr(T* p) : obj(p), cnt(new int(1)), weak_cnt(new int(0)) {}
    // new int(1) - создаем счетчик сильных ссылок = 1
    // new int(0) - создаем счетчик слабых ссылок = 0

    // Конструктор копирования
    MinimalSharedPtr(const MinimalSharedPtr& o) 
        : obj(o.obj), cnt(o.cnt), weak_cnt(o.weak_cnt) { 
        ++*cnt;  // Увеличиваем счетчик сильных ссылок
    }

    // Перегрузка оператора -> для доступа к объекту
    T* operator->() { return obj; }

    // Метод для получения количества сильных ссылок
    int count() { return *cnt; }

    // Метод для получения количества слабых ссылок
    int weak_count() { return *weak_cnt; }

    // Дружественный класс для доступа к приватным полям
    template <typename U> friend class MinimalWeakPtr;

    // Деструктор
    ~MinimalSharedPtr() { 
        if (--*cnt == 0) {   // Уменьшаем счетчик сильных ссылок
            delete obj;      // Удаляем объект, если счетчик = 0
            obj = nullptr;   // Обнуляем указатель

            // Если нет слабых ссылок, удаляем счетчики
            if (*weak_cnt == 0) {
                delete cnt;
                delete weak_cnt;
            }
        } 
    }
};

// Минимальная реализация weak_ptr (слабого указателя)
template <typename T>
class MinimalWeakPtr {
    T* obj;         // Указатель на объект (может быть невалидным)
    int* cnt;       // Указатель на счетчик сильных ссылок
    int* weak_cnt;  // Указатель на счетчик слабых ссылок

public:
    // Конструктор по умолчанию
    MinimalWeakPtr() : obj(nullptr), cnt(nullptr), weak_cnt(nullptr) {}

    // Конструктор от shared_ptr
    MinimalWeakPtr(const MinimalSharedPtr<T>& s) 
        : obj(s.obj), cnt(s.cnt), weak_cnt(s.weak_cnt) { 
        ++*weak_cnt;  // Увеличиваем счетчик слабых ссылок
    }

    // Конструктор копирования
    MinimalWeakPtr(const MinimalWeakPtr& o) 
        : obj(o.obj), cnt(o.cnt), weak_cnt(o.weak_cnt) { 
        if (weak_cnt) ++*weak_cnt;  // Увеличиваем счетчик, если он существует
    }

    // Проверка, валиден ли указатель
    bool expired() const { 
        return cnt == nullptr || *cnt == 0;  // true, если счетчик сильных ссылок = 0
    }

    // Преобразование weak_ptr в shared_ptr
    MinimalSharedPtr<T> lock() const {
        if (expired()) {
            // Возвращаем пустой shared_ptr, если объект удален
            return MinimalSharedPtr<T>(nullptr);
        }
        
        // Создаем новый shared_ptr на существующий объект
        MinimalSharedPtr<T> shared(nullptr);
        shared.obj = obj;          // Копируем указатель на объект
        shared.cnt = cnt;          // Копируем счетчик сильных ссылок
        shared.weak_cnt = weak_cnt; // Копируем счетчик слабых ссылок
        ++*cnt;                    // Увеличиваем счетчик сильных ссылок
        
        return shared;
    }
    
    // Деструктор
    ~MinimalWeakPtr() {
        if (weak_cnt && --*weak_cnt == 0) {  // Уменьшаем счетчик слабых ссылок
            if (*cnt == 0) {                // Если нет сильных ссылок
                delete cnt;                 // Удаляем счетчики
                delete weak_cnt;
            }
        }
    }
};

// Вспомогательная функция для создания shared_ptr
template <typename T>
MinimalSharedPtr<T> makeShared(const char* arg) {
    return MinimalSharedPtr<T>(new T(arg));  // Создаем объект и оборачиваем в shared_ptr
}

#endif  // Конец заголовочного файла