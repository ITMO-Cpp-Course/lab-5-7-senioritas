#pragma once
#include <cstddef>
#include <lab5/documents/Document.hpp>
#include <lab5/documents/Result.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::documents
{
class InvertedIndex
{
  public:
    Result<void> AddDocument(DocId doc_id, const std::vector<std::string>& words);

    Result<void> RemoveDocument(size_t doc_id);

    Result<std::pair<std::map<DocId, size_t>, size_t>> GetResultsForWord(const std::string& word) const;

    Result<std::vector<DocId>> GetListOfDocumentsForWord(const std::string& word) const;

  private:
    std::unordered_map<std::string, std::map<size_t, size_t>> index_;
};
} // namespace lab5::documents
