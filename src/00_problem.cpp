// ПРАВИЛЬНО!
void processUserData() {
    auto results = std::shared_ptr<QueryResults>(queryDatabase());
    // Кеш хранит shared_ptr на результаты
    cache.store("user_query", results);
    
    // Где-то в другом потоке
    if(auto cachedResults = cache.get("user_query")) {
        // Используем результаты
    }
}
// Когда последняя ссылка исчезнет - память освободится


// НЕ ПРАВИЛЬНО!
void processUserData() {
    QueryResults* results = queryDatabase();
    // Кто удалит эту память? Кеш? Пользователь кеша?
    cache.store("user_query", results);
    
    // В другом потоке
    QueryResults* cachedResults = cache.get("user_query");
    // А вдруг кто-то уже удалил? Крэш!
    
    // Утечка, если забыли удалить
}