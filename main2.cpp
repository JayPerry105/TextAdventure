#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Function to display the player's current status
void displayStatus(const string& currentRoom, const vector<string>& inventory, const map<string, map<string, string>>& rooms) {
    cout << "You are in the " << currentRoom << endl;
    cout << "Inventory: [";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << inventory[i];
        if (i < inventory.size() - 1) cout << ", ";
    }
    cout << "]\n";
    if (rooms.at(currentRoom).count("item")) {
        cout << "You see an item: " << rooms.at(currentRoom).at("item") << endl;
    }
}

// Function to display the map with the current room highlighted
void displayMap(const string& currentRoom) {
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

// Function to parse user input into tokens
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

// Function to convert a string to lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int main() {
    // Define the game map and room connections
    map<string, map<string, string>> rooms = {
        {"Abandoned Town Center", {{"south", "Tattered Old Altar"}, {"north", "Small Pond"}, {"east", "Mining Pit"}, {"west", "Tavern"}}},
        {"Tattered Old Altar", {{"north", "Abandoned Town Center"}, {"east", "Outskirts of Town"}, {"item", "Fire Arrows"}}},
        {"Outskirts of Town", {{"west", "Tattered Old Altar"}, {"villain", "Beast"}}},
        {"Tavern", {{"east", "Abandoned Town Center"}, {"item", "Bow"}}},
        {"Small Pond", {{"south", "Abandoned Town Center"}, {"east", "Old Barn"}, {"item", "Ice Arrows"}}},
        {"Old Barn", {{"west", "Small Pond"}, {"item", "Electric Arrows"}}},
        {"Mining Pit", {{"west", "Abandoned Town Center"}, {"north", "Tool Shed"}, {"item", "Stone Arrows"}}},
        {"Tool Shed", {{"south", "Mining Pit"}, {"item", "Quiver"}}}
    };

    string currentRoom = "Abandoned Town Center"; // Current room
    vector<string> inventory; // Player inventory

    // Intro for the gameplay
    cout << "Welcome to Slaying the Elemental Beast!\n"
        << "You must collect all 6 items before encountering the Beast.\n"
        << "Commands: 'Go <direction>', 'Get <item>', 'Exit'.\n";

    // Display status and game map for user
    displayStatus(currentRoom, inventory, rooms);
    displayMap(currentRoom);

    string input;
    while (true) {
        cout << "Enter your move: ";
        getline(cin, input);
        string lowerInput = toLowerCase(input);
        vector<string> move = parseInput(lowerInput);
        if (move.empty()) continue; // Skip empty user input

        cout << "*****************************************\n";

        // Handles user input for movements
        if (move[0] == "go" && move.size() > 1) {
            string direction = move[1];
            if (rooms[currentRoom].count(direction)) {
                currentRoom = rooms[currentRoom][direction];
                displayStatus(currentRoom, inventory, rooms);
                displayMap(currentRoom);

                // Checks if user is in the 'beast' room
                if (rooms[currentRoom].count("villain") && rooms[currentRoom]["villain"] == "Beast") {
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

        // Handles item collection into inventory
        else if (move[0] == "get" && move.size() > 1) {
            string item = input.substr(4); // Extract item name from input
            if (rooms[currentRoom].count("item") && toLowerCase(rooms[currentRoom]["item"]) == item) {
                inventory.push_back(rooms[currentRoom]["item"]);
                rooms[currentRoom].erase("item");
                cout << item << " added to inventory.\n";
                displayStatus(currentRoom, inventory, rooms);
                displayMap(currentRoom);
            }
            else {
                cout << "No such item here, try again!\n";
            }
        }
        
        // Allows user to exit game at any point
        else if (move[0] == "exit") {
            cout << "Thanks for playing!\n";
            break;
        }
        else {
            cout << "Invalid move, try again!\n";
        }
    }

    return 0;
}
