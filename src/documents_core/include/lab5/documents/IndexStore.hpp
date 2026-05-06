#pragma once

#include "InvertedIndex.hpp"
#include "Result.hpp"
#include "UpdateTransaction.hpp"
#include <set>
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace lab5::documents {

//Класс IndexStore — владелец стабильного состояния индекса - данные никогда не находятся в процессе изменения.
//В программе может быть много временных объектов или функций, которые обрабатывают текст.
//Можно сказать, что это единственное место, где лежат стопроцентно верные данные.

class IndexStore {
public:
    IndexStore() = default;

    // Запрещаем копирование хранилища, чтобы избежать дублирования данных
    IndexStore(const IndexStore&) = delete;
    IndexStore& operator=(const IndexStore&) = delete;

    //Выполняет поиск слова в подтвержденном индексе
    //возвращает Result с данными (мапа и общее кол-во) или IndexError
    Result<std::pair<std::map<size_t, size_t>, size_t>> GetResultsForWord(const std::string& word) const;

    //Возвращает список ID документов для слова
    Result<std::vector<size_t>> GetListOfDocumentsForWord(const std::string& word) const;

    //Создает и возвращает объект транзакции
    //Result с уникальным указателем на транзакцию или ошибка, если транзакция уже активна.

    Result<std::unique_ptr<UpdateTransaction>> BeginTransaction();

private:
    // Даем транзакции доступ к приватным методам Apply и SetTransactionActive
    friend class UpdateTransaction;

    //Атомарно обновляет индекс (вызывается только при Commit).
    void Apply(InvertedIndex transaction, std::set<size_t> transaction_docid);

    //Устанавливает флаг активности транзакции.
    void SetTransactionActive(bool active) { transaction_active = active; }

    // Основные данные (стабильная версия)
    InvertedIndex index_;
    std::set<size_t> approved_transaction_docid;

    // Состояние системы
    bool transaction_active = false;
};

} // namespace lab5::documents