#include <catch2/catch_all.hpp>
#include <fcntl.h>	
#include <lab5/documents/Document.hpp>
#include <lab5/documents/DocumentBuilder.hpp>
#include <lab5/documents/InvertedIndex.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstddef>
using namespace lab5::documents;
TEST_CASE("Test InvertedIndex")
{
	InvertedIndex Index;
	size_t doc_id1=1;
	size_t doc_id2=2;
	size_t doc_id3=3;
	std::vector<std::string> words1{"apple","apple","pear"};
	std::vector<std::string> words2{"apple","apple","car"};
	std::vector<std::string> words3{"apple","car","cat"};
	Index.AddDocument(doc_id1,words1);
	Index.AddDocument(doc_id2,words2);
	Index.AddDocument(doc_id3,words3);
	std::unordered_map<std::string, std::map<size_t, size_t>> example ={{"apple",{{1,2},{2,2},{3,1}}},{"pear",{{1,1}}},{"car",{{2,1},{3,1}}},{"cat",{{3,1}}}};
	REQUIRE(index_==example);
	Index.RemoveDocument(1);
	std::unordered_map<std::string, std::map<size_t, size_t>> example2 ={{"apple",{{2,2},{3,1}}},{"car",{{2,1},{3,1}}},{"cat",{{3,1}}}};
	REQUIRE(index_==example2);
	Index.RemoveDocument(2);
	std::unordered_map<std::string, std::map<size_t, size_t>> example3 ={{"apple",{{3,1}}},{"car",{{3,1}}},{"cat",{{3,1}}}};
	REQUIRE(index_==example3);
	Index.RemoveDocument(3);
	std::unordered_map<std::string, std::map<size_t, size_t>> example4={};
	REQUIRE(index_==example4);
}
