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
    UpdateTransaction(IndexStore& store);

    ~UpdateTransaction();

    UpdateTransaction(const UpdateTransaction&) = delete;            // от UpdateTransaction tx2 = tx1;
    UpdateTransaction& operator=(const UpdateTransaction&) = delete; // от tx2 = tx1

    Result<void> AddDocument(size_t doc_id, const std::vector<std::string>& words);

    Result<void> RemoveDocument(size_t doc_id);

    Result<void> Commit();

  private:
    IndexStore& store_ref;

    InvertedIndex transaction;

    bool is_committed = false; // Флаг, был ли вызван Commit
};

} // namespace lab5::documents
