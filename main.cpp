#include <iostream>
#include <windows.h>
#include <iomanip>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Method Headers

// "Convenience" methods (repetitive to type, used a lot)
void lineBreak(string companyName);
void printInventory(long double inventory[5]);
bool typeTrap();

// Menus
int titleScreen();
void supplierMenu(string companyName, long double inventory[5], int supplier, string name);
void advertiserMenu(string companyName, long double inventory[5], int advertiser, string name, int advertisements[4]);
void employmentMenu(string companyName, long double inventory[5], int &supplier, int &advertiser, string name);
void locationMenu(string companyName, long double inventory[5], string name, int locations[6]);

// Run the day
void startDay(string companyName, long double inventory[5], string name, long int &customers, int advertiser, int &day, int locations[6], int advertisements[4], int supplier, long double reputation);

// Name lookup tables
string suppliers(int id);
string advertisers(int id);

void createSaveFile(int saveID);
void saveData(int saveID, int day, long double inventory[5], int locations[6], int advertisements[4], long double reputation, int supplier, int advertiser, long int prevCustomers, long int customers, string name, string companyName);
void loadData(int& saveID, int& day, long double inventory[5], int locations[6], int advertisements[4], long double& reputation, int& supplier, int& advertiser, long int& prevCustomers, long int& customers, string& name, string& companyName);

