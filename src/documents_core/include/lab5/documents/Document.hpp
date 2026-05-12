#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
namespace lab5::documents
{
using DocId = size_t; // беззнаковый тип, защищенный от отрицательных значений
// плюс все контейнеры поддерживают сайз т
struct Document
{
    DocId id; // Уникальный номер. По нему InvertedIndex находит вхождения слов
    std::string name;
    std::string content; // Тело документа (весь текст), который DocumentBuilder будет разбивать на слова.
};
} // namespace lab5::documents
