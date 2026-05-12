#include <cstddef>
#include <lab5/documents/Document.hpp>
#include <lab5/documents/DocumentBuilder.hpp>
#include <lab5/documents/IndexStore.hpp>
#include <lab5/documents/InvertedIndex.hpp>
#include <lab5/documents/Result.hpp>
#include <lab5/documents/UpdateTransaction.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{

void IndexStore::Apply(InvertedIndex&& new_state)
{
    index_ = std::move(new_state);
}
Result<std::unique_ptr<UpdateTransaction>> IndexStore::BeginTransaction()
{
    if (transaction_active)
    {
        return std::unexpected(IndexError{ErrorCode::TransactionAlreadyActive, "Transaction already active"});
    }

    return {std::make_unique<UpdateTransaction>(*this)};
}

Result<std::pair<std::map<DocId, size_t>, size_t>> IndexStore::GetResultsForWord(const std::string& word) const
{
    if (transaction_active)
    {
        return std::unexpected{IndexError{ErrorCode::InvalidTransactionState,
                                          "Impossible to get correct result for word while transaction is active"}};
    }
    return index_.GetResultsForWord(word);
}

Result<std::vector<size_t>> IndexStore::GetListOfDocumentsForWord(const std::string& word) const
{
    if (transaction_active)
    {
        return std::unexpected{
            IndexError{ErrorCode::InvalidTransactionState,
                       "Impossible to get correct list of documents for word while transaction is active"}};
    }
    return index_.GetListOfDocumentsForWord(word);
}

}; // namespace lab5::documents