int main(){
    // Declare Variables

    string name, companyName;
    bool running = true;
    int saveID;

    // Inventory indexes: 0 = Containers, 1 = Chalk, 2 = Paper, 3 = Ink, 4 = Money
    long double inventory[5] = {0, 0, 0, 0, 100};
    int locations[6] = {0, 0, 0, 0, 0, 0};
    int advertisements[4] = {0, 0, 0, 0};
    double supplierPrices[10] = {10.50, 13.70, 20.00, 52.60, 120.00, 258.90, 372.10, 785.30, 1000.00, 1000000.00};
    int day = 1;
    long double reputation = 1;

    int supplier = 0;
    int advertiser = 0;
    long int prevCustomers = 0;
    long int customers = 0;

    int extraProb;
    bool starting = true;
    int choiceMain;

    // Run title screen then begin game

    choiceMain = titleScreen();
    if(choiceMain){
        system("pause");
        return 0;
    }

    // Store name of company and player name in their respective variables

    while(starting){
        system("cls");
        cout << "Please select a save file:\n\t[1]\n\t[2]\n\t[3]\n\t[4]\n\t[5]\n >>> ";
        cin >> choiceMain;
        saveID = choiceMain;

        if(choiceMain > 5 || choiceMain < 1){
            continue;
        }

        ostringstream text1;
        ostringstream msg1;

        msg1 << "saves/" << choiceMain << ".txt";

        ifstream in_file(msg1.str().c_str());

        string start = "day:";
        string ends = "inventory[0]";

        text1 << in_file.rdbuf();
        string str1 = text1.str();



        try{
            unsigned str1_start = str1.find(start);
            unsigned str1_end = str1.find(ends);

            string str1New = str1.substr(str1_start, str1_end);

            starting = false;
            loadData(saveID, day, inventory, locations, advertisements, reputation, supplier, advertiser, prevCustomers, customers, name, companyName);

            cout << str1New << endl;

            cout << "\nWould you like to continue this game?" << endl;
            cout << "[0] Yes\n[1] No\n[2] Reset File" << endl;
            cout << " >>> ";
            cin >> choiceMain;

            if(choiceMain == 0){
                starting = false;
                continue;
            }
            else if(choiceMain == 1){
                starting = true;
                continue;
            }
            else if(choiceMain == 2){
                createSaveFile(saveID);
                inventory[0] = 0;
                inventory[1] = 0;
                inventory[2] = 0;
                inventory[3] = 0;
                inventory[4] = 100;
                for(int i = 0; i < 6; i++){
                    locations[i] = 0;
                }
                for(int i = 0; i < 4; i++){
                    advertisements[i] = 0;
                }
                day = 1;
                reputation = 1;

                supplier = 0;
                advertiser = 0;
                prevCustomers = 0;
                customers = 0;

                starting = true;
                break;
            }

        } catch(int out_of_range){
            createSaveFile(saveID);
            starting = true;
            break;
        }
    }

    while(starting){
        system("cls");
        cout << "What is your name? ";
        cin >> name;
        if(typeTrap())
            continue;
        break;
    }

    while(starting){
        cout << "What is the name of your company? ";
        cin >> companyName;
        if(typeTrap())
            continue;
        break;
    }

    //Start main game loop

    while(running){
        // Check for win/loss based on money, reputation, and customers

        saveData(saveID, day, inventory, locations, advertisements, reputation, supplier, advertiser, prevCustomers, customers, name, companyName);
        if(inventory[4] <= 0){
            // If player is out of money they lose

            system("cls");
            cout << "You have gone bankrupt!" << endl;
            cout << "You lose!" << endl;
            lineBreak(companyName);
            cout << "STATS" << endl;
            cout << "Company Name: " << companyName << endl;
            cout << "Owner: " << name << endl;
            cout << "Day: " << day << endl;
            cout << "Members: " << customers << endl;
            cout << "Money: " << inventory[4] << endl;
            cout << setprecision(2) << fixed << "Reputation: " << reputation << endl;
            cout << "\n=== GAME OVER ===" << endl;
            running = false;
            continue;
        }
        if(reputation <= 0.35){
            // If player's reputation is below the threshold they lose

            system("cls");
            cout << "Your bad reputation led to the FBI catching you!" << endl;
            cout << "You lose!" << endl;
            lineBreak(companyName);
            cout << "STATS" << endl;
            cout << "Company Name: " << companyName << endl;
            cout << "Owner: " << name << endl;
            cout << "Day: " << day << endl;
            cout << "Members: " << customers << endl;
            cout << "Money: " << inventory[4] << endl;
            cout << setprecision(2) << fixed << "Reputation: " << reputation << endl;
            cout << "\n=== GAME OVER ===" << endl;
            running = false;
            continue;
        }
        if(customers >= 35000000){
            // If player's customer count is above the threshold they win
            system("cls");
            cout << "Everyone in the world has joined your scheme!" << endl;
            cout << "The company has collapsed due to lack of new customers and you walk away rich!" << endl;
            cout << "You win!" << endl;
            lineBreak(companyName);
            cout << "STATS" << endl;
            cout << "Company Name: " << companyName << endl;
            cout << "Owner: " << name << endl;
            cout << "Day: " << day << endl;
            cout << "Members: " << customers << endl;
            cout << "Money: " << inventory[4] << endl;
            cout << setprecision(2) << fixed << "Reputation: " << reputation << endl;
            cout << "\n=== GAME OVER ===" << endl;
            running = false;
            continue;
        }

        // After two weeks extras become possible

        if(day > 14){
            extraProb = rand()%100+1;
            if(extraProb == 17){
                // 1/100 chance they earn some money

                system("cls");
                cout << "Your recent insider trading was hugely successful!" << endl;
                cout << "You made " << inventory[4]*0.1 << setprecision(2) << fixed << " dollars!" << endl;
                inventory[4] += inventory[4]*0.1;
                cout << setprecision(0);
                system("pause");
            }
            if(extraProb == 29){
                // 1/100 chance they lose some money

                system("cls");
                cout << "Your recent insider trading was discovered by the FBI!" << endl;
                cout << "You lost " << inventory[4]*0.1 << setprecision(2) << fixed << " dollars!" << endl;
                inventory[4] -= inventory[4]*0.1;
                cout << setprecision(0);
                system("pause");
            }
        }

        // Print main menu and take player input

        system("cls");
        prevCustomers = customers;

        cout << companyName << " Portfolio" << endl;
        cout << "Day " << day << endl;
        cout << "Members: " << customers << endl;

        lineBreak(companyName);
        printInventory(inventory);
        lineBreak(companyName);

        cout << "[0] Exit Game" << endl;
        cout << "[1] Supplier" << endl;
        cout << "[2] Advertising" << endl;
        cout << "[3] Employments" << endl;
        cout << "[4] Location" << endl;
        cout << "[5] Start Day" << endl;
        cout << name << " >>> ";
        cin >> choiceMain;
        if(typeTrap())
            continue;

        // If input is 0, then exit the game

        if(choiceMain == 0){
            char exit;
            system("cls");
            cout << "Are you sure you want to leave [y/n]? ";
            cin >> exit;
            if(typeTrap())
                continue;

            if(exit == 'y'){
                running = false;
                continue;
            }
            else{
                continue;
            }
        }

        // If input is 1, then enter the supplier menu

        else if(choiceMain == 1){
            supplierMenu(companyName, inventory, supplier, name);
        }

        // If input is 2, then enter the advertiser menu

        else if(choiceMain == 2){
            advertiserMenu(companyName, inventory, advertiser, name, advertisements);
        }

        // If input is 3, then enter the employment menu

        else if(choiceMain == 3){
            employmentMenu(companyName, inventory, supplier, advertiser, name);
        }

        // If input is 4, then enter the locations menu

        else if(choiceMain == 4){
            locationMenu(companyName, inventory, name, locations);
        }

        // If input is 5, then begin the day

        else if(choiceMain == 5){
            startDay(companyName, inventory, name, customers, advertiser, day, locations, advertisements, supplier, reputation);
            if(prevCustomers < customers){
                reputation += 0.2;
            }
            else{
                reputation -= 0.1;
            }

            // If player cannot afford the services they have purchased, then they lose those services and their reputation goes down

            if(inventory[4] < supplierPrices[advertiser-1]){
                system("cls");
                cout << "You cannot afford your advertiser!" << endl;
                cout << "They have quit!" << endl;
                advertiser = 0;
                system("pause");
                reputation -= 0.05;
            }
            else if(advertiser != 0){
                inventory[4] -= supplierPrices[advertiser-1];
            }
            if(inventory[4] < supplierPrices[supplier-1]){
                system("cls");
                cout << "You cannot afford your supplier!" << endl;
                cout << "They have quit!" << endl;
                supplier = 0;
                system("pause");
                reputation -= 0.05;
            }
            else if(supplier != 0){
                inventory[4] -= supplierPrices[supplier-1];
            }
            if(inventory[4] < locations[1]*20){
                system("cls");
                cout << "You cannot afford your Corner Stores!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.01*locations[1];
                locations[1] = 0;
                system("pause");
            }
            else if(locations[1] != 0){
                inventory[4] -= locations[1]*20;
            }
            if(inventory[4] < locations[2]*150){
                system("cls");
                cout << "You cannot afford your Strip Malls!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.03*locations[2];
                locations[2] = 0;
                system("pause");
            }
            else if(locations[2] != 0){
                inventory[4] -= locations[2]*150;
            }
            if(inventory[4] < locations[3]*500){
                system("cls");
                cout << "You cannot afford your Recruitment Offices!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.05*locations[3];
                locations[3] = 0;
                system("pause");
            }
            else if(locations[3] != 0){
                inventory[4] -= locations[3]*500;
            }
            if(inventory[4] < locations[4]*1000){
                system("cls");
                cout << "You cannot afford your Websites!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.07*locations[4];
                locations[4] = 0;
                system("pause");
            }
            else if(locations[4] != 0){
                inventory[4] -= locations[4]*1000;
            }
            if(inventory[4] < locations[5]*5000){
                system("cls");
                cout << "You cannot afford your Sponsorships!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.09*locations[5];
                locations[5] = 0;
                system("pause");
            }
            else if(locations[5] != 0){
                inventory[4] -= locations[5]*5000;
                reputation += locations[5]*0.01;
            }
            if(advertisements[0]*10 > inventory[4]){
                system("cls");
                cout << "You cannot afford your newspaper ads!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.01*advertisements[0];
                advertisements[0] = 0;
                system("pause");
            }
            else if(advertisements != 0){
                inventory[4] -= advertisements[0]*10;
            }
            if(advertisements[1]*30 > inventory[4]){
                system("cls");
                cout << "You cannot afford your radio ads!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.03*advertisements[1];
                advertisements[1] = 0;
                system("pause");
            }
            else if(advertisements != 0){
                inventory[4] -= advertisements[1]*30;
            }
            if(advertisements[2]*100 > inventory[4]){
                system("cls");
                cout << "You cannot afford your television ads!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.05*advertisements[2];
                advertisements[2] = 0;
                system("pause");
            }
            else if(advertisements != 0){
                inventory[4] -= advertisements[2]*100;
            }
            if(advertisements[3]*1500 > inventory[4]){
                system("cls");
                cout << "You cannot afford your celebrity endorsements!" << endl;
                cout << "They have quit!" << endl;
                reputation -= 0.07*advertisements[3];
                advertisements[3] = 0;
                system("pause");
            }
            else if(advertisements != 0){
                inventory[4] -= advertisements[3]*1500;
                reputation += advertisements[3]*0.01;
            }
        }

        // Debugging menus only available if both the player and company names are set to 'debug'

        else if(choiceMain == 1971 && name == "debug" && companyName == "debug"){
            // Add money to inventory

            system("cls");
            cout << "How much money would you like to add? ";
            cin >> choiceMain;
            inventory[4] += choiceMain;
            cout << "$" << choiceMain << " has been added!" << endl;
            system("pause");
        }
        else if(choiceMain == 979 && name == "debug" && companyName == "debug"){
            // Check current reputation stat

            system("cls");
            cout << "Your reputation is currently " << setprecision(2) << fixed << reputation << endl;
            cout << setprecision(0);
            system("pause");
        }
    }
    system("pause");
    return 0;
}

