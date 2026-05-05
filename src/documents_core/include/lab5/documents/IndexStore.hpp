#pragma once
#include <cstddef>
#include <expected>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{
class IndexStore
{
  public:
    std::expected<void, std::string> AddDocument(size_t doc_id, const std::vector<std::string>& words);

    std::expected<void, std::string> RemoveDocument(size_t doc_id);

    std::expected<std::pair<std::map<size_t, size_t>, size_t>, std::string> GetResultsForWord(
        const std::string& word) const;

    std::expected<std::vector<size_t>, std::string> GetListOfDocumentsForWord(const std::string& word) const;

    // временая переменная - текущее состояние транзакцакции, там находятся в том числе те последние изменения, которых
    // нет в index_. Это самая актуальная версия index_, но еще не прошедшая commit(). Находится в public, чтобы
    // UpdateTransaction мог проталкивать её с помощью commit()
    std::unordered_map<std::string, std::map<size_t, size_t>> transaction;

    // перечислены id всех документов, которые добавлены для текущего состояния транзакции.
    std::set<size_t> transaction_docid;

    // перечислены id тех документов, которые находятся в index_.
    std::set<size_t> approved_transaction_docid;

    std::unordered_map<std::string, std::map<size_t, size_t>> index_;
};
} // namespace lab5::documents
