#include "Assignment04.h"


MonopolyBoard::MonopolyBoard() {

    board.add("Mediterranean Avenue", 60);
    board.add("Baltic Avenue", 60);
    board.add("Oriental Avenue", 100);
    board.add("Vermont Avenue", 100);
    board.add("Connecticut Avenue", 120);
    board.add("St. Charles Place", 140);
    board.add("States Avenue", 140);
    board.add("Virginia Avenue", 160);
    board.add("Tennessee Avenue", 180);
    board.add("Boardwalk", 400);

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