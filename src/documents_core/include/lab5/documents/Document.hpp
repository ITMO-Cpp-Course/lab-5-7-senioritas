#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>
namespace lab5::documents
{
using DocId = size_t;

struct Document
{
    DocId id;
    std::string name;
    std::string content;
};

class DocumentStorage
{
  public:
    // Добавляет документ в хранилище, забирая владение строками (std::move)
    void Save(Document&& doc);

    // Позволяет получить документ по ID (например, для отображения названия в результатах)
    const Document& Get(DocId id) const;

    void Remove(DocId id);

  private:
    std::unordered_map<DocId, Document> data_;
};
}
