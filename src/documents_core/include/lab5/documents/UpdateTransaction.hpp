#pragma once

#include "IndexStore.hpp"
#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <set>
#include <string>
#include <vector>

namespace lab5::documents
{

class UpdateTransaction
{
  public:
    // Конструктор создает локальную копию данных из IndexStore
    // Здесь происходит инициализация временных транзакций
    UpdateTransaction(IndexStore& store);

    // Если Commit() не был вызван, изменения в transaction и transaction_docid
    // удалятся вместе с этим объектом, а IndexStore разблокируется
    ~UpdateTransaction();

    // Запрещаем копирование транзакции
    UpdateTransaction(const UpdateTransaction&) = delete;            // от UpdateTransaction tx2 = tx1;
    UpdateTransaction& operator=(const UpdateTransaction&) = delete; // от tx2 = tx1

    // Добавление документа во временную транзакцию.
    Result<void> AddDocument(size_t doc_id, const std::vector<std::string>& words);

    // Удаление документа из временной транзакции.
    Result<void> RemoveDocument(size_t doc_id);

    // Фиксация изменений Commit.
    // Переносит данные из transaction и transaction_docid в основной IndexStore.
    Result<void> Commit();

  private:
    IndexStore& store_ref; // Ссылка на основной склад IndexStore

    // Временная копия индекса (её transaction)
    InvertedIndex transaction;

    bool is_committed = false; // Флаг, был ли вызван Commit
};

} // namespace lab5::documents
