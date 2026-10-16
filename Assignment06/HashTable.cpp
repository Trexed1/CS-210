#include "HashTable.h"

uint64_t demoHash(const string& s) {
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h = (h ^ c) * 1099511628211ULL;
    }
    return h;
}

HashTable::HashTable() {
    buckets.resize(5);
    count = 0;
}

bool HashTable::insert(string username, string password, string salt, string pepper) {
    UserRecord found;
    if (find(username, found)) {
        return false;
    }

    if ((count + 1.0) / getCapacity() > 0.75) {
        rehash();
    }

    UserRecord user;
    user.username = username;
    user.salt = salt;
    user.passwordHash = demoHash(salt + password + pepper);
    buckets[getBucketIndex(username)].push_back(user);
    count++;
    return true;
}

bool HashTable::find(string username, UserRecord& user) {
    int index = getBucketIndex(username);
    for (UserRecord current : buckets[index]) {
        if (current.username == username) {
            user = current;
            return true;
        }
    }
    return false;
}

bool HashTable::remove(string username) {
    int index = getBucketIndex(username);
    int length = buckets[index].size();

    for (int i = 0; i < length; i++) {
        if (buckets[index][i].username == username) {
            buckets[index][i] = buckets[index][length - 1];
            buckets[index].pop_back();
            count--;
            return true;
        }
    }
    return false;
}

double HashTable::loadFactor() {
    return count / (double)getCapacity();
}

int HashTable::getBucketIndex(string username) {
    return demoHash(username) % getCapacity();
}

int HashTable::getCapacity() {
    return buckets.size();
}

int HashTable::getSize() {
    return count;
}

void HashTable::rehash() {
    int newCapacity = getCapacity() * 2 + 1;
    vector<vector<UserRecord>> newBuckets(newCapacity);

    for (int i = 0; i < getCapacity(); i++) {
        for (UserRecord user : buckets[i]) {
            int newIndex = demoHash(user.username) % newCapacity;
            newBuckets[newIndex].push_back(user);
        }
    }

    buckets = newBuckets;
}
