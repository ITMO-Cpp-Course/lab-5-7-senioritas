#pragma once

#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace lab5::documents
{

class UpdateTransaction;
class IndexStore
{
  public:
    IndexStore() = default;

    IndexStore(const IndexStore&) = delete;
    IndexStore& operator=(const IndexStore&) = delete;

    Result<std::pair<std::map<DocId, size_t>, size_t>> GetResultsForWord(const std::string& word) const;

    Result<std::vector<DocId>> GetListOfDocumentsForWord(const std::string& word) const;

    // Создает и возвращает объект транзакции
    // Result с уникальным указателем на транзакцию или ошибка, если транзакция уже активна.
    Result<std::unique_ptr<UpdateTransaction>> BeginTransaction();

  private:
    friend class UpdateTransaction;

    void Apply(InvertedIndex&& new_state);

    InvertedIndex index_;

    bool transaction_active = false;
};

} // namespace lab5::documents
