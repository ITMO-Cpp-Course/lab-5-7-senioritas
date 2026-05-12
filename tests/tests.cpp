#include <catch2/catch_all.hpp>
#include <cstddef>
#include <fcntl.h>
#include <lab5/documents/Document.hpp>
#include <lab5/documents/DocumentBuilder.hpp>
#include <lab5/documents/IndexStore.hpp>
#include <lab5/documents/UpdateTransaction.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using namespace lab5::documents;
TEST_CASE("Test IndexStore")
{
    IndexStore index;

    DocId doc_id1 = 1;
    DocId doc_id2 = 2;
    DocId doc_id3 = 3;

    std::vector<std::string> words1{"apple", "apple", "pear"};
    std::vector<std::string> words2{"apple", "apple", "car"};
    std::vector<std::string> words3{"apple", "car", "cat"};

    auto transaction1 = *index.BeginTransaction();
    transaction1->AddDocument(doc_id1, words1);
    REQUIRE(!index.GetListOfDocumentsForWord("apple").has_value());
    transaction1->Commit();
    REQUIRE(*index.GetListOfDocumentsForWord("apple") == std::vector<DocId>{doc_id1});
    {
        auto transaction2 = *index.BeginTransaction();
        transaction2->AddDocument(doc_id2, words2);
    }
    REQUIRE(*index.GetListOfDocumentsForWord("car") == std::vector<DocId>{});
    {
        auto transaction2 = *index.BeginTransaction();
        transaction2->AddDocument(doc_id2, words2);
        transaction2->AddDocument(doc_id3, words2);
        REQUIRE(!index.BeginTransaction().has_value());
        transaction2->Commit();
    }
    REQUIRE(*index.GetListOfDocumentsForWord("car") == std::vector<DocId>{doc_id2, doc_id3});
    auto transaction2 = *index.BeginTransaction();
    transaction2->RemoveDocument(doc_id2);
    transaction2->Commit();
    REQUIRE(*index.GetListOfDocumentsForWord("car") == std::vector<DocId>{doc_id3});
}

TEST_CASE("DocumentBuilder::Build creates document with correct fields")
{
    Document doc = DocumentBuilder::Build(42, "test.txt", "Hello World!");

    REQUIRE(doc.id == 42);
    REQUIRE(doc.name == "test.txt");
    REQUIRE(doc.content == "Hello World!");
}

TEST_CASE("DocumentBuilder::Build handles empty content")
{
    Document doc = DocumentBuilder::Build(1, "empty.txt", "");

    REQUIRE(doc.id == 1);
    REQUIRE(doc.name == "empty.txt");
    REQUIRE(doc.content.empty());
}

TEST_CASE("DocumentBuilder::Build handles empty name")
{
    Document doc = DocumentBuilder::Build(2, "", "Some content");

    REQUIRE(doc.id == 2);
    REQUIRE(doc.name.empty());
    REQUIRE(doc.content == "Some content");
}

TEST_CASE("DocumentBuilder::Build handles zero id")
{
    Document doc = DocumentBuilder::Build(0, "zero.txt", "content");

    REQUIRE(doc.id == 0);
    REQUIRE(doc.name == "zero.txt");
    REQUIRE(doc.content == "content");
}

TEST_CASE("DocumentBuilder::Tokenize splits simple words")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("hello world");

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "world");
}

TEST_CASE("DocumentBuilder::Tokenize handles punctuation")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("Hello, world! How are you?");

    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "world");
    REQUIRE(result[2] == "how");
    REQUIRE(result[3] == "are");
    REQUIRE(result[4] == "you");
}

TEST_CASE("DocumentBuilder::Tokenize handles numbers")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("Hello 123 world 456");

    REQUIRE(result.size() == 4);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "123");
    REQUIRE(result[2] == "world");
    REQUIRE(result[3] == "456");
}

TEST_CASE("DocumentBuilder::Tokenize handles multiple spaces")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("hello    world");

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "world");
}

TEST_CASE("DocumentBuilder::Tokenize handles newlines and tabs")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("hello\nworld\tfoo");

    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "world");
    REQUIRE(result[2] == "foo");
}

TEST_CASE("DocumentBuilder::Tokenize handles empty text")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("");

    REQUIRE(result.empty());
}

TEST_CASE("DocumentBuilder::Tokenize handles only punctuation")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize(".,!?;:()[]{}\"'-");

    REQUIRE(result.empty());
}

TEST_CASE("DocumentBuilder::Tokenize handles single word")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("hello");

    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == "hello");
}

TEST_CASE("DocumentBuilder::Tokenize handles leading and trailing spaces")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("  hello world  ");

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "world");
}

TEST_CASE("DocumentBuilder::Tokenize converts to lowercase")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("Hello WORLD hElLo");

    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "hello");
    REQUIRE(result[1] == "world");
    REQUIRE(result[2] == "hello");
}

