#include <iostream>
#include <unordered_map>

class WriteThroughCache {
private:
    std::unordered_map<int, int> cache; // Кэш в памяти
    std::unordered_map<int, int> storage; // Основное хранилище

public:
    // Метод записи в кэш
    void put(int key, int value) {
        // Записываем в кэш
        cache[key] = value;
        // Записываем сразу в основное хранилище
        storage[key] = value;
        std::cout << "Записано: ключ = " << key << ", значение = " << value << std::endl;
    }

    // Метод чтения из кэша
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            std::cout << "Из кэша: ключ = " << key << ", значение = " << cache[key] << std::endl;
            return cache[key];
        }
        else if (storage.find(key) != storage.end()) {
            // Если в кэше нет, читаем из основного хранилища
            int value = storage[key];
            // И добавляем в кэш
            cache[key] = value;
            std::cout << "Из хранилища: ключ = " << key << ", значение = " << value << std::endl;
            return value;
        }
        else {
            std::cout << "Ключ " << key << " не найден." << std::endl;
            return -1; // Значение не найдено
        }
    }
};
int main() {
    setlocale(LC_ALL, "Russian");
    WriteThroughCache cache;
    cache.put(1, 100); // Добавляем пару ключ-значение
    cache.put(2, 200);

    cache.get(1); // Читаем из кэша
    cache.get(2);
    cache.get(3); // Пытаемся прочитать несуществующий ключ

    return 0;
}