#include "Assignment04.h"


MonopolyBoard::MonopolyBoard() {

    board.add("Plant Island", 60);
    board.add("Cold Island", 60);
    board.add("Air Island", 100);
    board.add("Water Island", 100);
    board.add("Earth Island", 120);
    board.add("Eathereal Workshop", 140);
    board.add("Plasma Islet", 140);
    board.add("Crystal Islet", 160);
    board.add("Mirror Plant Island", 180);
    board.add("Magical Sanctum", 400);

    board.makeCircular();
}


void MonopolyBoard::printBoard() {
    board.print();
}


Node* MonopolyBoard::getStart() {
    return board.getHead();
}


Node* MonopolyBoard::movePlayer(Node* currentPosition, int spaces) {

    for (int i = 0; i < spaces; ++i) {
        currentPosition = currentPosition->next;
    }

    return currentPosition;
}


bool MonopolyBoard::purchaseProperty(Node* property, string playerName) {

    if (property->owner == "Unowned") {

        property->owner = playerName;

        cout << "Result: " << playerName
             << " purchased "
             << property->name
             << " for $"
             << property->cost
             << endl;

        return true;
    }

    if (property->owner == playerName) {

        cout << "Result: "
             << playerName
             << " already owns "
             << property->name
             << endl;

        return false;
    }

    cout << "Result: "
         << property->name
         << " is already owned by "
         << property->owner
         << endl;

    return false;
}