int titleScreen(){
    // Displays the title screen and asks the player if they would like to begin

    // Text art generated at 'https://patorjk.com/software/taag/'

    bool running = true;

    while(running){
        system("cls");

        int choice;

        // "Multi Level Marketing"

        cout << "$$\\      $$\\           $$\\   $$\\     $$\\       $$\\                                    $$\\\n$$$\\    $$$ |          $$ |  $$ |    \\__|      $$ |                                   $$ |\n$$$$\\  $$$$ |$$\\   $$\\ $$ |$$$$$$\\   $$\\       $$ |      $$$$$$\\ $$\\    $$\\  $$$$$$\\  $$ |\n$$\\$$\\$$ $$ |$$ |  $$ |$$ |\\_$$  _|  $$ |      $$ |     $$  __$$\\\\$$\\  $$  |$$  __$$\\ $$ |\n$$ \\$$$  $$ |$$ |  $$ |$$ |  $$ |    $$ |      $$ |     $$$$$$$$ |\\$$\\$$  / $$$$$$$$ |$$ |\n$$ |\\$  /$$ |$$ |  $$ |$$ |  $$ |$$\\ $$ |      $$ |     $$   ____| \\$$$  /  $$   ____|$$ |\n$$ | \\_/ $$ |\\$$$$$$  |$$ |  \\$$$$  |$$ |      $$$$$$$$\\\\$$$$$$$\\   \\$  /   \\$$$$$$$\\ $$ |\n\\__|     \\__| \\______/ \\__|   \\____/ \\__|      \\________|\\_______|   \\_/     \\_______|\\__|\n\n\n\n$$\\      $$\\                     $$\\                  $$\\     $$\\                         \n$$$\\    $$$ |                    $$ |                 $$ |    \\__|                        \n$$$$\\  $$$$ | $$$$$$\\   $$$$$$\\  $$ |  $$\\  $$$$$$\\ $$$$$$\\   $$\\ $$$$$$$\\   $$$$$$\\      \n$$\\$$\\$$ $$ | \\____$$\\ $$  __$$\\ $$ | $$  |$$  __$$\\\\_$$  _|  $$ |$$  __$$\\ $$  __$$\\     \n$$ \\$$$  $$ | $$$$$$$ |$$ |  \\__|$$$$$$  / $$$$$$$$ | $$ |    $$ |$$ |  $$ |$$ /  $$ |    \n$$ |\\$  /$$ |$$  __$$ |$$ |      $$  _$$<  $$   ____| $$ |$$\\ $$ |$$ |  $$ |$$ |  $$ |    \n$$ | \\_/ $$ |\\$$$$$$$ |$$ |      $$ | \\$$\\ \\$$$$$$$\\  \\$$$$  |$$ |$$ |  $$ |\\$$$$$$$ |    \n\\__|     \\__| \\_______|\\__|      \\__|  \\__| \\_______|  \\____/ \\__|\\__|  \\__| \\____$$ |    \n                                                                            $$\\   $$ |    \n                                                                            \\$$$$$$  |    \n                                                                             \\______/" << endl;

        // "START" and "EXIT"

        cout << " ___    _____ _____ _____ _____ _____\n|   |  |   __|_   _|  _  | __  |_   _|\n| | |  |__   | | | |     |    -| | |\n|___|  |_____| |_| |__|__|__|__| |_|\n" << endl;
        cout << endl;
        cout << "\n ___      _____ __ __ _____ _____\n|_  |    |   __|  |  |     |_   _|\n _| |_   |   __|-   -|-   -| | |\n|_____|  |_____|__|__|_____| |_|\n" << endl;
        cout << ">>> ";
        cin >> choice;
        if(typeTrap())
            continue;

        return choice;
    }
    return 1;
}

void lineBreak(string companyName){
    // Generates a line that is as long as the company name plus " Portfolio"

    for(int unsigned i = 0; i < companyName.length(); i++){
            cout << "=";
        }
        cout << "==========" << endl;
}

void printInventory(long double inventory[5]){
    // Prints the players current inventory

    cout << "Inventory" << endl;
    cout << "Containers: \t" << inventory[0] << " units" << endl;
    cout << "Chalk: \t\t" << inventory[1] << " mg" << endl;
    cout << "Paper: \t\t" << inventory[2] << " sheets" << endl;
    cout << "Ink: \t\t" << inventory[3] << " ml" << endl;
    cout << "Money: \t\t$" << setprecision(2) << fixed << inventory[4] << endl;
    cout << setprecision(0);
}

bool typeTrap(){
    // Returns true if the player has entered an invalid input

    if(!cin.good()){
        cout << "ERROR: Invalid Input" << endl;
        cin.clear();
        cin.ignore(128, '\n');
        system("pause");
        return true;
    }
    return false;
}

