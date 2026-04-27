#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstddef>
#include <lab5/documents/Document.hpp>
#include <lab5/documents/DocumentBuilder.hpp>
#include <lab5/documents/InvertedIndex.hpp>

namespace lab5::documents
{
void InvertedIndex::AddDocument(size_t doc_id, const std::vector<std::string>& words){
	std::map<std::string, size_t> words_counter;
	for (auto w:words){
		words_counter[w]+=1;
	}
	for (auto w:words_counter){
		index_[w.first][doc_id]=w.second;
	}
}
void InvertedIndex::RemoveDocument(size_t doc_id){
	for (auto i:index_){
		if (i.second.find(doc_id)!=i.second.end()){
			i.second.erase(doc_id);
		}
	}
}

};
