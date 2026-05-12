#pragma once
#include <string>
namespace lab5::documents
{
using DocId = size_t;

struct Document
{
    DocId id;
    std::string name;
    std::string content;
};
} // namespace lab5::documents
