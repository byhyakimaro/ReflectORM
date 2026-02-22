#pragma once
// orm/core/result.hpp
// Responsibility: Define an engine-agnostic data structure for query results.
// This acts as a DTO (Data Transfer Object) to decouple Drivers.

#include <cstddef>
#include <string>
#include <vector>
#include <map>

namespace orm {

  /// @brief A single database row represented as a column-name -> value map.
  using Row = std::map<std::string, std::string>;

  /// @brief ResultSet acts as a lightweight container for database rows.
  /// @details Acts as the primary architectural boundary between low-level database Drivers and the ORM.
  struct ResultSet {
    std::vector<Row> rows;

    /// @brief Returns a mutable iterator to the sequence of rows.
    /// @details Exposing standard iterators satisfies the C++ Range concept, enabling seamless integration with loops.
    auto begin()  { return rows.begin(); }
    auto end()    { return rows.end(); }

    /// @brief Returns a constant (read-only) iterator to the sequence of rows.
    /// @details Enforces strict const-correctness. Providing const overloads ensures memory safety against accidental mutations.
    auto begin() const { return rows.begin(); }
    auto end() const   { return rows.end(); }

    /// @brief Checks if the database query returned an empty result set.
    /// @details Semantically expresses the intent to check for data "existence" rather than quantifying it (O(1) complexity).
    bool empty() const { return rows.empty(); }

    /// @brief Retrieves the exact number of rows fetched by the query.
    /// @details Encapsulates the internal implementation (std::vector) from the caller, adhering to the Law of Demeter.
    size_t size() const { return rows.size(); }
  };

}
