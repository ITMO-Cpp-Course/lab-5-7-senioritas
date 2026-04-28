#include "lab5/documents/DocumentBuilder.hpp"
#include <cctype>
namespace lab5::documents
{
Document DocumentBuilder::Build(size_t id, const std::string& name, std::string content)
{
    Document doc;
    doc.id = id;
    doc.name = name;
    doc.content = content;
    return doc;
}

std::vector<std::string> DocumentBuilder::Tokenize(const std::string& text)
{
    std::vector<std::string> tokens;
    std::string word;

    for (char c : text)
    {
        if (std::isalnum(static_cast<unsigned char>(c)))
        { // если английская буква или число
            word += c;
        }
        else if (!word.empty())
        {
            tokens.push_back(Normalize(word)); // добаляем в итоговый вектор
            word.clear();
        }
    }
    if (!word.empty())
    {
        tokens.push_back(Normalize(word));
    }
    return tokens;
}

std::string DocumentBuilder::Normalize(std::string word)
{
    for (char& c : word)
    {
        c = static_cast<char>(std::tolower(c));
    }
    return word;
}
}; // namespace lab5::documents
