#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstddef>

namespace lab5::documents
{
class InvertedIndex {
public:
    // Принимает ID документа и список очищенных слов
    void AddDocument(size_t doc_id, const std::vector<std::string>& words);

    // Удаляет упоминания документа из всех индексов
    void RemoveDocument(size_t doc_id);

private:
    // Слово -> { ID документа -> количество вхождений }
    std::unordered_map<std::string, std::map<size_t, size_t>> index_;
};
}
