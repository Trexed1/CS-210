#include "HashTable.h"
#include <iostream>

using namespace std;

bool login(HashTable& users, string username, string password, string pepper) {
    UserRecord user;
    if (!users.find(username, user)) {
        return false;
    }
    return demoHash(user.salt + password + pepper) == user.passwordHash;
}

void showResult(string label, bool passed) {
    if (passed) {
        cout << "PASS: " << label << endl;
    }
    else {
        cout << "FAIL: " << label << endl;
    }
}

int main() {
    HashTable users;
    string pepper = "classroom-pepper";

    users.insert("alice", "apple7", "salt-a1", pepper);
    users.insert("erin", "echo8", "salt-e2", pepper);

    cout << "Before rehash: alice bucket " << users.getBucketIndex("alice")
         << ", erin bucket " << users.getBucketIndex("erin") << endl;
    showResult("alice and erin collide",
               users.getBucketIndex("alice") == users.getBucketIndex("erin"));
    showResult("both users found in collision chain",
               login(users, "alice", "apple7", pepper) && login(users, "erin", "echo8", pepper));

    users.insert("bob", "banana9", "salt-b3", pepper);
    int oldCapacity = users.getCapacity();
    users.insert("dave", "delta10", "salt-d4", pepper);
    cout << "Rehash: " << oldCapacity << " -> " << users.getCapacity() << " buckets" << endl;
    showResult("fourth insert caused rehash", users.getCapacity() > oldCapacity);

    users.insert("grace", "grape11", "salt-g5", pepper);
    cout << "After rehash: erin bucket " << users.getBucketIndex("erin")
         << ", grace bucket " << users.getBucketIndex("grace") << endl;
    showResult("erin and grace collide",
               users.getBucketIndex("erin") == users.getBucketIndex("grace"));
    cout << "Users: " << users.getSize() << ", load factor: " << users.loadFactor() << endl;
    showResult("five users stored", users.getSize() == 5);

    showResult("correct password accepted", login(users, "grace", "grape11", pepper));
    showResult("wrong password rejected", !login(users, "grace", "wrong", pepper));
    showResult("unknown user rejected", !login(users, "nobody", "anything", pepper));
    showResult("alice still logs in after rehash", login(users, "alice", "apple7", pepper));
    showResult("duplicate username rejected",
               !users.insert("alice", "other", "salt-x", pepper));

    showResult("remove erin", users.remove("erin"));
    showResult("removed user cannot log in", !login(users, "erin", "echo8", pepper));
    showResult("grace still logs in", login(users, "grace", "grape11", pepper));
    cout << "After removal: " << users.getSize() << " users, load factor "
         << users.loadFactor() << endl;

    return 0;
}
