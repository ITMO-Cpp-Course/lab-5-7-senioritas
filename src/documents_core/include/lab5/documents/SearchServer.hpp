#pragma once
#include "Document.hpp"
#include "InvertedIndex.hpp"
#include "DocumentBuilder.hpp"
#include <string>
#include <vector>

class SearchServer {
public:
    // Добавляет документ: обрабатывает через Builder, пишет в Index и Storage
    void AddDocument(size_t id, std::string name, std::string content);

    // Удаляет документ из всех систем
    void RemoveDocument(size_t id);

    // Основной поиск по одному слову (возвращает полные объекты документов)
    // Результаты можно отсортировать по релевантности (частоте слова)
    std::vector<Document> FindDocuments(const std::string& query) const;

private:
    DocumentStorage storage_;
    InvertedIndex index_;
};