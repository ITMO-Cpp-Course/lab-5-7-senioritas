#include <cstddef>
#include <lab5/documents/Document.hpp>
#include <lab5/documents/DocumentBuilder.hpp>
#include <lab5/documents/InvertedIndex.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{

void InvertedIndex::AddDocument(size_t doc_id, const std::vector<std::string>& words)
{
    RemoveDocument(doc_id);
    std::map<std::string, size_t> words_counter;
    for (auto w : words)
    {
        words_counter[w] += 1;
    }
    for (auto w : words_counter)
    {
        index_[w.first][doc_id] = w.second;
    }
}
void InvertedIndex::RemoveDocument(size_t doc_id)
{
    for (auto& i : index_)
    {
        i.second.erase(doc_id);
        if (i.second.empty())
        {
            index_.erase(i.first);
        }
    }
}
std::pair<std::map<size_t, size_t>, size_t> InvertedIndex::GetResultsForWord(const std::string& word) const
{
    size_t cnt = 0;
    auto it = index_.find(word);
    if (it == index_.end())
    {
        return {std::map<size_t, size_t>{}, 0};
    }
    for (auto [id, c] : it->second)
    {
        cnt += c;
    }
    return {it->second, cnt};
}

std::vector<size_t> InvertedIndex::GetListOfDocumentsForWord(const std::string& word) const
{
    std::vector<size_t> v;
    auto it = index_.find(word);
    if (it == index_.end())
    {
        return std::vector<size_t>{};
    }
    for (auto [id, c] : it->second)
    {
        v.push_back(id);
    }
    return v;
}

}; // namespace lab5::documents
