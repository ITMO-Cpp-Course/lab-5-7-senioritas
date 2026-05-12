#pragma once
#include "Document.hpp"
#include <string>
#include <vector>
namespace lab5::documents
{
class DocumentBuilder
{
  public:
    static Document Build(size_t id, const std::string& name, std::string content);

    static std::vector<std::string> Tokenize(const std::string& text);

    static std::string Normalize(std::string word);
};
} // namespace lab5::documents
