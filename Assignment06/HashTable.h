#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

struct UserRecord {
    string username;
    string salt;
    uint64_t passwordHash;
};

uint64_t demoHash(const string& s);

class HashTable {
private:
    vector<vector<UserRecord>> buckets;
    int count;

    void rehash();

public:
    HashTable();

    bool insert(string username, string password, string salt, string pepper);
    bool find(string username, UserRecord& user);
    bool remove(string username);
    double loadFactor();
    int getBucketIndex(string username);
    int getCapacity();
    int getSize();
};

#endif
