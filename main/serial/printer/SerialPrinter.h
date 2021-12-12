template <typename T>
void show(T t) {
    Serial.println(t);
}

template <typename T, typename... Args>
void show(T first, Args... rest) {
    if (sizeof...(rest) == 0) {
        Serial.println(first);
        return;
    }

    Serial.print(first);

    show(rest...);
}