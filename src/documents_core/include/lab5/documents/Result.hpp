#pragma once
#include <expected>
#include <string>

namespace lab5::documents
{

// Коды ошибок для классификации
enum class ErrorCode
{
    DocumentAlreadyExists,
    DocumentNotFound,
    TransactionAlreadyActive,
    InternalError
};

// Структура ошибки, объединяющая код и текст
struct IndexError
{
    ErrorCode code;
    std::string message;
};

// Основной тип Result на базе std::expected
template <typename T> using Result = std::expected<T, IndexError>;

} // namespace lab5::documents
