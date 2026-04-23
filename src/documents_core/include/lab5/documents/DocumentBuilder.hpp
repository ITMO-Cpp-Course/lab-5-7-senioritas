#pragma once
#include "Document.hpp"
#include <string>
#include <vector>

class DocumentBuilder {
public:
    // Создает объект Document, приводя текст к нижнему регистру
    static Document Build(size_t id, std::string name, std::string content);

    // Разбивает текст на слова, убирая знаки препинания
    static std::vector<std::string> Tokenize(const std::string& text);

private:
    // Вспомогательная функция для очистки слова
    static std::string Normalize(std::string word);
};