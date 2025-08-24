#include <iostream>
#include "02_simple_shared_ptr.h"

class Connection {
public:
    Connection(const char* h) { std::cout << "Подключение: " << h << "\n"; }
    ~Connection() { std::cout << "Отключение\n"; }
    void send() { std::cout << "Отправка данных\n"; }
};

void use(MinimalSharedPtr<Connection> c) {
    std::cout << "Счетчик в функции Use: " << c.count() << "\n";
    c->send();
}

int main() {
    auto c1 = makeShared<Connection>("server");
    std::cout << "Счетчик: " << c1.count() << "\n";
    
    {
        auto c2 = c1;
        std::cout << "После копирования: " << c1.count() << "\n";
        use(c1);
    }
    
    std::cout << "После удаления копии: " << c1.count() << "\n";
    return 0;
}
