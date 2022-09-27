/**
 * Generic Hash Table (Double Hashing).
 *
 * @file hash-table.hpp
 *
 * @brief Implementation of a Generic Hash Table (Double Hashing).
 *
 * @author Liav Barsheshet
 * Contact: liavbarsheshet@gmail.com
 *
 * This implementation is free: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This implementation is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <stdlib.h>
#include <iostream>
#include "initialized-array.hpp"

#ifndef _HASH_TABLE_HPP
#define _HASH_TABLE_HPP

#define INIT_SIZE 7 // Start Size of the hash tables (Recommendation: Prime Number).
#define CONST_C 7
#define MAX_RATIO 0.75 // Ratio limit of expansion (total_elements/size).
#define MIN_RATIO 0.25 // Ratio limit of reduction (total_elements/size).
#define EXPAND_SIZE 2 // Multiply size by x (Expansion). x>1
#define REDUCE_SIZE 0.5 // Multiply size by x (Reduction). 0<x<1

namespace HTable {
    typedef enum {
        DOWN, UP
    } DIRECTION;

    typedef enum {
        EMPTY, FULL
    } CELL_STATE;

    template<typename Key, typename Value>
    class HTableCell;

    template<typename Key, typename Value, typename Number = long long int>
    class HashTable;
}

/**
 * Class: Represents Hash Table cell.
 * @tparam Key - The type/class of the key.
 * @tparam Value - The type/class of the value.
 */
template<typename Key, typename Value>
class HTable::HTableCell {
    Key key;
    Value value;
    HTable::CELL_STATE state;
public:
    /**
     * Constructor: Creates an empty table cell.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     */
    HTableCell() :
            state(EMPTY) {};

    /**
     * Constructor: Creates a full table cell from a given key and value.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @param key - The type/class of the key.
     * @param value - Specific value.
     */
    HTableCell(const Key key, const Value value) :
            key(key),
            value(value),
            state(FULL) {};

    /**
     * Copy Constructor: Creates an initialized array from an existing one.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     * @param key - The type/class of the key.
     * @param cell - Hash Table cell reference.
     */
    HTableCell(const HTableCell &cell) :
            key(cell.key),
            value(cell.value),
            state(cell.state) {};

    /**
     * Gets the key.
     * @return {Key} Returns the key.
     */
    Key GetKey() const {
        return this->key;
    };

    /**
     * Gets the value.
     * @return {Value} Returns the value.
     */
    Value GetValue() const {
        return this->value;
    };

    /**
     * Gets the cell state.
     * @return {CELL_STATE} Returns the cell state.
     */
    CELL_STATE GetCellState() const {
        return this->state;
    };

    /**
     * Updates the cell state to a given state.
     * @param state - New state.
     */
    void SetCellState(CELL_STATE state) {
        this->state = state;
    };
};

template<typename Key, typename Value>
std::ostream &operator<<(std::ostream &os, const HTable::HTableCell<Key, Value> &cell) {
    os << cell.GetKey() << ":" << cell.GetValue();
    return os;
}

/**
 * Class: Represents Hash Table (Double Hashing).
 * @tparam Key - The type/class of the key.
 * @tparam Value - The type/class of the value.
 * @tparam Number - Class/Primitive for numbers representation.
 */
template<typename Key, typename Value, typename Number>
class HTable::HashTable {
    InitArr::InitializedArray<Number, HTableCell<Key, Value> *> *elements;
    Number size;
    Number total_elements;

    bool IsPrime(Number number) { // Our Initial size is larger than 3
        if (number == 1 || number % 2 == 0 || number % 3 == 0) {
            return false;
        }
        Number div = 6;
        while (div * div - 2 * div + 1 <= number) {
            if (number % (div - 1) == 0 || number % (div + 1) == 0) {
                return false;
            }
            div += 6;
        }
        return true;
    }

    Number FindNextPrime(Number number) {
        while (!this->IsPrime(++number)) {}
        return number;
    }

    Number Hash(Key key, Number k = 0) const {
        Number new_index = (((key % this->size) + k * (1 + (key % CONST_C))) % this->size);
        return new_index;
    }

