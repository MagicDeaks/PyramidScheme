#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

void lineBreak(string companyName);
void printInventory(double inventory[5]);

bool typeTrap();

void supplierMenu(string companyName, double inventory[5], int supplier, string name);
void advertiserMenu(string companyName, double inventory[5], int advertiser, string name, int advertisements[4]);
void employmentMenu(string companyName, double inventory[5], int &supplier, int &advertiser, string name);
void locationMenu(string companyName, double inventory[5], string name, int locations[6]);
void startDay(string companyName, double inventory[5], string name, int &customers, int advertiser, int &day, int locations[6], int advertisements[4]);

string suppliers(int id);
string advertisers(int id);

int main(){
    string name, companyName;
    bool running = true;
    double inventory[5] = {0, 0, 0, 0, 100};
    int locations[6] = {0, 0, 0, 0, 0, 0};
    int advertisements[4] = {0, 0, 0, 0};
    double supplierPrices[10] = {10.50, 13.70, 20.00, 52.60, 120.00, 258.90, 372.10, 785.30, 1000.00, 1000000.00};
    int choiceMain;
    int supplier = 0;
    int customers = 0;
    int advertiser = 0;
    int day = 1;

    cout << "What is your name? ";
    cin >> name;
    cout << "What is the name of your company? ";
    cin >> companyName;
    while(running){
        system("cls");
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
        else if(choiceMain == 1){
            supplierMenu(companyName, inventory, supplier, name);
        }
        else if(choiceMain == 2){
            advertiserMenu(companyName, inventory, advertiser, name, advertisements);
        }
        else if(choiceMain == 3){
            employmentMenu(companyName, inventory, supplier, advertiser, name);
        }
        else if(choiceMain == 4){
            locationMenu(companyName, inventory, name, locations);
        }
        else if(choiceMain == 5){
            startDay(companyName, inventory, name, customers, advertiser, day, locations, advertisements);
            if(inventory[4] < supplierPrices[advertiser-1]){
                system("cls");
                cout << "You cannot afford your advertiser!" << endl;
                cout << "They have quit!" << endl;
                advertiser = 0;
                system("pause");
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
            }
            else if(supplier != 0){
                inventory[4] -= supplierPrices[supplier-1];
            }
            if(inventory[4] < locations[1]*20){
                system("cls");
                cout << "You cannot afford your Corner Stores!" << endl;
                cout << "They have quit!" << endl;
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
                locations[5] = 0;
                system("pause");
            }
            else if(locations[5] != 0){
                inventory[4] -= locations[1]*5000;
            }
        }
    }
    system("pause");
    return 0;
}

void lineBreak(string companyName){
    for(int unsigned i = 0; i < companyName.length(); i++){
            cout << "=";
        }
        cout << "==========" << endl;
}

void printInventory(double inventory[5]){
    cout << "Inventory" << endl;
    cout << "Containers: \t" << inventory[0] << " units" << endl;
    cout << "Chalk: \t\t" << inventory[1] << " mg" << endl;
    cout << "Paper: \t\t" << inventory[2] << " sheets" << endl;
    cout << "Ink: \t\t" << inventory[3] << " ml" << endl;
    cout << "Money: \t\t$" << setprecision(2) << fixed << inventory[4] << endl;
    cout << setprecision(0) << endl;
}

bool typeTrap(){
    if(!cin.good()){
        cout << "ERROR: Invalid Input" << endl;
        cin.clear();
        cin.ignore(128, '\n');
        system("pause");
        return true;
    }
    return false;
}

void supplierMenu(string companyName, double inventory[5], int supplier, string name){
    bool running = true;
    int choiceSupply;
    while(running){
        system("cls");
        if(supplier == 0){
            cout << "You do not have a supplier!" << endl;
            system("pause");
            running = false;
            continue;
        }
        else{
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
                running = false;
                continue;
            }
            else if(choiceSupply == 1){
                bool choosing = true;
                while(choosing){
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
                        system("cls");
                        cout << "That item does not exist!" << endl;
                        system("pause");
                        continue;
                    }
                    else if(choiceSupply == 0){
                        choosing = false;
                        continue;
                    }
                    else{
                        int quantity;
                        cout << "How many do you want? ";
                        cin >> quantity;
                        if(typeTrap())
                            continue;

                        if(choiceSupply == 1){
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
                            if(inventory[4] < quantity*13.62){
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
                        system("cls");
                        cout << "That item does not exist!" << endl;
                        system("pause");
                        continue;
                    }
                    else if(choiceSupply == 0){
                        choosing = false;
                        continue;
                    }
                    else{
                        int quantity;
                        cout << "How many do you want to sell? ";
                        cin >> quantity;
                        if(typeTrap())
                            continue;

                        if(choiceSupply == 1 && quantity <= inventory[0]){
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

void advertiserMenu(string companyName, double inventory[5], int advertiser, string name, int advertisements[4]){
    bool running = true;
    int choiceAdvertise;
    while(running){
        system("cls");
        if(advertiser == 0){
            cout << "You do not have an advertiser!" << endl;
            system("pause");
            running = false;
            continue;
        }
        else{
            cout << companyName << " Advertiser:" << endl;
            cout << advertisers(advertiser) << endl;
            lineBreak(companyName);
            printInventory(inventory);
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
                    system("cls");
                    cout << companyName << " Advertiser:" << endl;
                    cout << advertisers(advertiser) << endl;
                    lineBreak(companyName);
                    printInventory(inventory);
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

                        if(choiceAdvertise == 1){
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
                bool choosing = true;
                while(choosing){
                    system("cls");
                    cout << companyName << " Advertiser:" << endl;
                    cout << advertisers(advertiser) << endl;
                    lineBreak(companyName);
                    printInventory(inventory);
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

                        if(choiceAdvertise == 1 && quantity <= advertisements[0]){
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

void employmentMenu(string companyName, double inventory[5], int &supplier, int &advertiser, string name){
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

void locationMenu(string companyName, double inventory[5], string name, int locations[6]){
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

void startDay(string companyName, double inventory[5], string name, int &customers, int advertiser, int &day, int locations[6], int advertisements[4]){
    int newCustomers;

    system("cls");

    cout << name << "'s Day " << day << " Statistics" << endl;
    lineBreak(companyName);
    newCustomers = rand()%(advertiser + 2)*locations[0]
                    + rand()%(advertiser*2 + 3)*locations[1]
                    + rand()%(advertiser*3 + 4)*locations[2]
                    + rand()%(advertiser*3 + 7)*locations[3]
                    + rand()%(advertiser*5 + 9)*locations[4]
                    + rand()%(advertiser*7 + 15)*locations[5]
                    + advertisements[0]*advertiser*1
                    + advertisements[1]*advertiser*2
                    + advertisements[2]*advertiser*3
                    + advertisements[3]*advertiser*4;

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

    cout << setprecision(2) << fixed << "\"Medicine\" Sales: $" << newCustomers*19.99 << endl;
    cout << "Contract Payments: $" << customers*4.99 << endl;
    lineBreak(companyName);

    cout << "Total Returns: $" << newCustomers*19.99 + customers*4.99 << endl;
    cout << setprecision(0);

    inventory[4] += newCustomers*19.99 + customers*4.99;
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
