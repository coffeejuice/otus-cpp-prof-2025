#include <iostream>
// #include <memory>
#include "01_simple_smart_ptr.h"


class NetworkConnection { // Класс, представляющий сетевое соединение (условная реализация)
public:
    NetworkConnection(const char* host) {
        std::cout << "Подключаемся к " << host << "...\n";
        // Здесь реально: открытие сокета, выделение буферов и т.д.
    }

    ~NetworkConnection() {
        std::cout << "Закрываем соединение и освобождаем ресурсы\n";
        // Реально: закрытие сокета, освобождение буферов
    }

    void sendData(const char* data) {
        std::cout << "Отправляем данные: " << data << "\n";
    }
};

void handleRequest() {
    // Создаем соединение. Без unique_ptr:
    // NetworkConnection* conn = new NetworkConnection("example.com");
    // auto conn = std::make_unique<NetworkConnection>("example.com");
    auto conn = custom_make_unique<NetworkConnection>("example.com");
    // auto conn2 = conn;
    // Имитируем исключение при работе
    throw std::runtime_error("Ошибка сети!");

    // conn->sendData("Данные"); // Не выполнится из-за исключения

} // Здесь автоматически вызовется деструктор NetworkConnection

int main() {
    try {
        handleRequest();
    } catch (...) {
        std::cout << "Поймали исключение, но ресурсы УЖЕ освобождены\n";
    }
}