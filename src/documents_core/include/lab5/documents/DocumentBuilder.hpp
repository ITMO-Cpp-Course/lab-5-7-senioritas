#pragma once
#include "Document.hpp"
#include <string>
#include <vector>
namespace lab5::documents
{
class DocumentBuilder
{
  public:
    // Создает объект Document, приводя текст к нижнему регистру
    static Document Build(size_t id, const std::string& name, std::string content);

    // Разбивает текст на слова, убирая знаки препинания
    static std::vector<std::string> Tokenize(const std::string& text);

    // Вспомогательная функция для очистки слова
    static std::string Normalize(std::string word);
};
} // namespace lab5::documents
