// ============================================
// The HashTable class file
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

/****************************************************************************
 * Include the Public Interface
 *
 * By including the public interface at the top of the file, the compiler can
 * enforce that the function declarations in the the header are not in
 * conflict with the definitions in the file. This is not a guarantee of
 * correctness, but it is better than nothing!
 ***************************************************************************/
#include "hash_table.h"

/****************************************************************************
 * Include other private dependencies
 *
 * These other modules are used in the implementation of the hash table module,
 * but are not required by users of the hash table.
 ***************************************************************************/
#include <stdlib.h> // For malloc and free
#include <stdio.h>  // For printf

/****************************************************************************
 * Hidden Definitions
 *
 * These definitions are not available outside of this file. However, because
 * the are forward declared in hash_table.h, the type names are
 * available everywhere and user code can hold pointers to these structs.
 ***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable
{
    /** The array of pointers to the head of a singly linked list, whose nodes
        are HashTableEntry objects */
    HashTableEntry **buckets;

    /** The hash function pointer */
    HashFunction hash;

    /** The number of buckets in the hash table */
    unsigned int num_buckets;
}; // _HashTable

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry
{
    /** The key for the hash table entry */
    unsigned int key;

    /** The value associated with this hash table entry */
    void *value;

    /**
     * A pointer pointing to the next hash table entry
     * NULL means there is no next entry (i.e. this is the tail)
     */
    HashTableEntry *next;
}; // _HashTableEntry

/****************************************************************************
 * Private Functions
 *
 * These functions are not available outside of this file, since they are not
 * declared in hash_table.h.
 ***************************************************************************/
/**
 * createHashTableEntry
 *
 * Helper function that creates a hash table entry by allocating memory for it on
 * the heap. It initializes the entry with key and value, initialize pointer to
 * the next entry as NULL, and return the pointer to this hash table entry.
 *
 * @param key The key corresponds to the hash table entry
 * @param value The value stored in the hash table entry
 * @return The pointer to the hash table entry
 */
static HashTableEntry *createHashTableEntry(unsigned int key, void *value)
{
    HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry)); // allocate space for a new entry and create pointer
    newEntry->key = key;        // assign passed key to new entry's key
    newEntry->value = value;    // assign passed value to new entry's value
    newEntry->next = NULL;      // assign entry's next pointer to null
    return newEntry;            // return the new entry
} // createHashTableEntry

/**
 * findItem
 *
 * Helper function that checks whether there exists the hash table entry that
 * contains a specific key.
 *
 * @param hashTable The pointer to the hash table.
 * @param key The key corresponds to the hash table entry
 * @return The pointer to the hash table entry, or NULL if key does not exist
 */
static HashTableEntry *findItem(HashTable *hashTable, unsigned int key)
{
    int index = hashTable->hash(key); // find the index of buckets corresponding to the given key
    HashTableEntry* entry = hashTable->buckets[index]; // create a temporary pointer, pointing to the head of the LL at the corresponding index
    while (entry) {                 // while entry is non-null
        if (entry->key == key) {    // if current entry's key matches passed key...
            return entry;           // ...correct entry has been found! return the entry
        }
        entry = entry->next;        // otherwise, change entry to entry's next
    }
    return NULL;                    // if key does not exist in ht, return null
} // findItem

