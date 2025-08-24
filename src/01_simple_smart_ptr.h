#pragma once

#include <utility>      // для std::forward

template <typename T>
class SimpleUniquePtr {  // Простейший самодельный умный указатель
private:
    T* ptr;

public:
    explicit SimpleUniquePtr(T* p) : ptr(p) {}  // Конструктор, принимающий обычный указатель

    // Запрещаем копирование
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;

    T* operator->() const { // Перегрузка оператора ->
        return ptr;
    }

    ~SimpleUniquePtr() { // Деструктор, освобождающий память
        delete ptr;
    }
};

template <typename T, typename... Args> // Вспомогательная функция для создания объекта
SimpleUniquePtr<T> custom_make_unique(Args&&... args) {
    return SimpleUniquePtr<T>(new T(std::forward<Args>(args)...));
}

