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
    }
}
std::pair<std::map<size_t, size_t>, size_t> InvertedIndex::GetResultsForWord(std::string word)
{
    size_t cnt = 0;
    for (auto i : index_[word])
    {
        cnt += i.second;
    }
    return {index_[word], cnt};
}

std::vector<size_t> InvertedIndex::GetListOfDocementsForWord(std::string word)
{
    std::vector<size_t> v;
    for (auto i : index_[word])
    {
        v.push_back(i.first);
    }
    return v;
}

}; // namespace lab5::documents
