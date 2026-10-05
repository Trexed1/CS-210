#include "Assignment04.h"

int main() {

    // =========================
    // PART 1: LINKED LIST TEST
    // =========================

    cout << "PART 1: LINKED LIST TEST" << endl;
    cout << "========================" << endl;

    LinkedList testList;

    testList.add("Property A", 100);
    testList.add("Property B", 200);
    testList.add("Property C", 300);
    testList.add("Property D", 400);


    cout << "\nOriginal List:" << endl;
    cout << "--------------" << endl;

    testList.print();


    cout << "\nSearch Test:" << endl;
    cout << "------------" << endl;

    Node* found = testList.search("Property C");

    if (found != nullptr) {
        cout << "Found: "
             << found->name
             << " | Cost: $"
             << found->cost
             << endl;
    }
    else {
        cout << "Property was not found." << endl;
    }


    cout << "\nRemove Test:" << endl;
    cout << "------------" << endl;

    if (testList.remove("Property B")) {
        cout << "Property B was removed." << endl;
    }
    else {
        cout << "Property B was not found." << endl;
    }


    cout << "\nList After Removal:" << endl;
    cout << "-------------------" << endl;

    testList.print();



    // =========================
    // PART 2: MONOPOLY GAME
    // =========================

    cout << "\n\nPART 2: MONOPOLY GAME" << endl;
    cout << "=====================" << endl;

    MonopolyBoard game;


    cout << "\nInitial Board:" << endl;
    cout << "--------------" << endl;

    game.printBoard();


    Node* player1Position = game.getStart();
    Node* player2Position = game.getStart();

    string player1 = "Player 1";
    string player2 = "Player 2";


    // Different movement values so both players
    // can purchase properties and also land on
    // properties that are already owned.
    int moves[12] = {
        1, 2,
        3, 2,
        4, 3,
        5, 4,
        2, 6,
        3, 5
    };


    cout << "\nPLAYER TURNS" << endl;
    cout << "============" << endl;


    for (int turn = 0; turn < 12; ++turn) {

        cout << "\n----------------------------------------" << endl;

        if (turn % 2 == 0) {

            cout << "TURN "
                 << turn + 1
                 << " - "
                 << player1
                 << endl;

            cout << "----------------------------------------" << endl;

            player1Position =
                game.movePlayer(player1Position, moves[turn]);

            cout << "Move: "
                 << moves[turn]
                 << " spaces"
                 << endl;

            cout << "Landed on: "
                 << player1Position->name
                 << endl;

            cout << "Cost: $"
                 << player1Position->cost
                 << endl;

            game.purchaseProperty(
                player1Position,
                player1
            );
        }

        else {

            cout << "TURN "
                 << turn + 1
                 << " - "
                 << player2
                 << endl;

            cout << "----------------------------------------" << endl;

            player2Position =
                game.movePlayer(player2Position, moves[turn]);

            cout << "Move: "
                 << moves[turn]
                 << " spaces"
                 << endl;

            cout << "Landed on: "
                 << player2Position->name
                 << endl;

            cout << "Cost: $"
                 << player2Position->cost
                 << endl;

            game.purchaseProperty(
                player2Position,
                player2
            );
        }
    }


    cout << "\n\nFINAL BOARD STATE" << endl;
    cout << "=================" << endl;

    game.printBoard();


    return 0;
}