    void ReHash(DIRECTION dir) {
        Number old_size = this->size;
        if (dir == UP && this->total_elements >= (this->size * MAX_RATIO)) {
            this->size = this->FindNextPrime(floor(this->size * EXPAND_SIZE));
        } else if (dir == DOWN && this->size > INIT_SIZE && (this->total_elements) < (this->size * MIN_RATIO)) {
            this->size = this->FindNextPrime(floor(this->size * REDUCE_SIZE));;
        } else {
            return;
        }

        this->total_elements = 0;
        InitArr::InitializedArray<Number, HTableCell<Key, Value> *> *new_elements =
                new InitArr::InitializedArray<Number, HTableCell<Key, Value> *>(this->size, NULL);
        InitArr::InitializedArray<Number, HTableCell<Key, Value> *> *old_elements = this->elements;
        this->elements = new_elements;

        HTableCell<Key, Value> *elem = NULL;
        for (Number i = 0; i < old_size; ++i) {
            elem = old_elements->Get(i);
            if (!elem) {
                continue;
            }
            if (elem->GetCellState() == EMPTY) {
                delete elem;
                old_elements->Set(i, NULL);
                continue;
            }
            this->Insert(elem->GetKey(), elem->GetValue());
            delete elem;
        }
        delete old_elements;
    }

    Number FindKey(const Key &key) const {

        Number k = 0;
        Number hash = Hash(key, k);
        HTableCell<Key, Value> *elem = this->elements->Get(hash);

        while (elem && k < this->size) {
            if (elem->GetKey() == key) {
                break;
            }
            ++k;
            hash = Hash(key, k);
            elem = this->elements->Get(hash);
        }

        if (!elem || k >= this->size) {
            return -1;
        }

        if (elem->GetKey() == EMPTY) {
            return -1;
        }

        return (hash);
    }

public:
    /**
     * Constructor: Creates an empty Hash Table.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(1).
     */
    HashTable() :
            elements(new InitArr::InitializedArray<Number, HTableCell<Key, Value> *>(INIT_SIZE, NULL)),
            size(INIT_SIZE),
            total_elements(0) {}

    /**
     * Copy Constructor: Creates Hash Table from an existing one.
     * @note Worst-Time Complexity: O(n).
     * @note Worst-Space Complexity: O(n).
     */
    HashTable(const HashTable &ht) :
            elements(new InitArr::InitializedArray<Number, HTableCell<Key, Value> *>(INIT_SIZE, NULL)),
            size(ht.size),
            total_elements(ht.total_elements) {
        HTableCell<Value, Key> *elem = NULL;
        for (Number i = 0; i < this->size; ++i) {
            elem = ht.elements->Get(i);
            if (!elem) {
                continue;
            }
            if (elem->GetCellState() == EMPTY) {
                continue;
            }
            elements->Set(i) = new HTableCell<Value, Key>(elem->GetKey(), elem->GetValue());
            continue;
        }
    }

    /**
     * Constructor: Combines two Hash Table into one.
     * @note Worst-Time Complexity: O(max{n,m}).
     * @note Worst-Space Complexity: O(n+m).
     */
    HashTable(const HashTable &ht1, const HashTable &ht2) :
            elements(NULL),
            size(0),
            total_elements(0) {
        Number new_size = this->FindNextPrime(2 * (ht1.size + ht2.size));
        this->size = new_size;
        this->elements = new InitArr::InitializedArray<Number, HTableCell<Key, Value> *>(new_size, NULL);

        HTableCell<Value, Key> *elem = NULL;

        for (Number i = 0; i < ht1.size; ++i) {
            elem = ht1.elements->Get(i);
            if (!elem) {
                continue;
            }
            if (elem->GetCellState() == EMPTY) {
                continue;
            }
            this->Insert(elem->GetKey(), elem->GetValue());
        }

        for (Number i = 0; i < ht2.size; ++i) {
            elem = ht2.elements->Get(i);
            if (!elem) {
                continue;
            }
            if (elem->GetCellState() == EMPTY) {
                continue;
            }
            this->Insert(elem->GetKey(), elem->GetValue());
        }
    }

    /**
     * Destructor: Deallocates the entire Hash Table.
     * @note Without responsibility of deallocating (values & keys).
     * @note Worst-Time Complexity: O(n).
     */
    ~HashTable() {
        for (Number i = 0; i < this->size; ++i) {
            if (this->elements->Get(i)) {
                delete this->elements->Get(i);
            }
        }
        delete this->elements;
    }

