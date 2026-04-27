#pragma once
#include <cstddef>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{
class InvertedIndex
{
  public:
    // Принимает ID документа и список очищенных слов
    void AddDocument(size_t doc_id, const std::vector<std::string>& words);

    // Удаляет упоминания документа из всех индексов
    void RemoveDocument(size_t doc_id);

    // Получить по слову количество вхожлений в каждом документе и общее количество вхождений
    std::pair<std::map<size_t, size_t>, size_t> GetResultsForWord(std::string word);

    // Получить по слову список документов, в которые он входит
    std::vector<size_t> GetListOfDocementsForWord(std::string word);

  private:
    // Слово -> { ID документа -> количество вхождений }
    std::unordered_map<std::string, std::map<size_t, size_t>> index_;
};
} // namespace lab5::documents
