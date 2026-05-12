#include "lab5/documents/UpdateTransaction.hpp"
#include <cctype>
namespace lab5::documents
{
UpdateTransaction::UpdateTransaction(IndexStore& store) : store_ref(store)
{
    store_ref.transaction_active = true;
    transaction = store_ref.index_;
}

UpdateTransaction::~UpdateTransaction()
{
    if (!is_committed)
    {
        store_ref.transaction_active = false;
    }
}

Result<void> UpdateTransaction::AddDocument(size_t doc_id, const std::vector<std::string>& words)
{
    if (is_committed)
    {
        return std::unexpected(
            IndexError{ErrorCode::InternalError, "Cannot add document to already committed transaction"});
    }

    return transaction.AddDocument(doc_id, words);
}

Result<void> UpdateTransaction::RemoveDocument(size_t doc_id)
{
    if (is_committed)
    {
        return std::unexpected(
            IndexError{ErrorCode::InternalError, "Cannot remove document from already committed transaction"});
    }

    return transaction.RemoveDocument(doc_id);
}

Result<void> UpdateTransaction::Commit()
{
    // проверка, нельзя коммитить дважды
    if (is_committed)
    {
        return std::unexpected(IndexError{ErrorCode::InternalError, "Transaction already committed"});
    }

    // применяем накопленные изменения к основному хранилищу
    store_ref.Apply(std::move(transaction));

    store_ref.transaction_active = false;
    is_committed = true;

    return {};
}

}; // namespace lab5::documents