void supplierMenu(string companyName, long double inventory[5], int supplier, string name){
    // Allows the player to buy and sell materials

    bool running = true;
    int choiceSupply;
    while(running){
        system("cls");
        if(supplier == 0){
            // If the player does not have a supplier they cannot buy/sell materials

            cout << "You do not have a supplier!" << endl;
            system("pause");
            running = false;
            continue;
        }
        else{
            // Prints the supplier menu and asks if they player would like to buy or sell

            cout << companyName << " Supplier:" << endl;
            cout << suppliers(supplier) << endl;
            lineBreak(companyName);
            printInventory(inventory);
            lineBreak(companyName);
            cout << "[0] Exit Menu" << endl;
            cout << "[1] Purchase" << endl;
            cout << "[2] Sell" << endl;
            cout << name << " >>> ";
            cin >> choiceSupply;
            if(typeTrap())
                continue;

            if(choiceSupply == 0){
                // If the input is 0 then exit the menu

                running = false;
                continue;
            }
            else if(choiceSupply == 1){
                bool choosing = true;
                while(choosing){
                    // If the input is 1 then enter the buying menu

                    system("cls");
                    cout << companyName << " Supplier:" << endl;
                    cout << suppliers(supplier) << endl;
                    lineBreak(companyName);
                    printInventory(inventory);
                    lineBreak(companyName);
                    cout << "[0] Exit Menu" << endl;
                    cout << "[1] Containers: $0.17 per unit" << endl;
                    cout << "[2] Chalk: $0.10 per mg" << endl;
                    cout << "[3] Paper: $0.05 per sheet" << endl;
                    cout << "[4] Ink: $10.00 per liter" << endl;
                    cout << name << " >>> ";
                    cin >> choiceSupply;
                    if(typeTrap())
                        continue;

                    if(choiceSupply < 0 || choiceSupply > 4){
                        // Prevent the player from entering the number of an item that isn't in the list

                        system("cls");
                        cout << "That item does not exist!" << endl;
                        system("pause");
                        continue;
                    }
                    else if(choiceSupply == 0){
                        // If the input is 0 then exit the menu

                        choosing = false;
                        continue;
                    }
                    else{
                        // If their input is valid, then ask how many they want of that item

                        int quantity;
                        cout << "How many do you want? ";
                        cin >> quantity;
                        if(typeTrap())
                            continue;

                        if(quantity < 0){
                            // Prevent the player from buying a negative amount of items

                            system("cls");
                            cout << "You cannot buy a negative amount!" << endl;
                            system("pause");
                            continue;
                        }

                        // Check to see if the player can afford the materials, then purchase them and add to the players inventory, while subtracting from their money

                        else if(choiceSupply == 1){
                            if(inventory[4] < quantity*0.17){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*0.17;
                                inventory[0] += quantity;
                                continue;
                            }
                        }
                        else if(choiceSupply == 2){
                            if(inventory[4] < quantity*0.10){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*0.10;
                                inventory[1] += quantity;
                                continue;
                            }
                        }
                        else if(choiceSupply == 3){
                            if(inventory[4] < quantity*0.05){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*0.05;
                                inventory[2] += quantity;
                                continue;
                            }
                        }
                        else if(choiceSupply == 4){
                            if(inventory[4] < quantity*10.00){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*10.00;
                                inventory[3] += quantity*1000;
                                continue;
                            }
                        }
                    }
                }
            }
            else if(choiceSupply == 2){
                bool choosing = true;
                while(choosing){
                    // If input is 2 then enter the selling menu

                    system("cls");
                    cout << companyName << " Supplier:" << endl;
                    cout << suppliers(supplier) << endl;
                    lineBreak(companyName);
                    printInventory(inventory);
                    lineBreak(companyName);
                    cout << "[0] Exit Menu" << endl;
                    cout << "[1] Containers: $0.10 per unit" << endl;
                    cout << "[2] Chalk: $0.05 per mg" << endl;
                    cout << "[3] Paper: $0.05 per sheet" << endl;
                    cout << "[4] Ink: $8.00 per liter" << endl;
                    cout << name << " >>> ";
                    cin >> choiceSupply;
                    if(typeTrap())
                        continue;

                    if(choiceSupply < 0 || choiceSupply > 4){
                        // Same as buying menu, prevent invalid options

                        system("cls");
                        cout << "That item does not exist!" << endl;
                        system("pause");
                        continue;
                    }
                    else if(choiceSupply == 0){
                        // If the input is 0 then exit the menu

                        choosing = false;
                        continue;
                    }
                    else{
                        // If the input is valid then ask how much they want to sell

                        int quantity;
                        cout << "How many do you want to sell? ";
                        cin >> quantity;
                        if(typeTrap())
                            continue;

                        if(quantity < 0){
                            // Prevent the player from selling a negative amount of materials

                            system("cls");
                            cout << "You cannot sell a negative amount!" << endl;
                            system("pause");
                            continue;
                        }

                        // If they have enough materials to sell, then subtract them from their inventory and add the appropriate amount to their money

                        else if(choiceSupply == 1 && quantity <= inventory[0]){
                            inventory[4] += quantity*0.10;
                            inventory[0] -= quantity;
                            continue;
                        }
                        else if(choiceSupply == 2 && quantity <= inventory[1]){
                            inventory[4] += quantity*0.05;
                            inventory[1] -= quantity;
                            continue;
                        }
                        else if(choiceSupply == 3 && quantity <= inventory[2]){
                            inventory[4] += quantity*0.05;
                            inventory[2] -= quantity;
                            continue;
                        }
                        else if(choiceSupply == 4 && quantity*1000 <= inventory[3]){
                            inventory[4] += quantity*8.00;
                            inventory[3] -= quantity*1000;
                            continue;
                        }
                        else{
                            system("cls");
                            cout << "You do not have enough of that item to sell!" << endl;
                            system("pause");
                            continue;
                        }
                    }
                }
            }
        }
    }
}

