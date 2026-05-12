#pragma once
#include <expected>
#include <string>

namespace lab5::documents
{

enum class ErrorCode
{
    DocumentAlreadyExists,
    DocumentNotFound,
    TransactionAlreadyActive,
    InternalError,
    TransactionAlreadyCommitted,
    InvalidTransactionState
};

struct IndexError
{
    ErrorCode code;
    std::string message;
};

// Основной тип Result на базе std::expected
template <typename T> using Result = std::expected<T, IndexError>;

} // namespace lab5::documents
