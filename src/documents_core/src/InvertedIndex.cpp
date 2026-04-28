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
        if (index_[w.first].find(doc_id) != index_[w.first].end())
        {
            index_[w.first][doc_id] = w.second;
        }
        else
        {
            cout << "This document already exists" << endl;
        }
    }
}
void InvertedIndex::RemoveDocument(size_t doc_id)
{
    for (auto& i : index_)
    {
        i.second.erase(doc_id);
        if (i.second = std::map<size_t, size_t>{})
        {
            index_.erase(i.first);
        }
    }
}
std::pair<std::map<size_t, size_t>, size_t> InvertedIndex::GetResultsForWord(const std::string& word) const
{
    size_t cnt = 0;
    if (index_.find(word) == index_.end())
    {
        cout << "There is not this word" << endl;
        return std::pair<std::map<size_t, size_t>, size_t>{{}, 0};
    }
    for (auto i : index_[word])
    {
        cnt += i.second;
    }
    return {index_[word], cnt};
}

std::vector<size_t> InvertedIndex::GetListOfDocumentsForWord(const std::string& word) const
{
    if (index_.find(word) == index_.end())
    {
        cout << "There is not this word" << endl;
        return std::vector<size_t>{};
    }
    std::vector<size_t> v;
    for (auto i : index_[word])
    {
        v.push_back(i.first);
    }
    return v;
}

}; // namespace lab5::documents