void advertiserMenu(string companyName, long double inventory[5], int advertiser, string name, int advertisements[4]){
    // Allows player to buy and sell advertisements

    bool running = true;
    int choiceAdvertise;

    // Main advertisement loop

    while(running){
        system("cls");
        if(advertiser == 0){
            // Player can only access menu if they have an advertiser

            cout << "You do not have an advertiser!" << endl;
            system("pause");
            running = false;
            continue;
        }
        else{
            // Print menu

            cout << companyName << " Advertiser:" << endl;
            cout << advertisers(advertiser) << endl;

            lineBreak(companyName);
            printInventory(inventory);

            lineBreak(companyName);
            cout << "Newspaper Ads: " << advertisements[0] << endl;
            cout << "Radio Ads: " << advertisements[1] << endl;
            cout << "Television Ads: " << advertisements[2] << endl;
            cout << "Celebrity Endorsements: " << advertisements[3] << endl;

            lineBreak(companyName);
            cout << "[0] Exit Menu" << endl;
            cout << "[1] Purchase" << endl;
            cout << "[2] Sell" << endl;

            cout << name << " >>> ";
            cin >> choiceAdvertise;

            if(typeTrap())
                continue;

            if(choiceAdvertise == 0){
                running = false;
                continue;
            }
            else if(choiceAdvertise == 1){
                bool choosing = true;
                while(choosing){
                    // If palyer enters 1, then enter the buying menu

                    system("cls");
                    cout << companyName << " Advertiser:" << endl;
                    cout << advertisers(advertiser) << endl;
                    lineBreak(companyName);
                    printInventory(inventory);
                    lineBreak(companyName);
                    cout << "Newspaper Ads: " << advertisements[0] << endl;
                    cout << "Radio Ads: " << advertisements[1] << endl;
                    cout << "Television Ads: " << advertisements[2] << endl;
                    cout << "Celebrity Endorsements: " << advertisements[3] << endl;
                    lineBreak(companyName);
                    cout << "[0] Exit Menu" << endl;
                    cout << "[1] Newspaper Ads: $10 per day" << endl;
                    cout << "[2] Radio Ads: $30 per day" << endl;
                    cout << "[3] Television Ads: $100 per day" << endl;
                    cout << "[4] Celebrity Endorsements: $1500 per day" << endl;
                    cout << name << " >>> ";
                    cin >> choiceAdvertise;
                    if(typeTrap())
                        continue;

                    // Same premise as with supplier menu, prevent player from entering invalid options, check if they can afford the purchase, then update the variables - this time with the 'advertisements' variable

                    if(choiceAdvertise < 0 || choiceAdvertise > 4){
                        system("cls");
                        cout << "That item does not exist!" << endl;
                        system("pause");
                        continue;
                    }
                    else if(choiceAdvertise == 0){
                        choosing = false;
                        continue;
                    }
                    else{
                        int quantity;
                        cout << "How many do you want? ";
                        cin >> quantity;
                        if(typeTrap())
                            continue;

                        if(quantity < 0){
                            system("cls");
                            cout << "You cannot buy a negative amount!" << endl;
                            system("pause");
                            continue;
                        }
                        else if(choiceAdvertise == 1){
                            if(inventory[4] < quantity*10){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*10;
                                advertisements[0] += quantity;
                                continue;
                            }
                        }
                        else if(choiceAdvertise == 2){
                            if(inventory[4] < quantity*30){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*30;
                                advertisements[1] += quantity;
                                continue;
                            }
                        }
                        else if(choiceAdvertise == 3){
                            if(inventory[4] < quantity*100){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*100;
                                advertisements[2] += quantity;
                                continue;
                            }
                        }
                        else if(choiceAdvertise == 4){
                            if(inventory[4] < quantity*1500){
                                system("cls");
                                cout << "You do not have enough money!" << endl;
                                system("pause");
                                continue;
                            }
                            else{
                                inventory[4] -= quantity*1500;
                                advertisements[3] += quantity;
                                continue;
                            }
                        }
                    }
                }
            }
            else if(choiceAdvertise == 2){
                // If the player enters 2, then open the seller menu

                bool choosing = true;
                while(choosing){
                    system("cls");
                    cout << companyName << " Advertiser:" << endl;
                    cout << advertisers(advertiser) << endl;
                    lineBreak(companyName);
                    printInventory(inventory);
                    lineBreak(companyName);
                    cout << "Newspaper Ads: " << advertisements[0] << endl;
                    cout << "Radio Ads: " << advertisements[1] << endl;
                    cout << "Television Ads: " << advertisements[2] << endl;
                    cout << "Celebrity Endorsements: " << advertisements[3] << endl;
                    lineBreak(companyName);
                    cout << "[0] Exit Menu" << endl;
                    cout << "[1] Newspaper Ads" << endl;
                    cout << "[2] Radio Ads" << endl;
                    cout << "[3] Television Ads" << endl;
                    cout << "[4] Celebrity Endorsements" << endl;
                    cout << name << " >>> ";
                    cin >> choiceAdvertise;
                    if(typeTrap())
                        continue;

                    // Again... same thing as with the supplier, prevent invalid options, check if the player has enough to sell, then update the variables

                    if(choiceAdvertise < 0 || choiceAdvertise > 4){
                        system("cls");
                        cout << "That item does not exist!" << endl;
                        system("pause");
                        continue;
                    }
                    else if(choiceAdvertise == 0){
                        choosing = false;
                        continue;
                    }
                    else{
                        int quantity;
                        cout << "How many do you want to sell? ";
                        cin >> quantity;
                        if(typeTrap())
                            continue;

                        if(quantity < 0){
                            system("cls");
                            cout << "You cannot sell a negative amount!" << endl;
                            system("pause");
                            continue;
                        }
                        else if(choiceAdvertise == 1 && quantity <= advertisements[0]){
                            advertisements[0] -= quantity;
                            continue;
                        }
                        else if(choiceAdvertise == 2 && quantity <= advertisements[1]){
                            advertisements[1] -= quantity;
                            continue;
                        }
                        else if(choiceAdvertise == 3 && quantity <= advertisements[2]){
                            advertisements[2] -= quantity;
                            continue;
                        }
                        else if(choiceAdvertise == 4 && quantity <= advertisements[3]){
                            advertisements[3] -= quantity;
                            continue;
                        }
                        else{
                            system("cls");
                            cout << "You do not have enough of that item to sell!" << endl;
                            system("pause");
                            continue;
                        }
                    }
                }
            }
        }
    }
}