TEST_CASE("DocumentBuilder::Tokenize handles mixed alphanumeric")
{
    std::vector<std::string> result = DocumentBuilder::Tokenize("abc123 def456");

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == "abc123");
    REQUIRE(result[1] == "def456");
}

TEST_CASE("DocumentBuilder::Normalize converts uppercase to lowercase")
{
    std::string result = DocumentBuilder::Normalize("HELLO");

    REQUIRE(result == "hello");
}

TEST_CASE("DocumentBuilder::Normalize leaves lowercase unchanged")
{
    std::string result = DocumentBuilder::Normalize("hello");

    REQUIRE(result == "hello");
}

TEST_CASE("DocumentBuilder::Normalize handles mixed case")
{
    std::string result = DocumentBuilder::Normalize("HeLlO WoRlD");

    REQUIRE(result == "hello world");
}

TEST_CASE("DocumentBuilder::Normalize handles numbers")
{
    std::string result = DocumentBuilder::Normalize("Hello123");

    REQUIRE(result == "hello123");
}

TEST_CASE("DocumentBuilder::Normalize handles empty string")
{
    std::string result = DocumentBuilder::Normalize("");

    REQUIRE(result.empty());
}

TEST_CASE("Integration: Build and Tokenize work together")
{
    Document doc = DocumentBuilder::Build(1, "test.txt", "Hello World! This is a test.");
    std::vector<std::string> tokens = DocumentBuilder::Tokenize(doc.content);

    REQUIRE(tokens.size() == 6);
    REQUIRE(tokens[0] == "hello");
    REQUIRE(tokens[1] == "world");
    REQUIRE(tokens[2] == "this");
    REQUIRE(tokens[3] == "is");
    REQUIRE(tokens[4] == "a");
    REQUIRE(tokens[5] == "test");
}

TEST_CASE("UpdateTransaction - успешное добавление документа", "[transaction]")
{
    IndexStore store;

    auto txResult = store.BeginTransaction();
    REQUIRE(txResult.has_value());
    auto& tx = *txResult.value();

    std::vector<std::string> words = {"hello", "world"};
    auto addResult = tx.AddDocument(1, words);
    REQUIRE(addResult.has_value());

    auto commitResult = tx.Commit();
    REQUIRE(commitResult.has_value());

    auto searchResult = store.GetResultsForWord("hello");
    REQUIRE(searchResult.has_value());
    REQUIRE(searchResult->first.size() == 1);
    REQUIRE(searchResult->first[1] == 1);
}

TEST_CASE("UpdateTransaction - автоматический откат при разрушении", "[transaction]")
{
    IndexStore store;

    {
        auto txResult = store.BeginTransaction();
        REQUIRE(txResult.has_value());
        auto& tx = *txResult.value();

        auto addResult = tx.AddDocument(1, {"test"});
        REQUIRE(addResult.has_value());
        // нет Commit() - откат при разрушении
    }

    auto searchResult = store.GetResultsForWord("test");
    REQUIRE(searchResult.has_value());
    REQUIRE(searchResult->first.empty());
}

TEST_CASE("UpdateTransaction - ошибка при двойном Commit", "[transaction]")
{
    IndexStore store;

    auto txResult = store.BeginTransaction();
    REQUIRE(txResult.has_value());
    auto& tx = *txResult.value();

    auto add = tx.AddDocument(1, {"x"});
    REQUIRE(add.has_value());

    auto commit1 = tx.Commit();
    REQUIRE(commit1.has_value());

    auto commit2 = tx.Commit();
    REQUIRE_FALSE(commit2.has_value());
    REQUIRE(commit2.error().code == ErrorCode::TransactionAlreadyCommitted);
}

TEST_CASE("UpdateTransaction - удаление документа через транзакцию", "[transaction]")
{
    IndexStore store;

    {

        auto txResult = store.BeginTransaction();
        REQUIRE(txResult.has_value());
        auto tx = std::move(txResult.value());
        REQUIRE(tx->AddDocument(42, {"remove_me"}).has_value());
        REQUIRE(tx->RemoveDocument(42).has_value());
        REQUIRE(tx->Commit().has_value());
    }
    {
        auto result = store.GetResultsForWord("remove_me");
        REQUIRE(result.has_value());
        REQUIRE(result->first.empty());
    }
}
TEST_CASE("Транзакция с ошибкой", "[transaction]")
{
    IndexStore store;

    auto txResult = store.BeginTransaction();
    REQUIRE(txResult.has_value());
    auto& tx = *txResult.value();

    REQUIRE(tx.AddDocument(1, {"hello"}).has_value());
    REQUIRE(tx.Commit().has_value());

    auto result = tx.AddDocument(2, {"world"});

    REQUIRE_FALSE(result.has_value());
}
