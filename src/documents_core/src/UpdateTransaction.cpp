#include "lab5/documents/UpdateTransaction.hpp"
#include <cctype>
namespace lab5::documents
{
UpdateTransaction::UpdateTransaction(IndexStore& store) : store_ref(store)
{
    // конструктор сохраняет ссылку на хранилище
    // transaction и transaction_docid инициализируются по умолчанию (пустые)
}

UpdateTransaction::~UpdateTransaction()
{
    // если коммита не было, разблокируем хранилище
    if (!is_committed)
    {
        store_ref.SetTransactionActive(false);
    }
}

Result<void> UpdateTransaction::AddDocument(size_t doc_id, const std::vector<std::string>& words)
{
    // проверка, нельзя добавлять документы в уже закоммиченную транзакцию
    if (is_committed)
    {
        return std::unexpected(
            IndexError{ErrorCode::InternalError, "Cannot add document to already committed transaction"});
    }

    // добавляем документ во временный индекс и во временный набор ID
    transaction.AddDocument(doc_id, words);
    transaction_docid.insert(doc_id);

    return {};
}

Result<void> UpdateTransaction::RemoveDocument(size_t doc_id)
{
    // проверка, нельзя удалять документы из уже закоммиченной транзакции
    if (is_committed)
    {
        return std::unexpected(
            IndexError{ErrorCode::InternalError, "Cannot remove document from already committed transaction"});
    }

    // удаляем документ из временного индекса и из временного набора ID
    transaction.RemoveDocument(doc_id);
    transaction_docid.erase(doc_id);

    return {};
}

Result<void> UpdateTransaction::Commit()
{
    // роверка, нельзя коммитить дважды
    if (is_committed)
    {
        return std::unexpected(IndexError{ErrorCode::InternalError, "Transaction already committed"});
    }

    // применяем накопленные изменения к основному хранилищу
    store_ref.Apply(std::move(transaction), std::move(transaction_docid));

    // разблокируем хранилище и помечаем транзакцию как закоммиченную
    store_ref.SetTransactionActive(false);
    is_committed = true;

    return {};
}

}; // namespace lab5::documents