void employmentMenu(string companyName, long double inventory[5], int &supplier, int &advertiser, string name){
    bool running = true;
    int choiceEmploy;
    while(running){
        system("cls");
        cout << companyName << " Employments" << endl;
        lineBreak(companyName);
        printInventory(inventory);
        lineBreak(companyName);
        cout << "[0] Exit Menu" << endl;
        cout << "[1] Supplier" << endl;
        cout << "[2] Advertiser" << endl;
        cout << name << " >>> ";
        cin >> choiceEmploy;
        if(typeTrap())
            continue;

        if(choiceEmploy == 0){
            running = false;
            continue;
        }
        else if(choiceEmploy == 1){
            bool choosing = true;
            while(choosing){
                system("cls");
                cout << companyName << " Supplier:" << endl;
                cout << suppliers(supplier) << endl;
                lineBreak(companyName);
                printInventory(inventory);
                lineBreak(companyName);
                cout << "[0] Exit Menu" << endl;
                cout << "[1] " << suppliers(1) << "\t\t\t$10.50 per day" << endl;
                cout << "[2] " << suppliers(2) << "\t\t\t$13.70 per day" << endl;
                cout << "[3] " << suppliers(3) << "\t\t\t\t$20.00 per day" << endl;
                cout << "[4] " << suppliers(4) << "\t\t\t\t$52.60 per day" << endl;
                cout << "[5] " << suppliers(5) << "\t\t\t\t$120.00 per day" << endl;
                cout << "[6] " << suppliers(6) << "\t\t\t$258.90 per day" << endl;
                cout << "[7] " << suppliers(7) << "\t\t\t\t$372.10 per day" << endl;
                cout << "[8] " << suppliers(8) << "\t\t\t\t$785.30 per day" << endl;
                cout << "[9] " << suppliers(9) << "\t\t\t\t$1000.00 per day" << endl;
                cout << "[10] " << suppliers(10) << "\t\t\t$1000000.00 per day" << endl;
                cout << name << " >>> ";
                cin >> choiceEmploy;
                if(typeTrap())
                    continue;

                if(choiceEmploy > 10 || choiceEmploy < 0){
                    system("cls");
                    cout << "That item does not exist!" << endl;
                    system("pause");
                    continue;
                }
                else if(choiceEmploy == 0){
                    choosing = false;
                    continue;
                }
                else if(choiceEmploy == 1){
                    if(inventory[4] < 10.50){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 10.50;
                        supplier = 1;
                    }
                }
                else if(choiceEmploy == 2){
                    if(inventory[4] < 13.70){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 13.70;
                        supplier = 2;
                    }
                }
                else if(choiceEmploy == 3){
                    if(inventory[4] < 20){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 20;
                        supplier = 3;
                    }
                }
                else if(choiceEmploy == 4){
                    if(inventory[4] < 52.60){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 52.60;
                        supplier = 4;
                    }
                }
                else if(choiceEmploy == 5){
                    if(inventory[4] < 120){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 120;
                        supplier = 5;
                    }
                }
                else if(choiceEmploy == 6){
                    if(inventory[4] < 258.90){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 258.90;
                        supplier = 6;
                    }
                }
                else if(choiceEmploy == 7){
                    if(inventory[4] < 372.10){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 372.10;
                        supplier = 7;
                    }
                }
                else if(choiceEmploy == 8){
                    if(inventory[4] < 785.30){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 785.30;
                        supplier = 8;
                    }
                }
                else if(choiceEmploy == 9){
                    if(inventory[4] < 1000){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 1000;
                        supplier = 9;
                    }
                }
                else if(choiceEmploy == 10){
                    if(inventory[4] < 1000000){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 1000000;
                        supplier = 10;
                    }
                }
            }
        }
        else if(choiceEmploy == 2){
            bool choosing = true;
            while(choosing){
                system("cls");
                cout << companyName << " Advertiser:" << endl;
                cout << advertisers(advertiser) << endl;
                lineBreak(companyName);
                printInventory(inventory);
                lineBreak(companyName);
                cout << "[0] Exit Menu" << endl;
                cout << "[1] " << advertisers(1) << "\t\t\t$10.50 per day" << endl;
                cout << "[2] " << advertisers(2) << "\t\t$13.70 per day" << endl;
                cout << "[3] " << advertisers(3) << "\t\t$20.00 per day" << endl;
                cout << "[4] " << advertisers(4) << "\t\t\t$52.60 per day" << endl;
                cout << "[5] " << advertisers(5) << "\t\t\t\t$120.00 per day" << endl;
                cout << "[6] " << advertisers(6) << "\t\t$258.90 per day" << endl;
                cout << "[7] " << advertisers(7) << "\t$372.10 per day" << endl;
                cout << "[8] " << advertisers(8) << "\t$785.30 per day" << endl;
                cout << "[9] " << advertisers(9) << "\t\t$1000.00 per day" << endl;
                cout << "[10] " << advertisers(10) << "\t\t\t$1000000.00 per day" << endl;
                cout << name << " >>> ";
                cin >> choiceEmploy;
                if(typeTrap())
                    continue;

                if(choiceEmploy > 10 || choiceEmploy < 0){
                    system("cls");
                    cout << "That item does not exist!" << endl;
                    system("pause");
                    continue;
                }
                else if(choiceEmploy == 0){
                    choosing = false;
                    continue;
                }
                else if(choiceEmploy == 1){
                    if(inventory[4] < 10.50){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 10.50;
                        advertiser = 1;
                    }
                }
                else if(choiceEmploy == 2){
                    if(inventory[4] < 13.70){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 13.70;
                        advertiser = 2;
                    }
                }
                else if(choiceEmploy == 3){
                    if(inventory[4] < 20){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 20;
                        advertiser = 3;
                    }
                }
                else if(choiceEmploy == 4){
                    if(inventory[4] < 52.60){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 52.60;
                        advertiser = 4;
                    }
                }
                else if(choiceEmploy == 5){
                    if(inventory[4] < 120){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 120;
                        advertiser = 5;
                    }
                }
                else if(choiceEmploy == 6){
                    if(inventory[4] < 258.90){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 258.90;
                        advertiser = 6;
                    }
                }
                else if(choiceEmploy == 7){
                    if(inventory[4] < 372.10){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 372.10;
                        advertiser = 7;
                    }
                }
                else if(choiceEmploy == 8){
                    if(inventory[4] < 785.30){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 785.30;
                        advertiser = 8;
                    }
                }
                else if(choiceEmploy == 9){
                    if(inventory[4] < 1000){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 1000;
                        advertiser = 9;
                    }
                }
                else if(choiceEmploy == 10){
                    if(inventory[4] < 1000000){
                        system("cls");
                        cout << "You do not have enough money!" << endl;
                        system("pause");
                        continue;
                    }
                    else{
                        inventory[4] -= 1000000;
                        advertiser = 10;
                    }
                }
            }
        }
    }
}

