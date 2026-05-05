#include <cstddef>
#include <expected>
#include <lab5/documents/Document.hpp>
#include <lab5/documents/DocumentBuilder.hpp>
#include <lab5/documents/IndexStore.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{

std::expected<void, std::string> IndexStore::AddDocument(size_t doc_id, const std::vector<std::string>& words)
{
    if (transaction_docid.count(doc_id))
    {
        if (approved_transaction_docid.count(doc_id))
        {
            return std::unexpected("This document already exists and confirmed.");
        }
        return std::unexpected("This document already exists but not confirmed. Do not forget to commit changes!");
    }
    transaction_docid.insert(doc_id);
    std::map<std::string, size_t> words_counter;
    for (auto w : words)
    {
        words_counter[w] += 1;
    }
    for (auto w : words_counter)
    {
        transaction[w.first][doc_id] = w.second;
    }
    return {};
}
std::expected<void, std::string> IndexStore::RemoveDocument(size_t doc_id)
{
    if (!transaction_docid.count(doc_id))
    {
        if (!approved_transaction_docid.count(doc_id))
        {
            return std::unexpected("This document does not exist!");
        }
        return std::unexpected("This document does not exist among unconfirmed documents, but exist among confirmed "
                               "documents. You have already removed it, just commit changes!");
    }
    transaction_docid.erase(doc_id);
    for (auto it = transaction.begin(); it != transaction.end();)
    {
        it->second.erase(doc_id);
        if (it->second.empty())
        {
            it = transaction.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return {};
}
std::expected<std::pair<std::map<size_t, size_t>, size_t>, std::string> IndexStore::GetResultsForWord(
    const std::string& word) const
{
    if (!index_.count(word))
    {
        if (transaction.count(word))
        {
            return std::unexpected("This word does not exist among the confirmed changes. You can commit changes to "
                                   "see the usage of this word.");
        }
        else
        {
            return std::unexpected("This word is not used.");
        }
    }
    size_t cnt = 0;
    auto it = index_.find(word);
    for (auto [id, c] : it->second)
    {
        cnt += c;
    }
    return std::pair<std::map<size_t, size_t>, size_t>{it->second, cnt};
}

std::expected<std::vector<size_t>, std::string> IndexStore::GetListOfDocumentsForWord(const std::string& word) const
{
    if (!index_.count(word))
    {
        if (transaction.count(word))
        {
            return std::unexpected("This word does not exist among the confirmed changes. You can commit changes to "
                                   "see the usage of this word.");
        }
        else
        {
            return std::unexpected("This word is not used.");
        }
    }
    std::vector<size_t> v;
    auto it = index_.find(word);
    for (auto [id, c] : it->second)
    {
        v.push_back(id);
    }
    return v;
}

}; // namespace lab5::documents
