#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Game {
private:
    struct Room {
        map<string, string> directions;
        string item;
        string villain;
    };

    map<string, Room> rooms;
    string currentRoom;
    vector<string> inventory;

    void displayStatus() {
        cout << endl << "You are in the " << currentRoom << endl;
        cout << "Inventory: [";
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << inventory[i];
            if (i < inventory.size() - 1) cout << ", ";
        }
        cout << "]\n";
        if (!rooms[currentRoom].item.empty()) {
            cout << "You see an item: " << rooms[currentRoom].item << endl;
        }
    }

    void displayMap() {
        cout << R"(
                       +----------------+         +----------+
                       |   Small Pond   | <------>| Old Barn |
                       +----------------+         +----------+
                               ^
                               |
                               |
                               |              +-------------+
                               |              |  Tool Shed  |
                               |              +-------------+
                               |                    ^
                               |                    |
                               v                    v
+----------------+     +----------------+     +------------+
|     Tavern     |<--->| Abandoned Town |<--->| Mining Pit |
+----------------+     |     Center     |     +------------+
                       +----------------+
                              |                      
                              v                      
                      +----------------+      +----------------+
                      | Tattered Old   | <--> |  Outskirts of  |
                      |     Altar      |      |     Town       |
                      +----------------+      +----------------+

        )" << endl;
    }

    vector<string> parseInput(const string& input) {
        vector<string> tokens;
        string token;
        for (char c : input) {
            if (c == ' ') {
                if (!token.empty()) tokens.push_back(token);
                token.clear();
            }
            else {
                token += c;
            }
        }
        if (!token.empty()) tokens.push_back(token);
        return tokens;
    }

    string toLowerCase(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:
    Game() {
        rooms["Abandoned Town Center"] = { { {"south", "Tattered Old Altar"}, {"north", "Small Pond"}, {"east", "Mining Pit"}, {"west", "Tavern"} }, "", "" };
        rooms["Tattered Old Altar"] = { { {"north", "Abandoned Town Center"}, {"east", "Outskirts of Town"} }, "Fire Arrows", "" };
        rooms["Outskirts of Town"] = { { {"west", "Tattered Old Altar"} }, "", "Beast" };
        rooms["Tavern"] = { { {"east", "Abandoned Town Center"} }, "Bow", "" };
        rooms["Small Pond"] = { { {"south", "Abandoned Town Center"}, {"east", "Old Barn"} }, "Ice Arrows", "" };
        rooms["Old Barn"] = { { {"west", "Small Pond"} }, "Electric Arrows", "" };
        rooms["Mining Pit"] = { { {"west", "Abandoned Town Center"}, {"north", "Tool Shed"} }, "Stone Arrows", "" };
        rooms["Tool Shed"] = { { {"south", "Mining Pit"} }, "Quiver", "" };

        currentRoom = "Abandoned Town Center";
    }

    void run() {
        cout << "*****************************************\n";
        displayStatus();
        displayMap();

        string input;
        while (true) {
            cout << "Enter your move: ";
            getline(cin, input);
            string lowerInput = toLowerCase(input);
            vector<string> move = parseInput(lowerInput);
            if (move.empty()) continue;

            cout << "*****************************************\n";

            if (move[0] == "go" && move.size() > 1) {
                string direction = move[1];
                if (rooms[currentRoom].directions.find(direction) != rooms[currentRoom].directions.end()) {
                    currentRoom = rooms[currentRoom].directions[direction];
                    displayStatus();
                    displayMap();

                    if (rooms[currentRoom].villain == "Beast") {
                        if (inventory.size() < 6) {
                            cout << "You encountered the beast before acquiring all 6 items. You have been killed.\n";
                            break;
                        }
                        else {
                            cout << "You found all 6 items and defeated the beast. You have won!\n";
                            break;
                        }
                    }
                }
                else {
                    cout << "You can't go that way, try again!\n";
                }
            }
            else if (move[0] == "get" && move.size() > 1) {
                string item = input.substr(4); // Extract item name from input
                if (toLowerCase(rooms[currentRoom].item) == item) {
                    inventory.push_back(rooms[currentRoom].item);
                    rooms[currentRoom].item.clear();
                    cout << item << " added to inventory.\n";
                    displayStatus();
                    displayMap();
                }
                else {
                    cout << "No such item here, try again!\n";
                }
            }
            else if (move[0] == "exit") {
                cout << "Thanks for playing!\n";
                break;
            }
            else {
                cout << "Invalid move, try again!\n";
            }
        }
    }
};

int main() {
    cout << "Welcome to Slaying the Elemental Beast!\n"
        << "You must collect all 6 items before encountering the Beast.\n"
        << "Commands: 'Go <direction>', 'Get <item>', 'Exit'.\n";

    Game game;
    game.run();

    return 0;
}
