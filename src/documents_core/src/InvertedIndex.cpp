#include <lab5/documents/Document.hpp>
#include <lab5/documents/InvertedIndex.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{

Result<void> InvertedIndex::AddDocument(DocId doc_id, const std::vector<std::string>& words)
{

    for (auto& [word, idx_map] : index_)
    {
        if (idx_map.count(doc_id))
        {
            return std::unexpected{IndexError{ErrorCode::DocumentAlreadyExists,
                                              "The document " + std::to_string(doc_id) + " already exists."}};
        }
    }
    std::map<std::string, size_t> words_counter;
    for (const auto& w : words)
    {
        words_counter[w] += 1;
    }
    for (const auto& [word, cnt] : words_counter)
    {
        index_[word][doc_id] = cnt;
    }
    return {};
}
Result<void> InvertedIndex::RemoveDocument(DocId doc_id)
{
    int deletions = 0;
    for (auto it = index_.begin(); it != index_.end();)
    {
        if (it->second.count(doc_id))
        {
            ++deletions;
        }
        it->second.erase(doc_id);
        if (it->second.empty())
        {
            it = index_.erase(it);
        }
        else
        {
            ++it;
        }
    }
    if (deletions == 0)
    {
        return std::unexpected{
            IndexError{ErrorCode::DocumentNotFound, "There is no document with index " + std::to_string(doc_id)}};
    }
    return {};
}
Result<std::pair<std::map<DocId, size_t>, size_t>> InvertedIndex::GetResultsForWord(const std::string& word) const
{
    size_t cnt = 0;
    auto it = index_.find(word);
    if (it == index_.end())
    {
        return {std::pair{std::map<DocId, size_t>{}, 0}};
    }
    for (auto [id, c] : it->second)
    {
        cnt += c;
    }
    return {std::pair{it->second, cnt}};
}

Result<std::vector<DocId>> InvertedIndex::GetListOfDocumentsForWord(const std::string& word) const
{
    std::vector<DocId> v;
    auto it = index_.find(word);
    if (it == index_.end())
    {
        return {v};
    }
    for (auto [id, c] : it->second)
    {
        v.push_back(id);
    }
    return {v};
}

}; // namespace lab5::documents
