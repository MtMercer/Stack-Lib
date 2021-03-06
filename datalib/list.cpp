#include <iostream>
#include "list.h"

using namespace std;

template<class T>
bool List<T>::addSpace(int idx) {
    // Duplicate if full
    if (full()) {
        if (!duplicateDataSize()) {
            // Cancel the operation if it failed
            return false;
        }
    }

    // Extends the array until the size is good
    duplicateDataSizeToIdx(idx);

    // Sends the rest of the elements to the right of the index
    int i = count;
    do {
        data[i + 1] = data[i];
    } while (i-- >= idx);

    return true;
}

template<class T>
bool List<T>::removeSpace(int idx) {
    // Sends everything to the left from the index
    while (idx++ < count) {
        data[idx] = data[idx + 1];
    }

    return true;
}

template<class T>
bool List<T>::duplicateDataSize() {
    // Allocate the new array
    T *newArray = allocateArray(size * 2);

    // Cancel the operation if failed to allocate
    if (newArray == nullptr) {
        return false;
    }

    // Copy the content of data to the new array
    for (int i = 0; i <= count; i++) {
        newArray[i] = data[i];
    }

    // Delete old data
    delete[] data;

    // Shift the pointers
    data = newArray;

    // Duplicate data size
    size *= 2;

    // Returns success
    return true;
}

template<class T>
bool List<T>::duplicateDataSizeToIdx(int idx) {
    // While not successful
    while (idx >= size) {
        // If it failed to duplicate, cancel the operation
        if (!duplicateDataSize()) {
            return false;
        }
    }

    return true;
}

template<class T>
T *List<T>::allocateArray(int size) {
    return new T[size];
}

template<class T>
List<T>::List(int initialSize) {
    // Setup internal variables
    size = initialSize;
    count = -1;
    data = allocateArray(size);

}

template<class T>
bool List<T>::add(int idx, T el) {
    // Duplicate if full
    if (full()) {
        if (!duplicateDataSize()) {
            // Cancel the operation if it failed
            return false;
        }
    }

    // If a shift must be made
    if (idx <= count) {
        if (!addSpace(idx)) {
            // Cancel the operation if it failed
            return false;
        }
    } else if (idx > count + 1) {
        // Move the index to the last pos of the list
        cerr << "Index to add in the list too large: " << idx << ". Using " << count + 1 << " index instead." << endl;
        idx = count + 1;
    }

    // Adds the el and adds to count
    data[idx] = el;
    count += 1;

    // Returns success
    return true;
}

template<class T>
T List<T>::remove(int idx) {
    T removedEl;

    if (idx > count) {
        // Cancel the operation if the index is invalid
        cerr << "Can't remove from index " << idx << ". The last index is " << count << "." << endl;
        return removedEl;
    }

    // Keeps the future removed el to return it
    removedEl = data[idx];

    // If the removed el isn't the last, a shift must be made
    if (idx != count) {
        removeSpace(idx);
    }

    // Decrease el count
    count -= 1;

    return removedEl;
}

template<class T>
bool List<T>::empty() {
    return count == -1;
}

template<class T>
bool List<T>::full() {
    return count + 1 == size;
}

template<class T>
void List<T>::printList() {
    for (int i = 0; i <= count; i++) {
        cout << " | " << data[i] << " | ";
    }
    cout << endl;
}

template<class T>
T List<T>::update(int idx, T newEl) {
    T updatedEl;

    if (idx > count) {
        // Cancel the operation if the index is invalid
        cerr << "Can't update from index " << idx << ". The last index is " << count << "." << endl;
        return updatedEl;
    }

    // Update the element and returns the updated element
    updatedEl = data[idx];
    data[idx] = newEl;
    return updatedEl;
}

template<class T>
bool List<T>::addSorted(T el) {
    // Sort the array first
    sort();

    // Finds where the new el should be placed
    int sortedIndex = 0;
    int i = 0;
    while (el > data[i]) {
        i += 1;
    }
    sortedIndex = i;

    // Adds the element to the right index
    add(sortedIndex, el);

    return true;
}

template<class T>
void List<T>::sort() {
    for (int i = 1; i <= count; i++) {
        T idx = data[i];
        int j = i;
        while (j > 0 && data[j - 1] > idx) {
            data[j] = data[j - 1];
            j -= 1;
        }
        data[j] = idx;
    }
}

// Explicit instantiations of all the templates used in the file
template
class List<int>;

template
class List<string>;