void locationMenu(string companyName, long double inventory[5], string name, int locations[6]){
    bool running = true;
    int choiceLocation;
    while(running){
        system("cls");
        cout << companyName << " Locations" << endl;
        lineBreak(companyName);
        printInventory(inventory);
        lineBreak(companyName);
        cout << "Lawn Stands: \t\t"     << locations[0] << endl;
        cout << "Corner Stores: \t\t" << locations[1] << endl;
        cout << "Strip Malls: \t\t" << locations[2] << endl;
        cout << "Recruitment Offices: \t" << locations[3] << endl;
        cout << "Websites: \t\t" << locations[4] << endl;
        cout << "Sponsorships: \t\t" << locations[5] << endl;
        lineBreak(companyName);
        cout << "[0] Exit Menu" << endl;
        cout << "[1] Purchase" << endl;
        cout << "[2] Sell" << endl;
        cout << name << " >>> ";
        cin >> choiceLocation;
        if(typeTrap())
            continue;

        if(choiceLocation == 0){
            running = false;
            continue;
        }
        else if(choiceLocation == 1){
            bool choosing = true;
            while(choosing){
                system("cls");
                cout << companyName << " Locations" << endl;
                lineBreak(companyName);
                printInventory(inventory);
                lineBreak(companyName);
                cout << "Lawn Stands: \t\t" << locations[0] << endl;
                cout << "Corner Stores: \t\t" << locations[1] << endl;
                cout << "Strip Malls: \t\t" << locations[2] << endl;
                cout << "Recruitment Offices: \t" << locations[3] << endl;
                cout << "Websites: \t\t" << locations[4] << endl;
                cout << "Sponsorships: \t\t" << locations[5] << endl;
                lineBreak(companyName);
                cout << "[0] Exit Menu" << endl;
                cout << "[1] Lawn Stands         $30.00" << endl;
                cout << "[2] Corner Stores       $20.00 per day" << endl;
                cout << "[3] Strip Malls         $150.00 per day" << endl;
                cout << "[4] Recruitment Offices $500.00 per day" << endl;
                cout << "[5] Websites            $1000.00 per day" << endl;
                cout << "[6] Sponsorships        $5000.00 per day" << endl;
                cout << name << " >>> ";
                cin >> choiceLocation;
                if(typeTrap())
                    continue;

                if(choiceLocation == 0){
                    choosing = false;
                    continue;
                }
                else if(choiceLocation > 6 || choiceLocation < 0){
                    system("cls");
                    cout << "That item does not exist!" << endl;
                    system("pause");
                }
                else if(choiceLocation == 1 && inventory[4] >= 30){
                    locations[0] += 1;
                    inventory[4] -= 30;
                }
                else if(choiceLocation == 2 && inventory[4] >= 20){
                    locations[1] += 1;
                    inventory[4] -= 20;
                }
                else if(choiceLocation == 3 && inventory[4] >= 150){
                    locations[2] += 1;
                    inventory[4] -= 150;
                }
                else if(choiceLocation == 4 && inventory[4] >= 500){
                    locations[3] += 1;
                    inventory[4] -= 500;
                }
                else if(choiceLocation == 5 && inventory[4] >= 1000){
                    locations[4] += 1;
                    inventory[4] -= 1000;
                }
                else if(choiceLocation == 6 && inventory[4] >= 5000){
                    locations[5] += 1;
                    inventory[4] -= 5000;
                }
                else{
                    system("cls");
                    cout << "You do not have enough money!" << endl;
                    system("pause");
                }
            }
        }
        else if(choiceLocation == 2){
            bool choosing = true;
            while(choosing){
                system("cls");
                cout << companyName << " Locations" << endl;
                lineBreak(companyName);
                printInventory(inventory);
                lineBreak(companyName);
                cout << "Lawn Stands: \t\t" << locations[0] << endl;
                cout << "Corner Stores: \t\t" << locations[1] << endl;
                cout << "Strip Malls: \t\t" << locations[2] << endl;
                cout << "Recruitment Offices: \t" << locations[3] << endl;
                cout << "Websites: \t\t" << locations[4] << endl;
                cout << "Sponsorships: \t\t" << locations[5] << endl;
                lineBreak(companyName);
                cout << "[0] Exit Menu" << endl;
                cout << "[1] Lawn Stands         $15.00" << endl;
                cout << "[2] Corner Stores       $15.00" << endl;
                cout << "[3] Strip Malls         $80.00" << endl;
                cout << "[4] Recruitment Offices $350.00" << endl;
                cout << "[5] Websites            $800.00" << endl;
                cout << "[6] Sponsorships        $4500.00" << endl;
                cout << name << " >>> ";
                cin >> choiceLocation;
                if(typeTrap())
                    continue;

                if(choiceLocation == 0){
                    choosing = false;
                    continue;
                }
                else if(choiceLocation > 6 || choiceLocation < 0){
                    system("cls");
                    cout << "That item does not exist!" << endl;
                    system("pause");
                }
                else if(choiceLocation == 1 && locations[0] > 0){
                    locations[0] -= 1;
                    inventory[4] += 15;
                }
                else if(choiceLocation == 2 && locations[1] > 0){
                    locations[1] -= 1;
                    inventory[4] += 15;
                }
                else if(choiceLocation == 3 && locations[2] > 0){
                    locations[2] -= 1;
                    inventory[4] += 80;
                }
                else if(choiceLocation == 4 && locations[3] > 0){
                    locations[3] -= 1;
                    inventory[4] += 350;
                }
                else if(choiceLocation == 5 && locations[4] > 0){
                    locations[4] -= 1;
                    inventory[4] += 800;
                }
                else if(choiceLocation == 6 && locations[5] > 0){
                    locations[5] -= 1;
                    inventory[4] += 4500;
                }
                else{
                    system("cls");
                    cout << "You do not own that location!" << endl;
                    system("pause");
                }
            }
        }
    }
}

void startDay(string companyName, long double inventory[5], string name, long int &customers, int advertiser, int &day, int locations[6], int advertisements[4], int supplier, long double reputation){
    long int newCustomers;

    system("cls");

    cout << name << "'s Day " << day << " Statistics" << endl;
    lineBreak(companyName);
    newCustomers = ceil((rand()%(advertiser + 2)*locations[0]
                    + rand()%(advertiser*2 + 3)*locations[1]
                    + rand()%(advertiser*3 + 4)*locations[2]
                    + rand()%(advertiser*3 + 7)*locations[3]
                    + rand()%(advertiser*5 + 9)*locations[4]
                    + rand()%(advertiser*7 + 15)*locations[5]
                    + advertisements[0]*advertiser*1
                    + advertisements[1]*advertiser*2
                    + advertisements[2]*advertiser*3
                    + advertisements[3]*advertiser*4)*reputation)+1;

    if(inventory[0] < newCustomers){
        newCustomers = (int)inventory[0];
    }
    if(inventory[1] < newCustomers*35){
        newCustomers = (int)inventory[1]/35;
    }
    if(inventory[2] < customers){
        customers = (int)inventory[2];
    }
    if(inventory[3] < customers*5){
        customers = (int)inventory[3]/5;
    }

    inventory[0] -= newCustomers;
    inventory[1] -= newCustomers*35;
    inventory[2] -= customers;
    inventory[3] -= customers*5;

    cout << "New Customers: " << newCustomers << endl;
    cout << "Returning Customers: " << customers << endl;
    lineBreak(companyName);

    cout << setprecision(2) << fixed << "\"Medicine\" Sales: $" << newCustomers*19.99*(1+supplier/10) << endl;
    cout << "Contract Payments: $" << customers*4.99*(1+supplier/10) << endl;
    lineBreak(companyName);

    cout << "Total Returns: $" << newCustomers*19.99*(1+supplier/10) + customers*4.99*(1+supplier/10) << endl;
    cout << setprecision(0);

    inventory[4] += newCustomers*19.99*(1+supplier/10) + customers*4.99*(1+supplier/10);
    customers += newCustomers;
    day++;

    system("pause");
}