    /**
     * Gets Hash Table Size.
     * @note Worst-Time Complexity: O(1).
     * @return {Number} Hash Table size.
     */
    Number GetSize() const {
        return this->size;
    }

    /**
     * Gets total elements.
     * @note Worst-Time Complexity: O(1).
     * @return {Number} Total elements.
     */
    Number GetTotalElements() const {
        return this->total_elements;
    }

    /**
     * Stores a given value in a specific key.
     * @note Worst-Time Complexity: O(n).
     * @note Average-Time Complexity: O(1).
     * @param key - Specific key.
     * @param value - Specific value.
     */
    void Insert(Key key, Value value) {
        Number is_exist = FindKey(key);
        Number hash;

        HTableCell<Key, Value> *elem = NULL;

        if (is_exist > 0) {
            hash = is_exist;
            elem = this->elements->Get(hash);
            delete elem;
            this->elements->Set(hash, new HTableCell<Key, Value>(key, value));
            return;
        }

        Number k = 0;
        hash = this->Hash(key, k);
        elem = this->elements->Get(hash);

        while (elem && k <= this->size) {
            if (elem->GetKey() == key || elem->GetCellState() == EMPTY) {
                break;
            }
            ++k;
            hash = this->Hash(key, k);
            elem = this->elements->Get(hash);
        }

        if (elem) {
            --this->total_elements;
            delete elem;
        }

        ++this->total_elements;
        this->elements->Set(hash, new HTableCell<Key, Value>(key, value));
        this->ReHash(UP);
    }

    /**
     *  Finds the value of a given key.
     * @note Worst-Time Complexity: O(n).
     * @note Average-Time Complexity: O(1).
     * @param key - Specific key.
     * @return {HTableCell<Key, Value>} Hash Table Cell if exists o.w NULL.
     */
    HTableCell<Key, Value> *Find(const Key &key) const {
        Number new_key = this->FindKey(key);

        if (new_key < 0) {
            return NULL;
        }

        HTableCell<Key, Value> *elem = this->elements->Get(new_key);

        return new HTableCell<Key, Value>(*elem);
    }

    /**
     *  Checks if a key is exists on this Hash Table.
     * @note Worst-Time Complexity: O(n).
     * @note Average-Time Complexity: O(1).
     * @param key - Specific key.
     * @return {bool} True if exists o.w false.
     */
    bool Exists(const Key &key) const {
        Number found_key = this->FindKey(key);
        return found_key > 0;
    }

    /**
     * Removes a specific key from this Hash Table.
     * @note If the key is not exists, this method will do nothing.
     * @note Worst-Time Complexity: O(n).
     * @note Average-Time Complexity: O(1).
     * @param key - Specific key.
     */
    void Remove(const Key &key) {
        Number is_exist = FindKey(key);

        if (is_exist < 0) {
            return;
        }

        HTableCell<Key, Value> *elem = this->elements->Get(is_exist);

        if (elem->GetCellState() == FULL) {
            elem->SetCellState(EMPTY);
            --this->total_elements;
            this->ReHash(DOWN);
        }
    }

    /**
     *  Finds the value of a given key.
     * @note Worst-Time Complexity: O(n).
     * @note Average-Time Complexity: O(1).
     * @param key - Specific key.
     * @return {HTableCell<Key, Value>} Hash Table Cell if exists o.w NULL.
     */
    HTableCell<Key, Value> *operator[](const Key &key) const {
        return this->Find(key);
    }


    /**
     *  Prints the hash table.
     * @note Worst-Time Complexity: O(n).
     * @note Average-Time Complexity: O(n).
     * @param os - Ostream.
     */
    std::ostream &Print(std::ostream &os) const {
        os << "{";
        if (this->total_elements > 0) {
            os << std::endl;
        }
        for (Number i = 0; i < this->size; ++i) {
            HTableCell<Key, Value> *elem = this->elements->Get(i);
            if (!elem || elem->GetCellState() == EMPTY) {
                continue;
            }
            os << (*elem) << (i == this->size - 1 ? "" : ",") << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }
};

template<typename Key, typename Value>
std::ostream &operator<<(std::ostream &os, const HTable::HashTable<Key, Value> &ht) {
    ht.Print(os);
    return os;
}

template<typename Key, typename Value>
std::ostream &operator<<(std::ostream &os, const HTable::HashTable<Key, Value> *ht) {
    ht->Print(os);
    return os;
}

#endif
