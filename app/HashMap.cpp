/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : HashMap.cpp
*/

#include <iostream>
#include "HashMap.hpp"

// Hash functions can be put in the namespace below.
namespace {
    // default hash function, used in our constructor with no arguments
    unsigned int hashFunc(const std::string& key)
    {
        unsigned int hashValue = 0; // what we end up returning
        for(int i = 0; i < key.length(); i++) { // iterate through string
            int letterIndex = key.at(i) - 96; // create an index for each ASCII char
            // first multiply our current hashValue by a prime number
            // add to the letter index, to maintain a stable result
            hashValue = hashValue * 27 + letterIndex;
        }
        return hashValue;
    } // end hashFunc
}

HashMap::HashMap()
    : hasher{hashFunc}, hashTable{new Node*[initialBucketCount]()}, amountOfBuckets{initialBucketCount}, sz{0}
{
}

// constructor that initializes HashMap to use a different hash function other
// than the default
HashMap::HashMap(HashFunction hasher)
    : hasher{hasher}, hashTable{new Node*[initialBucketCount]()}, amountOfBuckets{initialBucketCount}, sz{0}
{
}

// copy constructor
HashMap::HashMap(const HashMap& hm)
   : hasher{hm.hasher}, hashTable{new Node*[hm.amountOfBuckets]}, amountOfBuckets{hm.amountOfBuckets}, sz{hm.sz}
{
    // we go down buckets vertically and for each bucket we go horizontally through a list
    for(unsigned int i = 0; i < amountOfBuckets; i++) {
        Node* sourceNode = hm.hashTable[i]; // store source head node into a node (for traversal)
        Node** head = &hashTable[i]; // modify pointer to head to store address of hash table at i
        *head = nullptr; // initialize the node to nullptr
        while(sourceNode != nullptr) {
            Node* copy = new Node(); // create a new Node to store data to
            copy->key = sourceNode->key; // copy username
            copy->value = sourceNode->value; // copy password
            copy->next = nullptr; // set next to nullptr
            *head = copy; // set the previous node to the newly copied node
            head = &copy->next; // head holds reference to the next pointer
            copy->next = nullptr; // update next (which updates head)
            sourceNode = sourceNode->next; // advance to next node in list
        } // end while
    } // end for
}

// destructor: deallocate the HashMap
HashMap::~HashMap()
{
    for(unsigned int i = 0; i < amountOfBuckets; i++) {
        Node* nextNode = hashTable[i]; // store each hashtable list in a bucket node
        while(nextNode != nullptr) {
            Node* deleteCurrent = nextNode; // set current to the bucket node (head)
            nextNode = nextNode->next; // delete current is on the first node, update head to second node
            delete deleteCurrent;
        } // end while
    } // end for
    delete[] hashTable; // once done, delete hash table
} // end destructor

// overloaded assignment operator
// example: hm2 = hm1; delete everything in hm2; store everything from hm1 into hm2
HashMap& HashMap::operator=(const HashMap& hm)
{
    if(this != &hm) { // check for self-assignment
        this->HashMap::~HashMap(); // call destructor
        // initialize table to new amount of buckets
        Node** newTable = new Node*[hm.amountOfBuckets];
        // copy items over from original hash table into the new one
        const Node* source;
        for(unsigned int i = 0; i < hm.amountOfBuckets; i++) { // do same thing as cctor
            source = hm.hashTable[i];
            Node** head = &newTable[i];
            *head = nullptr;
            while(source != nullptr) {
                Node* copy = new Node();
                copy->key = source->key;
                copy->value = source->value;
                copy->next = nullptr;
                *head = copy;
                head = &copy->next;
                copy->next = nullptr;
                source = source->next;
            } // end while
        } // end for
        amountOfBuckets = hm.amountOfBuckets; // update amount of buckets
        sz = hm.sz; // update size
        // put newTable into our member variable
        hashTable = newTable;
    } // end if
    return *this; // return object
}

// add function: takes a key and a value. If key is not stored in HashMap,
// we add the key pair/value. Otherwise, if it is already in the HashMap,
// the function has no effect
// If load factor of a HashMap gets to 0.8 from adding this key/value
// 1. We should increase the number of buckets ((curAmt * 2) + 1)
// 2. All key value/pairs will be rehashed to new buckets
void HashMap::add(const std::string& key, const std::string& value)
{
    if(contains(key) == true) // if key is already in hashtable
        return; // exit
    sz++; // increment size
    if(isRehash() == true) { // if we go over the loadfactor, we need to rehash
        // get new capacity
        unsigned int oldAmountOfBuckets = amountOfBuckets;
        amountOfBuckets = ((amountOfBuckets * 2) + 1);
        rehash(oldAmountOfBuckets); // rehash the table
    }
    // we add the new value here
    unsigned int hashedValue = hasher(key); // get hash value (unmodified by buckets)
    unsigned int tableIndex = getTableIndex(hashedValue); // get the table index
    // case 1, check to see if current is nullptr, meaning our first node
    // is the one we should use, ie. we don't need to traverse the list
    Node* head = hashTable[tableIndex];
    Node* current = head;
    if(current == nullptr) {
        // nothing in bucket, create a new node
        current = new Node();
        current->key = key; // set username
        current->value = value; // set pw
        current->next = nullptr;
        hashTable[tableIndex] = current; // store current in head node
        return; // exit
    } else { // case 2, not our first item
        do {
            current = current->next; // advance to next node
        }while(current != nullptr);// end while
        // currently at node we want to insert key/value at
        current = new Node();
        current->key = key; // set key(username)
        current->value = value; // set value (pw)
        current->next = head;
        hashTable[tableIndex] = current; // set next to point to nullptr
    } // end inner if-else (creates node)
} // end add