/****************************************************************************
 * Public Interface Functions
 *
 * These functions implement the public interface as specified in the header
 * file, and make use of the private functions and hidden definitions in the
 * above sections.
 ****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable *createHashTable(HashFunction hashFunction, unsigned int numBuckets)
{
    // The hash table has to contain at least one bucket. Exit gracefully if
    // this condition is not met.
    if (numBuckets == 0)
    {
        printf("Hash table has to contain at least 1 bucket...\n");
        exit(1);
    }

    // Allocate memory for the new HashTable struct on heap.
    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));

    // Initialize the components of the new HashTable struct.
    newTable->hash = hashFunction;
    newTable->num_buckets = numBuckets;
    newTable->buckets = (HashTableEntry **)malloc(numBuckets * sizeof(HashTableEntry *));

    // As the new buckets are empty, init each bucket as NULL.
    unsigned int i;
    for (i = 0; i < numBuckets; ++i)
    {
        newTable->buckets[i] = NULL;
    }

    // Return the new HashTable struct.
    return newTable;
} // createHashTable

void destroyHashTable(HashTable *hashTable)
{
    // 1. Loop through each bucket of the hash table to remove all items.
    //      1a. set temp to be the first entry of the ith bucket
    //      1b. delete all entries

    // create bound for for-loop based on number of buckets
    
    unsigned int numBuckets = hashTable->num_buckets, i = 0;
    for (i = 0; i < numBuckets; i++) {
        // if the head of the ith bucket is not null...
        if (hashTable->buckets[i]) {
            HashTableEntry* current = hashTable->buckets[i]; // set the "current" pointer to the head of the ith bucket
            HashTableEntry* next = current->next;            // set the "next" pointer to head's next pointer so we can't lose track of it
            // while the current entry's next pointer points to a non-null entry
            while (next) {  
                free(current->value); // free space allocated for current's value
                free(current);        // free space allocated for current itself
                current = next;       // reset current to next
                next = current->next; // reset next to current's next
            }
            free(current->value); // finally, free space allocated for last entry's value
            free(current);        // and the last entry itself
        }
    }

    // 2. Free buckets
    free(hashTable->buckets);

    // 3. Free hash table
    free(hashTable);
    return;
} // destroyHashTable

void *insertItem(HashTable *hashTable, unsigned int key, void *value)
{
    //1. First, we want to check if the key is present in the hash table.
    HashTableEntry* newEntry = findItem(hashTable, key);
    //2. If the key is present in the hash table, store new value and return old value
    if (newEntry) {
        void* temp = newEntry->value;
        newEntry->value = value;
        return temp;
    } else { //3. If not, create entry for new value and return NULL
        newEntry = createHashTableEntry(key, value);
        newEntry->next = hashTable->buckets[hashTable->hash(key)]; // set new entry's next to the bucket's head
        hashTable->buckets[hashTable->hash(key)] = newEntry;       // set bucket's head to new entry
        return NULL;
    }
} // insertItem

void *getItem(HashTable *hashTable, unsigned int key)
{
    //1. First, we want to check if the key is present in the hash table.
    HashTableEntry* entry = findItem(hashTable, key);
    
    //2. If the key exist, return the value
    if (entry) {
        return entry->value;
    }
    //3. If not, return NULL
    return NULL;
} // getItem

void *removeItem(HashTable *hashTable, unsigned int key)
{
    //1. Get the bucket number and the head entry
    int index = hashTable->hash(key);
    HashTableEntry* entry = hashTable->buckets[index];
    
    //2. If head of bucket is null, return null
    if (!entry) {       
        return NULL;
    }

    //Otherwise, if the head holds the key, change the head to the next value, and return the old value
    if (entry->key == key) {
        void* value = entry->value;
        hashTable->buckets[index] = entry->next;
        free(entry);
        return value;
    }

    //3. If not the head, search for the key to be removed 
    HashTableEntry* removedPrevious = NULL; // The previous entry before the entry to be removed
    while(entry->next) {
        if (entry->next->key == key) {
            removedPrevious = entry;        // find which entry's next contains the given key
        }
        entry = entry->next;
    }

    //4. If the key is not present in the list, return NULL
    if (!removedPrevious) {
        return NULL;
    }

    //5. Unlink node from the list and return old value
    HashTableEntry* removed = removedPrevious->next;    // The entry to be removed is removedPrevious' next entry
    void* value = removed->value;                       // value to be returned is removed's value
    removedPrevious->next = removed->next;              // set removedPrevious' next to removed's next
    free(removed);                                      // free the entry
    return value;
} // removeItem

void deleteItem(HashTable *hashTable, unsigned int key)
{
    //1. Remove the entry with removeItem
    void* removedItem = removeItem(hashTable, key);
    if(removedItem) {       // If removedItem is non-null (key existed in the ht)...
        free(removedItem);  // ...then free the value itself from the ht
    }
} // deleteItem