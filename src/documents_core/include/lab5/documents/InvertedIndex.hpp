#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

class InvertedIndex {
public:
    // Принимает ID документа и список очищенных слов
    void Add(size_t doc_id, const std::vector<std::string>& words);

    // Возвращает словарь: ID документа -> сколько раз слово там встретилось
    const std::map<size_t, size_t>& Lookup(const std::string& word) const;

    // Удаляет упоминания документа из всех индексов
    void Remove(size_t doc_id);

private:
    // Слово -> { ID документа -> количество вхождений }
    std::unordered_map<std::string, std::map<size_t, size_t>> index_;
};