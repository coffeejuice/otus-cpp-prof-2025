#include <iostream>
#include "03_minimal_weak_ptr.h"

class Connection {
public:
    Connection(const char* h) { std::cout << "Подключение: " << h << "\n"; }
    ~Connection() { std::cout << "Отключение\n"; }
    void send() { std::cout << "Отправка данных\n"; }
};

class Client {
    MinimalWeakPtr<Connection> conn;
public:
    void setConnection(const MinimalSharedPtr<Connection>& c) {
        conn = c;
        std::cout << "Клиент получил соединение\n";
    }
    
    void sendData() {
        if (conn.expired()) {
            std::cout << "Ошибка: соединение уже закрыто\n";
            return;
        }
        
        // Получаем временный shared_ptr из weak_ptr
        auto sharedConn = conn.lock();
        std::cout << "Счетчик во время отправки: " << sharedConn.count() << "\n";
        sharedConn->send();
    }
};

int main() {
    // Создаем клиента с долгим временем жизни
    Client client;
    
    {
        // Блок, в котором соединение активно
        std::cout << "--- Открываем блок с соединением ---\n";
        auto conn = makeShared<Connection>("server");
        
        // Передаем соединение клиенту
        client.setConnection(conn);
        
        // Клиент может использовать соединение
        client.sendData();
        
        std::cout << "--- Закрываем блок с соединением ---\n";
    } // Здесь соединение уничтожается
    
    // Пробуем использовать закрытое соединение
    std::cout << "\n--- Пробуем использовать соединение после закрытия ---\n";
    client.sendData(); // Должна быть ошибка
    
    return 0;
}
