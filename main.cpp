#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "files/Board.h"
#include <cstdlib> // for srand() and rand()
#include <ctime>

using namespace std;

// Character class
class Character {
    private:
        string name;
        int experience;
        int accuracy;
        int efficiency;
        int insight;
        int discoveryPoints;
    
    public:
        // Getters
        string getName() { return name; }
        int getExperience() { return experience; }
        int getAccuracy() { return accuracy; }
        int getEfficiency() { return efficiency; }
        int getInsight() { return insight; }
        int getDiscoveryPoints() { return discoveryPoints; }
        
        // Setters
        void setName(string n) { name = n; }
        void setExperience(int e) { experience = e; }
        void setAccuracy(int a) { accuracy = a; }
        void setEfficiency(int e) { efficiency = e; }
        void setInsight(int i) { insight = i; }
        void setDiscoveryPoints(int d) { discoveryPoints = d; }
};

// Player class
class Player {
    public:
        string name;
        Character character;
        int path;
        int advisor;

};

int spinner() {
    return (rand() % 6) + 1; // Returns a number between 1 and 6
}

// Pick Path function
Player pathChoice(Player player, int choice) {
    // Training Path
    if (choice == 1) {
        player.character.setDiscoveryPoints(player.character.getDiscoveryPoints() - 5000);
        player.character.setAccuracy(player.character.getAccuracy() + 500);
        player.character.setEfficiency(player.character.getEfficiency() + 500);
        player.character.setInsight(player.character.getInsight() + 1000);

        // Pick Advisor
        cout << "You have chosen the Training Fellowship path and gained the ability to pick an Advisor!" << endl;
        cout << "1. Dr. Aliquot: avoid contamination\n2. Dr. Assembler: improve efficiency and streamlines pipelines\n3. Dr. Pop-Gen: identifies rare genetic variants\n4. Dr. Bio-Script: helps debug code\n5. Dr. Loci: assists in learning equipment" << endl;
        int advisorChoice;
        cout << "Pick your Advisor (1-5): ";
        cin >> advisorChoice;
        player.advisor = advisorChoice;

    // Direct Path
    } else if (choice == 2) {
        player.character.setDiscoveryPoints(player.character.getDiscoveryPoints() + 5000);
        player.character.setAccuracy(player.character.getAccuracy() + 200);
        player.character.setEfficiency(player.character.getEfficiency() + 200);
        player.character.setInsight(player.character.getInsight() + 200);
    }
    return player;
}