// takes in a key (username), removes it and the value (password) associated
// with it, otherwise, it has no effect
void HashMap::remove(const std::string& key)
{
    unsigned int hashedValue = hasher(key);
    unsigned int tableIndex = getTableIndex(hashedValue);
    if(contains(key) == false) { // could not find key in bucket
        return; // do nothing
    } else {
        // create a node that keeps track of the node before current node
        // current will get deleted, and we will set the previous node->next to nullptr
        // or we will set it to the next node in the list after current
        Node* prevNode = hashTable[tableIndex];
        Node* delNode = prevNode;
        if(prevNode->key == key) { // first one is a match
            hashTable[tableIndex] = prevNode->next; // set the head of the hash table to point to the next node
            sz--; // decrement amount of keys in hashmap
            delete delNode;
            return; // exit
        } else { // otherwise, we must loop through and find the node we want to delete
            do{
                // check for match, if found, break out of do while
                if(delNode->key == key) {
                    sz--; // decrement size here since we found a match
                    break;
                }
                prevNode = delNode; // save current node in previous
                delNode = delNode->next; // point the searched node to the next node
            }while(delNode != nullptr); // end do while
            // set the previous node to point to delNodes next node
            prevNode->next = delNode->next;
        } // end inner if-else
        delete delNode; // de-allocate
    } // end outer if-else
} // end remove()

// returns true if given key is in hash map, otherwise returns false
// this acts as a find method
bool HashMap::contains(const std::string& key) const
{
    unsigned int hashedValue = hasher(key); // hash the key given to get an index
    unsigned int tableIndex = getTableIndex(hashedValue); // get the table index
    Node* current = hashTable[tableIndex];
    // iterate through each node in the linked list starting at first node
    while(current != nullptr) {
        if(current->key == key) {
            return true; // found match, exit
        }
        current = current->next;
    } // end while
    return false; // we haven't found a match
}

// value() returns the value (pw) associated with the given key in this HashMap
// if the key is stored in this HashMap; if not, the empty string is returned.
std::string HashMap::value(const std::string& key) const
{
    if(contains(key) == true) { // found match
        unsigned int hashedValue = hasher(key); // hash the key given to get an index
        unsigned int tableIndex = getTableIndex(hashedValue); // get the table index
        Node* current = hashTable[tableIndex];
        while(current != nullptr && current->key != key) {
            current = current->next;
        }
        return current->value; // return value after traversal
    } else {
        return ""; // no match, return empty string
    }
}

// size() returns the number of key/value pairs stored in this HashMap.
unsigned int HashMap::size() const
{
    return sz;
}

// bucketCount() returns the number of buckets currently allocated in this HashMap.
unsigned int HashMap::bucketCount() const
{
    return amountOfBuckets;
}

// loadFactor() returns the proportion of the number of key/value pairs
// to the number of buckets, a measurement of how "full" the HashMap is.
double HashMap::loadFactor() const
{
    return sz / (double) amountOfBuckets;
}

// maxBucketSize() returns the number of key/value pairs stored in this
// HashMap's largest bucket.
unsigned int HashMap::maxBucketSize() const
{
    unsigned int maxSize = 0; // holds our max bucket size integer
    for(unsigned int i = 0; i < amountOfBuckets; i++) {
        unsigned int currentLargest = 0; // holds the current largest amount
        Node* current = hashTable[i];
        while(current != nullptr) {
                currentLargest++;
            current = current->next;
        } // end while
        if(currentLargest >= maxSize)
            maxSize = currentLargest;
    } // end for
    return maxSize;
}

// return the table index for a given hashvalue
unsigned int HashMap::getTableIndex(unsigned int hashVal) const{
    return hashVal % amountOfBuckets;
}

void HashMap::rehash(unsigned int oldCap) {
    // create a temp hash map that holds new info before we transfer it to hashTable
    Node** newTable = new Node*[amountOfBuckets](); // initialize to nullptr
    for(unsigned int i = 0; i < oldCap; i++) {
        Node* source = hashTable[i]; // holds values that go into the new hash map
        while(source != nullptr) {
            Node* newValue = source; // creates a new value that we hash and put into newTable
            source = source->next; // advance source to next node
            // compute where newValue goes
            unsigned int hashedValue = hasher(newValue->key);
            unsigned int tableIndex = getTableIndex(hashedValue);
            // store in the correct bucket
            newTable[tableIndex] = newValue;
            newValue = newValue->next; // advance newValue to the next Node
        } // end while
    } // end for
    delete[] hashTable; // free the memory from old table
    hashTable = newTable; // put the new Hash Table in our member variable
} // end rehash

// If we need to rehash the table, return true
// otherwise, return false
bool HashMap::isRehash() {
    if(loadFactor() >= 0.8) {
        return true;
    } else {
        return false;
    }
}

// clears entire table, returns a new hash map
void HashMap::clearTable() {
    for(unsigned int i = 0; i < amountOfBuckets; i++) {
        Node* next = hashTable[i];
        while(next != nullptr) {
            next->key = "";
            next->value = "";
            hashTable[i] = next;
            next = next->next;
        } // end while
    } // end for
    // reset the amount of values
    sz = 0;
}
