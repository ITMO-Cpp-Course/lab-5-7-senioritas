#pragma once
#include <cstddef>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{
class InvertedIndex
{
  public:
    void AddDocument(size_t doc_id, const std::vector<std::string>& words);

    void RemoveDocument(size_t doc_id);

    std::pair<std::map<size_t, size_t>, size_t> GetResultsForWord(std::string word);

    std::vector<size_t> GetListOfDocementsForWord(std::string word);

  private:
    std::unordered_map<std::string, std::map<size_t, size_t>> index_;
};
} // namespace lab5::documents
