#include "lab5/documents/Document.hpp"
#include <stdexcept>
#include <string>

void DocumentStorage::Save(Document&& doc) {
   DocId id = doc.id;
    data_[id] = std::move(doc);
}

const Document& DocumentStorage::Get(DocId id) const {
    auto it = data_.find(id);

    if (it == data_.end()) {
        throw std::out_of_range("DocumentStorage: Document with ID " + std::to_string(id) + " not found.");
    }
    return it->second;
}

void DocumentStorage::Remove(DocId id) {
    // Удаление из unordered_map по ключу
    data_.erase(id);
}