// Main function
int main() {
    // clear terminal
    system("clear");

    // Load characters from characters.txt
    ifstream file("files/characters.txt");
    string line;
    vector<Character> characters;
    
    getline(file, line); // Skip header

    while (getline(file, line)) {
        int pos = 0;
        vector<string> attributes;
        
        while ((pos = line.find('|')) != string::npos) {
            attributes.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        attributes.push_back(line); // Last attribute
        
        Character c;
        c.setName(attributes[0]);
        c.setExperience(stoi(attributes[1]));
        c.setAccuracy(stoi(attributes[2]));
        c.setEfficiency(stoi(attributes[3]));
        c.setInsight(stoi(attributes[4]));
        c.setDiscoveryPoints(stoi(attributes[5]));
        
        characters.push_back(c);
    }
    
    file.close();

    // Players pick a character
    string player1Name, player2Name;
    Character player1Character, player2Character;

    // Player 1 selection
    Player player1;
    cout << "Player 1 enter your name: ";
    cin >> player1.name;
    cout << player1.name + ", Pick a character\n";

    for (size_t i = 0; i < characters.size(); ++i) {
        cout << i + 1 << ": " << characters[i].getName() << endl;
    }

    int choice1;
    cin >> choice1;
    player1.character = characters[choice1 - 1];

    // Player 2 selection
    Player player2;
    cout << "Player 2 enter your name: ";
    cin >> player2.name;
    cout << player2.name + ", Pick a character\n";

    for (size_t i = 0; i < characters.size(); ++i) {
        if (i == choice1 - 1) continue; // Skip the character chosen by player 1
        cout << i + 1 << ": " << characters[i].getName() << endl;
    }

    int choice2;
    cin >> choice2;
    player2.character = characters[choice2 - 1];

    // Set player discovery points to 20,0000
    player1.character.setDiscoveryPoints(200000);
    player2.character.setDiscoveryPoints(200000);

    // Pick Path
    cout << "Next, Choose your path.\nPaths:\n1. Training Fellowship\n  -5,000 Discovery Points\n  +500 Accuracy Points\n  +500 Efficiency Points\n  +1,000 Insight Points\n  +And you gain the ability to pick an Advisor\n" << endl;
    cout << "2. Direct Lab Assignment\n  +5,000 Discovery Points\n  +200 Accuracy Points\n  +200 Efficiency Points\n  +200 Insight Points" << endl;
    
    int choice;
    cout << player1.name + ", pick your path (1-2): ";
    cin >> player1.path;

    player1 = pathChoice(player1, player1.path);
    
    cout << player2.name + ", pick your path (1-2): ";
    cin >> player2.path;

    player2 = pathChoice(player2, player2.path);

    
    //Initialize Board
    srand((unsigned)time(nullptr)); // randomize tile seeding

    Board board;

    // Start the Game loop
    system("clear");
    bool game_over = false;
    int turn = 0;
    Player current_player;

    while (!game_over) {
        if (turn % 2 == 0) {
            current_player = player1;
            cout << player1.name + "'s Turn\n";
        } else {
            current_player = player2;
            cout << player2.name + "'s Turn\n";
        }

        cout << "===== Main Menu =====\n\n1. Check Progress\n  a) Review Discover Points\n  b) Review Trait Stats\n2. Review Character\n3. Check Position\n4. Review Advisor\n  a) View Ability\n  b) Use ability\n5. Move Forward" << endl;
        cout << "\nSelect an option (1-5): ";
        int menu_choice;
        cin >> menu_choice;
        switch(menu_choice) {
            case 1:
                cout<< "Do you want to review:\n1. Discovery Points\n2. Trait Stats\n";
                int sub_choice;
                cin >> sub_choice;
                if (sub_choice == 1) {
                    cout << "Discovery Points: " << current_player.character.getDiscoveryPoints() << endl;
                } else if (sub_choice == 2) {
                    cout << "Accuracy: " << current_player.character.getAccuracy() << endl;
                    cout << "Efficiency: " << current_player.character.getEfficiency() << endl;
                    cout << "Insight: " << current_player.character.getInsight() << endl;
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            case 2:
                cout << "Character Name: " << current_player.character.getName() << endl;
                cout << "Experience: " << current_player.character.getExperience() << endl;
                break;
            case 3:
                cout << "Current Position on Board: " << board.getPlayerPosition(turn % 2) << endl;
                break;
            case 4:
                cout << "Do you want to:\n1. View Ability\n2. Use Ability\n";
                int advisor_choice;
                cin >> advisor_choice;
                if (advisor_choice == 1) {
                    switch (current_player.advisor) {
                        case 1:
                            cout << "Dr. Aliquot: Helps avoid contamination during experiments." << endl;
                            break;
                        case 2:
                            cout << "Dr. Assembler: Improves efficiency and streamlines pipelines." << endl;
                            break;
                        case 3:
                            cout << "Dr. Pop-Gen: Identifies rare genetic variants." << endl;
                            break;
                        case 4:
                            cout << "Dr. Bio-Script: Helps debug code." << endl;
                            break;
                        case 5:
                            cout << "Dr. Loci: Assists in learning equipment." << endl;
                            break;
                        default:
                            cout << "No Advisor selected." << endl;
                    }
                } else if (advisor_choice == 2) {
                    cout << "Using Advisor ability..." << endl;
                    // Implement advisor ability effects here
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            case 5:
                cout << current_player.name + " spins the spinner..." << endl;
                int spin_result;
                spin_result = spinner();
                cout << "You rolled a " << spin_result << "!" << endl;
                for (int i = 0; i < spin_result; ++i) {
                    board.movePlayer(turn % 2);
                }
                board.displayBoard();
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    turn++;
    }       
    return 0;
}
