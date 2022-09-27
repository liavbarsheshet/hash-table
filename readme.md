# C++ Generic Hash Table (Double Hashing)

Implementation of a Generic Hash Table (Double Hashing).

---

## Declaration

Supports >= c++11:

```c++
#include "hash-table.hpp"

auto hash_table = HTable::HashTable<typename Key, typename Value, typename Number>();
```

## Template

```c++
/**
 * Class: Represents Hash Table (Double Hashing).
 * @tparam Key - The type/class of the key.
 * @tparam Value - The type/class of the value.
 * @tparam Number - Class/Primitive for numbers representation.
 */
template<typename Key, typename Value, typename Number>
class HTable::HashTable {...}
```

## Enums

```c++
// Represents direction (For rehashing).
typedef enum {
    DOWN, UP
} DIRECTION;

// Represents cell state.
typedef enum {
    EMPTY, FULL
} CELL_STATE;
```

## Hash Table Cell

```c++
/**
 * Class: Represents Hash Table cell.
 * @tparam Key - The type/class of the key.
 * @tparam Value - The type/class of the value.
 */
template<typename Key, typename Value>
class HTable::HTableCell {
...
public:
    /**
     * Constructor: Creates an empty table cell.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     */
    HTableCell();

    /**
     * Constructor: Creates a full table cell from a given key and value.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @param key - The type/class of the key.
     * @param value - Specific value.
     */
    HTableCell(const Key key, const Value value);

    /**
     * Copy Constructor: Creates an initialized array from an existing one.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @param key - The type/class of the key.
     * @param cell - Hash Table cell reference.
     */
    HTableCell(const HTableCell &cell);

    /**
     * Gets the key.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @return {Key} Returns the key.
     */
    Key GetKey() const;

    /**
     * Gets the value.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @return {Value} Returns the value.
     */
    Value GetValue() const;

    /**
     * Gets the cell state.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @return {CELL_STATE} Returns the cell state.
     */
    CELL_STATE GetCellState() const;
};
```

## Methods

Represents Hash Table (Double Hashing).

```cpp
/**
 * Constructor: Creates an empty Hash Table.
 * @note Worst-Time Complexity: O(1).
 * @note Worst-Space Complexity: O(1).
 */
HashTable();

/**
 * Copy Constructor: Creates Hash Table from an existing one.
 * @note Worst-Time Complexity: O(n).
 * @note Worst-Space Complexity: O(n).
 */
HashTable(const HashTable &ht);

/**
 * Constructor: Combines two Hash Table into one.
 * @note Worst-Time Complexity: O(max{n,m}).
 * @note Worst-Space Complexity: O(n+m).
 */
HashTable(const HashTable &ht1, const HashTable &ht2);

/**
* Destructor: Deallocates the entire Hash Table.
* @note Without responsibility of deallocating (values & keys).
* @note Worst-Time Complexity: O(n).
*/
~HashTable();

/**
 * Gets Hash Table Size.
 * @note Worst-Time Complexity: O(1).
 * @return {Number} Hash Table size.
 */
Number GetSize() const;

/**
 * Gets total elements.
 * @note Worst-Time Complexity: O(1).
 * @return {Number} Total elements.
 */
Number GetTotalElements() const;

/**
 * Stores a given value in a specific key.
 * @note Worst-Time Complexity: O(n).
 * @note Average-Time Complexity: O(1).
 * @param key - Specific key.
 * @param value - Specific value.
 */
void Insert(Key key, Value value);

/**
 * Finds the value of a given key.
 * @note Worst-Time Complexity: O(n).
 * @note Average-Time Complexity: O(1).
 * @param key - Specific key.
 * @return {HTableCell<Key, Value>} Hash Table Cell if exists o.w NULL.
 */
HTableCell<Key, Value> *Find(const Key &key) const;

/**
 * Checks if a key is exists on this Hash Table.
 * @note Worst-Time Complexity: O(n).
 * @note Average-Time Complexity: O(1).
 * @param key - Specific key.
 * @return {bool} True if exists o.w false.
 */
bool Exists(const Key &key) const;

/**
 * Removes a specific key from this Hash Table.
 * @note If the key is not exists, this method will do nothing.
 * @note Worst-Time Complexity: O(n).
 * @note Average-Time Complexity: O(1).
 * @param key - Specific key.
 */
void Remove(const Key &key);

/**
 * Finds the value of a given key.
 * @note Worst-Time Complexity: O(n).
 * @note Average-Time Complexity: O(1).
 * @param key - Specific key.
 * @return {HTableCell<Key, Value>} Hash Table Cell if exists o.w NULL.
 */
HTableCell<Key, Value> *operator[](const Key &key) const;


/**
 * Prints the hash table.
 * @note Worst-Time Complexity: O(n).
 * @note Average-Time Complexity: O(n).
 * @param os - OS stream.
 */
std::ostream &Print(std::ostream &os) const;
```

## Author

[Liav Barsheshet, LBDevelopments](https://github.com/liavbarsheshet)

## License

[MIT](LICENSE)
