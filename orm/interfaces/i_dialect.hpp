#pragma once
// orm/core/i_dialect.hpp
// Responsibility: Define the contract for SQL dialect-specific syntax generation.
// This allows the ORM engine to remain database-agnostic while supporting multiple backends.

#include <string>
#include "../core/result.hpp"

namespace orm { struct TableSchema; }

namespace orm {

  /// @brief Abstract base class defining the SQL translation layer (The Dialect).
  /// @details Acts as a Strategy Pattern interface.
  class IDialect {
    public:
      virtual ~IDialect() = default;

      /// @brief Safely translates and wraps an identifier (table or column name) to prevent SQL injection and keyword clashes.
      /// @param name The raw identifier string.
      /// @return std::string The safely quoted identifier.
      virtual std::string quote_identifier(const std::string& name) const = 0;

      /**
      * @brief Generates the Data Definition Language (DDL) statement to construct a table.
      * @param schema The programmatic representation of the table's structure.
      * @return std::string The complete CREATE TABLE SQL string.
      */
      virtual std::string create_table_sql(const TableSchema& schema) const = 0;

      /**
      * @brief Generates the dialect-specific query to check for a table's existence.
      * @param table_name The raw name of the table to look for.
      * @return std::string The SQL query string to execute.
      */
      virtual std::string table_exists_sql(const std::string& table_name) const = 0;

      /**
      * @brief Interprets the raw ResultSet returned by table_exists_sql().
      * @details Since different engines return existence checks differently (e.g., a boolean
      * column vs. a count of rows), this method centralizes the parsing logic.
      * @param rs The query result containing the existence data.
      * @return true if the table exists, false otherwise.
      */
      virtual bool parse_exists_result(const ResultSet& rs) const = 0;

      /**
      * @brief Generates the parameterized query placeholder for prepared statements.
      * @details Crucial for preventing SQL injection.
      * @param index The 1-based index of the parameter in the query string.
      * @return std::string The parameter placeholder.
      */
      virtual std::string bind_parameter(int index) const = 0;

      /**
      * @brief Exposes the underlying type mapping strategy for this dialect.
      * @details Resolves how C++ native types (e.g., int, bool, std::string) map to
      * SQL column types (e.g., INTEGER, BOOLEAN, VARCHAR) during migrations.
      * @return const ITypeMapper& A reference to the dialect's specific type mapper.
      */
      virtual const class ITypeMapper& type_mapper() const = 0;
  };
}