string suppliers(int id){
    if(id == 0){
        return "None";
    }
    else if(id == 1){
        return "Totally Legal Guy";
    }
    else if(id == 2){
        return "Your 17th Cousin";
    }
    else if(id == 3){
        return "Moderno";
    }
    else if(id == 4){
        return "Phizer";
    }
    else if(id == 5){
        return "AstroZencio";
    }
    else if(id == 6){
        return "Proctor&Game";
    }
    else if(id == 7){
        return "Sanofo";
    }
    else if(id == 8){
        return "AbsVie";
    }
    else if(id == 9){
        return "NovaArtist";
    }
    else if(id == 10){
        return "MOLE PEOPLE";
    }
    else{
        return "ERROR: Does Not Exist";
    }
}

string advertisers(int id){
    if(id == 0){
        return "None";
    }
    else if(id == 1){
        return "The Ad Guy";
    }
    else if(id == 2){
        return "Your Ad Here";
    }
    else if(id == 3){
        return "Get Rich Quick!";
    }
    else if(id == 4){
        return "Uncle Sam";
    }
    else if(id == 5){
        return "TBD";
    }
    else if(id == 6){
        return "Conspiracies.net";
    }
    else if(id == 7){
        return "idk what to put here";
    }
    else if(id == 8){
        return "Great Value Advertising";
    }
    else if(id == 9){
        return "Facedook Ads";
    }
    else if(id == 10){
        return "Goggle Ads";
    }
    else{
        return "ERROR: Does Not Exist";
    }
}

void createSaveFile(int saveID){
    ostringstream text2;
    ostringstream msg2;
    msg2 << "saves/" << saveID << ".txt";
    string str2 = "day:\ninventory[0]:\ninventory[1]:\ninventory[2]:\ninventory[3]:\ninventory[4]:\nlocations[0]:\nlocations[1]:\nlocations[2]:\nlocations[3]:\nlocations[4]:\nlocations[5]:\nadvertisements[0]:\nadvertisements[1]:\nadvertisements[2]:\nadvertisements[3]:\nreputation:\nsupplier:\nadvertiser:\nprevCustomers:\ncustomers:\nname:\ncompanyName:\nEND";
    ofstream out_file(msg2.str().c_str());
    out_file << str2;
    return;
}

void loadData(int& saveID, int& day, long double inventory[5], int locations[6], int advertisements[4], long double& reputation, int& supplier, int& advertiser, long int& prevCustomers, long int& customers, string& name, string& companyName){
    string startDEL, stopDEL, strNew;
    unsigned firstLim, lastLim;

    string delimiters[23] = {"day:", "inventory[0]:", "inventory[1]:", "inventory[2]:", "inventory[3]:", "inventory[4]:", "locations[0]:", "locations[1]:", "locations[2]:", "locations[3]:", "locations[4]:", "locations[5]:", "advertisements[0]:", "advertisements[1]:", "advertisements[2]:", "advertisements[3]:", "reputation:", "supplier:", "advertiser:", "prevCustomers:", "customers:", "name:", "companyName:"};

    ostringstream text3;
    ostringstream msg3;

    msg3 << "saves/" << saveID << ".txt";
    ifstream in_file(msg3.str().c_str());
    text3 << in_file.rdbuf();
    string str3 = text3.str();

    for(int i = 0; i < 23; i++){

        firstLim = 0;
        lastLim = 0;

        startDEL = delimiters[i];
        if(i != 22){
            stopDEL = delimiters[i+1];
        }
        else{
            stopDEL = "END";
        }

        firstLim = str3.find(startDEL);
        lastLim = str3.find(stopDEL);
        strNew = str3.substr(firstLim, lastLim-firstLim);
        strNew = strNew.substr(delimiters[i].size());
        strNew = strNew.substr(strNew.size()-1);

        if(i == 0){
            day = atoi(strNew.data());
        }
        if(i == 1){
            inventory[0] = atoi(strNew.data());
        }
        if(i == 2){
            inventory[1] = atoi(strNew.data());
        }
        if(i == 3){
            inventory[2] = atoi(strNew.data());
        }
        if(i == 4){
            inventory[3] = atoi(strNew.data());
        }
        if(i == 5){
            inventory[4] = atoi(strNew.data())/100.00;
        }
        if(i == 6){
            locations[0] = atoi(strNew.data());
        }
        if(i == 7){
            locations[1] = atoi(strNew.data());
        }
        if(i == 8){
            locations[2] = atoi(strNew.data());
        }
        if(i == 9){
            locations[3] = atoi(strNew.data());
        }
        if(i == 10){
            locations[4] = atoi(strNew.data());
        }
        if(i == 11){
            locations[5] = atoi(strNew.data());
        }
        if(i == 12){
            advertisements[0] = atoi(strNew.data());
        }
        if(i == 13){
            advertisements[1] = atoi(strNew.data());
        }
        if(i == 14){
            advertisements[2] = atoi(strNew.data());
        }
        if(i == 15){
            advertisements[3] = atoi(strNew.data());
        }
        if(i == 16){
            reputation = atoi(strNew.data())/100.00;
        }
        if(i == 17){
            supplier = atoi(strNew.data());
        }
        if(i == 18){
            advertiser = atoi(strNew.data());
        }
        if(i == 19){
            prevCustomers = atoi(strNew.data());
        }
        if(i == 20){
            customers = atoi(strNew.data());
        }
        if(i == 21){
            name = strNew;
        }
        if(i == 22){
            companyName = strNew;
        }
    }
}

void saveData(int saveID, int day, long double inventory[5], int locations[6], int advertisements[4], long double reputation, int supplier, int advertiser, long int prevCustomers, long int customers, string name, string companyName){
    ostringstream msg5;
    msg5 << "saves/" << saveID << ".txt";
    ostringstream msg4;
    msg4 << "day:" << day << "\ninventory[0]:" << inventory[0] << "\ninventory[1]:" << inventory[1] << "\ninventory[2]:" << inventory[2] << "\ninventory[3]:" << inventory[3] << "\ninventory[4]:" << inventory[4]*100 << "\nlocations[0]:" << locations[0] << "\nlocations[1]:" << locations[1] << "\nlocations[2]:" << locations[2] << "\nlocations[3]:" << locations[3] << "\nlocations[4]:" << locations[4] << "\nlocations[5]:" << locations[5] << "\nadvertisements[0]:" << advertisements[0] << "\nadvertisements[1]:" << advertisements[1] << "\nadvertisements[2]:" << advertisements[2] << "\nadvertisements[3]:" << advertisements[3] << "\nreputation:" << reputation*100 << "\nsupplier:" << supplier << "\nadvertiser:" << advertiser << "\nprevCustomers:" << prevCustomers << "\ncustomers:" << customers << "\nname:" << name << "\ncompanyName:" << companyName;
    ofstream out_file(msg5.str().c_str());
    out_file << msg4.str();
    out_file.close();
}
