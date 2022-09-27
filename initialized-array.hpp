/**
 * Generic Initialized Array.
 *
 * @file initialized-array.hpp
 *
 * @brief Implementation of a Generic Initialized Array.
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

#ifndef _INITIALIZED_ARRAY_HPP
#define _INITIALIZED_ARRAY_HPP
namespace InitArr {
    template<typename Value, typename Number>
    class InitializedArray;
}

/**
 * Class: Represents an initialized array.
 * @tparam Value - The type/class of the value.
 * @tparam Number - Class/Primitive number type for index representation.
 */
template<typename Value, typename Number>
class InitArr::InitializedArray {
    Value *values;
    Number *short_cuts;
    Number *init_indexes;
    Number top;
    Number length;
    Value def;

    bool IsInitialized(const Number &index) {
        if (index >= this->length || index < 0) {
            throw std::out_of_range("Index out of range.");
        }
        if (this->top == 0) return false;
        return (this->short_cuts[index] < this->top &&
                this->short_cuts[index] >= 0 &&
                this->init_indexes[this->short_cuts[index]] == index);
    }

public:
    /**
     * Constructor: Creates an initialized array.
     * @note Worst-Time Complexity: O(1).
     * @note Worst-Space Complexity: O(3n).
     * @param length - The length of the array.
     * @param def - The default value which all values will be initialized to.
     */
    InitializedArray(Number length, Value def) :
            values(new Value[length]),
            short_cuts(new Number[length]),
            init_indexes(new Number[length]),
            top(0),
            length(length),
            def(def) {}

    /**
     * Copy Constructor: Creates an initialized array from an existing one.
     * @note Worst-Time Complexity: O(top) <= O(n).
     * @note Worst-Space Complexity: O(3n).
     * @param arr - The array reference.
     */
    InitializedArray(const InitializedArray<Value, Number> &arr) :
            values(new Value[arr.length]),
            short_cuts(new Number[arr.length]),
            init_indexes(new Number[arr.length]),
            top(arr.top),
            length(arr.length),
            def(arr.def) {

        for (Number i = 0; i < this->top; i++) {
            this->values[i] = arr.values[i];
            this->short_cuts[i] = arr.short_cuts[i];
            this->init_indexes[i] = arr.init_indexes[i];
        }
    }

    /**
     * Destructor: Deallocates the entire array.
     * @note Without responsibility of the content(items).
     * @note Worst-Time Complexity: O(1).
     */
    ~InitializedArray() {
        delete[] this->values;
        delete[] this->short_cuts;
        delete[] this->init_indexes;
    }

    /**
     * Gets the element at a specific index.
     * @note Worst-Time Complexity: O(1).
     * @param index - Specific index of an element.
     * @return {Value} Returns the element at specific index.
     */
    Value Get(const Number &index) const {
        if (this->IsInitialized(index)) {
            return this->values[index];
        }
        return this->def;
    }

    /**
     * Sets the element at a specific index.
     * @note Worst-Time Complexity: O(1).
     * @param index - Specific index of an element.
     * @param value - Specific value.
     */
    void Set(const Number &index, Value value) {
        if (!this->IsInitialized(index)) {
            this->init_indexes[this->top] = index;
            this->short_cuts[index] = this->top;
            ++this->top;
        }
        this->values[index] = value;
    };

    /**
     * Gets the default value.
     * @note Worst-Time Complexity: O(1).
     * @return {Value} Returns the default value.
     */
    Value Default() const {
        return this->def;
    }

    /**
     * Gets the length of the array.
     * @note Worst-Time Complexity: O(1).
     * @return {Number} Returns the length of the array.
     */
    Number Length() const {
        return this->length;
    }

    /**
     * Gets the element at a specific index.
     * @note Worst-Time Complexity: O(1).
     * @param index - Specific index of an element.
     * @return {Value} Returns the element at specific index.
     */
    Value operator[](const Number &index) {
        return this->Get(index);
    }
};

#endif
