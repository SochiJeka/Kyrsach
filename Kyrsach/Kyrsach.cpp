#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <iterator>>
#include <windows.h>
#ifdef max
#undef max
#endif

using namespace std;
string fileUsers = "users.txt";
string fileBus = "bus.txt";
const string PROGR_INFO = "author Evgeny Sochinsky";
int const countOfUsers = 10;
int const countOfBus = 10;

struct Bus {
    string number;
    vector<std::string> route;
    int numberOfVacancies;
    int time;
};

struct User {
    string login;
    string password;
};

istream& operator>>(istream& is, Bus& bus) {
    is >> bus.number;
    int routeSize;
    is >> routeSize;
    bus.route.resize(routeSize);
    for (int i = 0; i < routeSize; i++) {
        is >> bus.route[i];
    }
    is >> bus.numberOfVacancies;
    is >> bus.time;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Bus& bus) {
    os << "Number: " << bus.number << std::endl;
    os << "Free seats: " << bus.numberOfVacancies << std::endl;
    os << "Travel time: " << bus.time << std::endl;
    os << "Route: " << std::endl;
    for (const std::string& stop : bus.route) {
        os << "- " << stop << std::endl;
    }
    return os;
}


int main();

void admMenuStart();

void admMenuBus();

void admMenuUsers();

void userMenuStart();

bool fileExists(const string& filename);

bool isLoginExists(const string& filename, const string& login);

bool loginUser(const string& fileUsers, const string& login, const string& password);

void authorizationMainMenu();

void showUsers(User* users);

void editUser(const string& filename);

void dellUser();

void sortUsers();

void showBus();

void editBus(const std::string& filename);

void showAllBuses();

void addBusToFile(const std::string& filename);

void dellBus();

std::vector<Bus> readBusesFromFile(const std::string& filename);

void sortBuses(const std::string& filename);


void mainMenu() {
    cout << "\033[1;34m**************************************" << endl;
    cout << "* bus schedule                       *" << endl;
    cout << "**************************************" << endl;
    cout << "* \033[1;36m1. Registration                    \033[1;34m*" << endl;
    cout << "* \033[1;36m2. Sign in                         \033[1;34m*" << endl;
    cout << "* \033[1;36m3. Log out                         \033[1;34m*" << endl;
    cout << "**************************************\033[0m" << endl;
};


bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool isLoginExists(const string& fileUsers, const string& login) {
    ifstream file(fileUsers);
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string fileLogin = line.substr(0, pos);
            if (login == fileLogin) {
                return true;
            }
        }
    }
    return false;
}

void registerUser(string& filename) {
    string login, password;

    do {
        cout << "Enter a login: ";
        cin >> login;
        if (isLoginExists(fileUsers, login)) {
            cout << "This login already exists. Try another one." << endl;
        }
    } while (isLoginExists(fileUsers, login));

    cout << "Enter a password: ";
    cin >> password;
    ofstream file(fileUsers, ios::app);
    file << login << ':' << password << endl;
    file.close();
    cout << "Successfully registered." << endl;
};

bool loginUser(const string& fileUsers, const string& login, const string& password) {
    ifstream file(fileUsers);
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string fileLogin = line.substr(0, pos);
            string filePassword = line.substr(pos + 1);
            if (login == fileLogin && password == filePassword) {
                return true;
            }
        }
    }
    return false;
}

void authorizationMainMenu() {

    if (!fileExists(fileUsers)) {
        ofstream file(fileUsers);
        file.close();
    }

    int choice;
    string login, password;
    do {
        while (true) {
            Sleep(2000);
            system("cls");
            mainMenu();
            cout << "select choice: ";
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input, please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (choice == 1 || choice == 2 || choice == 3) {
                break;
            }
            else {
                cout << "Invalid input, please select an item from the existing ones." << endl;
            }
        }
        switch (choice) {
        case 1:
            registerUser(fileUsers);
            break;
        case 2:
            cout << "Enter your login: ";
            cin >> login;
            cout << "Enter your password: ";
            cin >> password;
            if (loginUser(fileUsers, login, password)) {
                choice = 3;
                if (login == "admin") {
                    system("cls");
                    admMenuStart();
                }
                else {
                    system("cls");
                    userMenuStart();
                }
                cout << "You have successfully logged in." << endl;
            }
            else {
                cout << "Incorrect username or password." << endl;
            }
            break;
        case 3:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Incorrect choice." << endl;
            break;
        }
    } while (choice != 3);
}

void admMenuStart() {
    char myChoice;
    cout << "\033[1;34m********************************************" << endl;
    cout << "* Main menu for administrator              *" << endl;
    cout << "********************************************" << endl;
    cout << "* \033[1;36m1: Working with users                    \033[1;34m*" << endl;
    cout << "* \033[1;36m2: Working with buses             \033[1;34m*" << endl;
    cout << "* \033[1;36m9: Exit to main menu                     \033[1;34m*" << endl;
    cout << "* \033[1;36m0: Exiting the program                   \033[1;34m*" << endl;
    cout << "* \033[1;36m?: Program Information                   \033[1;34m*" << endl;
    cout << "********************************************\033[0m" << endl;
tryAgain_am1:
    cout << "\nSelect menu item: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        admMenuUsers();
        break;
    case '2':
        admMenuBus();
        break;
    case '9':
        main();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "There is no such menu item! Try again." << endl;
        break;
    }
    goto tryAgain_am1;
}

void admMenuUsers() {


    char myChoice;
    User users[countOfUsers];
    cout << "\033[1;34m********************************************" << endl;
    cout << "*      Working with users                  *" << endl;
    cout << "********************************************" << endl;
    cout << "* \033[1;36m1: Show details of all users             \033[1;34m*" << endl;
    cout << "* \033[1;36m2: Add user to file                      \033[1;34m*" << endl;
    cout << "* \033[1;36m3: Change user details                   \033[1;34m*" << endl;
    cout << "* \033[1;36m4: Delete user data                      \033[1;34m*" << endl;
    cout << "* \033[1;36m5: Order Users                           \033[1;34m*" << endl;
    cout << "* \033[1;36m9: Back to main menu                     \033[1;34m*" << endl;
    cout << "* \033[1;36m0: Exiting the program                   \033[1;34m*" << endl;
    cout << "* \033[1;36m?: Program Information                   \033[1;34m*" << endl;
    cout << "********************************************\033[0m" << endl;
tryAgain_adm2:
    cout << "\nSelect menu item: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        showUsers(users);
        break;
    case '2':
        registerUser(fileUsers);
        break;
    case '3':
        editUser(fileUsers);
        break;
    case '4':
        dellUser();
        break;
    case '5':
        sortUsers();
        break;
    case '9':
        admMenuStart();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "There is no such menu item! Try again." << endl;
        break;
    }
    goto tryAgain_adm2;
}


void admMenuBus()
{
    char myChoice;
    Bus bus[countOfBus];
    int numberOfBus = 0;
    cout << "\033[1;34m**************************************" << endl;
    cout << "* Working with bus data              *" << endl;
    cout << "**************************************" << endl;
    cout << "* \033[1;36m1: Show Bus Information             \033[1;34m*" << endl;
    cout << "* \033[1;36m2: Add bus entry                    \033[1;34m*" << endl;
    cout << "* \033[1;36m3: Show information about all buse  \033[1;34m*" << endl;
    cout << "* \033[1;36m4: Edit Bus Entry                   \033[1;34m*" << endl;
    cout << "* \033[1;36m5: Delete bus entry                 \033[1;34m*" << endl;
    cout << "* \033[1;36m6: Sorting records                  \033[1;34m*" << endl;
    cout << "* \033[1;36m9: Back to main menu                \033[1;34m*" << endl;
    cout << "* \033[1;36m0: Exiting the program              \033[1;34m*" << endl;
    cout << "* \033[1;36m?: Program Information              \033[1;34m*" << endl;
    cout << "**************************************\033[0m" << endl;
tryAgain_am2:
    cout << "\nSelect menu item: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        showBus();
        break;
    case '2':
        addBusToFile(fileBus);
        break;
    case '3':
        showAllBuses();
        break;
    case '4':
        editBus(fileBus);
        break;
    case '5':
        dellBus();
        break;
    case '6':
        sortBuses(fileBus);
        break;
    case '9':
        admMenuStart();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "There is no such menu item! Try again. " << endl;
        break;
    }
    goto tryAgain_am2;
}


void userMenuStart()
{
    char myChoice;
    Bus bus[countOfBus];
    int numberOfBus = 0;
    cout << "\033[1;34m**************************************" << endl;
    cout << "* Working with data                  *" << endl;
    cout << "**************************************" << endl;
    cout << "* \033[1;36m1: Show Bus Information            \033[1;34m*" << endl;
    cout << "* \033[1;36m2: Sorting records                 \033[1;34m*" << endl;
    cout << "* \033[1;36m9: Back to main menu               \033[1;34m*" << endl;
    cout << "* \033[1;36m0: Exiting the program             \033[1;34m*" << endl;
    cout << "* \033[1;36m?: Program Informatio              \033[1;34m*" << endl;
    cout << "\033[1;34m**************************************" << endl;
tryAgain_um1:
    cout << "\nSelect menu item: ";
    cin >> myChoice;
    switch (myChoice)
    {
    case '1':
        showAllBuses();
        break;
    case '2':
        sortBuses(fileBus);
        break;
    case '9':
        main();
        break;
    case '0':
        exit(0);
    case '?':
        cout << PROGR_INFO << endl;
        break;
    default:
        cout << "There is no such menu item! Try again." << endl;
        break;
    }
    goto tryAgain_um1;
}

void showUsers(User* users) {
    std::ifstream infile("users.txt");
    std::string line;
    while (std::getline(infile, line)) {
        size_t pos = line.find(':');
        std::string login = line.substr(0, pos);
        std::string password = line.substr(pos + 1);

        std::cout << "Login: " << login << ", Password: " << password << "\n";
    }
}

void editUser(const string& filename) {
    cout << "Enter the username of the user you want to change: ";
    string login;
    cin >> login;

    cout << "Enter a new login: ";
    string newLogin;
    cin >> newLogin;

    cout << "Enter a new password: ";
    string newPassword;
    cin >> newPassword;

    ifstream inFile(filename);
    ofstream outFile("temp.txt");
    string line;
    bool foundUser = false;

    while (getline(inFile, line)) {
        size_t pos = line.find(":");
        string currLogin = line.substr(0, pos);
        string currPassword = line.substr(pos + 1);

        if (currLogin == login) {
            if (!newLogin.empty()) {
                currLogin = newLogin;
            }
            if (!newPassword.empty()) {
                currPassword = newPassword;
            }
            line = currLogin + ":" + currPassword;
            foundUser = true;
        }
        outFile << line << endl;
    }

    if (!foundUser) {
        cout << "User with login " << login << " not found." << endl;
    }
    else {
        cout << "Data updated successfully" << endl;
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

void dellUser() {
    cout << "*******************"
        << " Deleting a user "
        << "*******************" << endl;
    string login;
    cout << "Enter user login to delete: ";
    cin >> login;

    ifstream infile("users.txt");
    if (!infile) {
        cerr << "Error: Failed to open file for reading!" << endl;
        return;
    }

    ofstream outfile("temp.txt");
    if (!outfile) {
        cerr << "Error: Failed to open temporary file for writing!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        size_t pos = line.find(':');
        string userLogin = line.substr(0, pos);
        string password = line.substr(pos + 1);

        if (userLogin == login) {
            found = true;
            continue;
        }

        outfile << line << endl;
    }

    infile.close();
    outfile.close();

    if (found) {
        if (remove("users.txt") != 0) {
            cerr << "Error: Unable to delete source file!" << endl;
            return;
        }
        if (rename("temp.txt", "users.txt") != 0) {
            cerr << "Error: Failed to rename temporary file!" << endl;
            return;
        }
        cout << "User deleted!" << endl;
    }
    else {
        cout << "User with login " << login << " not found!" << endl;
    }
}


bool compareUsers(const User& a, const User& b) {
    return a.login < b.password;
}

void sortUsers() {
    ifstream inputFile("users.txt");
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<User> users;
    string line;
    while (getline(inputFile, line)) {
        size_t pos = line.find(':');
        if (pos == string::npos) {
            cerr << "Wrong data format in file!" << endl;
            return;
        }
        string login = line.substr(0, pos);
        string password = line.substr(pos + 1);
        users.push_back({ login, password });
    }

    inputFile.close();

    sort(users.begin(), users.end(), compareUsers);

    ofstream outputFile("users.txt");
    if (!outputFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (const auto& user : users) {
        outputFile << user.login << ":" << user.password << endl;
    }

    outputFile.close();

    cout << "Data successfully sorted and written to file!" << endl;
}

void showAllBuses() {
    ifstream infile(fileBus);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    else {
        cout << "Error opening file " << fileBus << " for reading" << endl;
    }

}

void showBus() {
    int numberOfBus = 0;
    cout << "Enter bus number" << endl;
    cin >> numberOfBus;
    fstream infile(fileBus, ios::in);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.find("Number: " + to_string(numberOfBus)) != string::npos) {
                cout << line << endl;
                getline(infile, line); // read and print the next line
                cout << line << endl;
                getline(infile, line); // read and print the next line
                cout << line << endl;
                cout << "Route:" << endl;
                while (getline(infile, line) && line.find("-") != string::npos) {
                    cout << line << endl;
                }
                break;
            }
        }
        infile.close();
    }
    else {
        cout << "Error opening file " << fileBus << " for reading" << endl;
    }
}


void editBus(const std::string& filename) {
    std::cin.ignore();
    std::cout << "Enter the number of the bus to edit: ";
    std::string number;
    std::getline(std::cin, number);

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file " << filename << " for reading" << std::endl;
        return;
    }

    std::vector<Bus> buses;
    std::string line;
    Bus bus;
    bool busFound = false;
    while (std::getline(infile, line)) {
        if (line.find("Number: ") == 0) {
            if (!bus.number.empty()) {
                buses.push_back(bus);
                bus = Bus();
            }
            bus.number = line.substr(8);
            if (bus.number == number) {
                busFound = true;
            }
        }
        else if (line.find("Free seats: ") == 0) {
            bus.numberOfVacancies = std::stoi(line.substr(12));
        }
        else if (line.find("Travel time: ") == 0) {
            bus.time = std::stoi(line.substr(13));
        }
        else if (line.find("- ") == 0) {
            bus.route.push_back(line.substr(2));
        }
        else if (line == "") {
            buses.push_back(bus);
            bus = Bus();
        }
    }
    if (!bus.number.empty()) {
        buses.push_back(bus);
    }

    if (!busFound) {
        std::cout << "Bus with number " << number << " was not found." << std::endl;
        return;
    }

    std::cout << "Enter new number of vacancies: ";
    std::string input;
    std::getline(std::cin, input);
    int newVacancies = std::stoi(input);

    for (Bus& bus : buses) {
        if (bus.number == number) {
            bus.numberOfVacancies = newVacancies;
        }
    }


    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file " << filename << " for writing" << std::endl;
        return;
    }

    for (const Bus& bus : buses) {
        outfile << "Number: " << bus.number << std::endl;
        outfile << "Free seats: " << bus.numberOfVacancies << std::endl;
        outfile << "Travel time: " << bus.time << std::endl;
        outfile << "Route: " << std::endl;
        for (const std::string& stop : bus.route) {
            outfile << "- " << stop << std::endl;
        }
        outfile << std::endl;
    }

    std::cout << "Information for bus with number " << number << " has been updated." << std::endl;
}


std::vector<Bus> readBusesFromFile(const std::string& filename) {
    std::vector<Bus> buses;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file " << filename << " for reading" << std::endl;
        return buses;
    }

    std::string line;
    Bus bus;
    bool reading_route = false;
    while (std::getline(infile, line)) {
        if (line.find("Number: ") != std::string::npos) {
            if (reading_route) {
                buses.push_back(bus);
                bus = Bus();
                reading_route = false;
            }
            bus.number = std::stoi(line.substr(line.find("Number: ") + 8));
        }
        else if (line.find("Free seats: ") != std::string::npos) {
            bus.numberOfVacancies = std::stoi(line.substr(line.find("Free seats: ") + 13));
        }
        else if (line.find("Travel time: ") != std::string::npos) {
            bus.time = std::stoi(line.substr(line.find("Travel time: ") + 14));
        }
        else if (line.find("Route:") != std::string::npos) {
            reading_route = true;
        }
        else if (reading_route && !line.empty()) {
            bus.route.push_back(line.substr(2));
        }
    }
    if (reading_route && !bus.route.empty()) {
        buses.push_back(bus);
    }

    infile.close();
    return buses;
}

void addBusToFile(const std::string& filename) {
    std::ofstream outfile(filename, std::ios::app);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file " << filename << " for writing" << std::endl;
        return;
    }
    Bus newBus;
    std::cout << "Enter bus number: ";
    std::cin >> newBus.number;
    std::cin.ignore();
    std::cout << "Enter number of vacancies: ";
    std::cin >> newBus.numberOfVacancies;
    std::cin.ignore();
    std::cout << "Enter travel time: ";
    std::cin >> newBus.time;
    std::cin.ignore();
    std::string stop;
    while (true) {
        std::cout << "Enter a stop on the route (or type 'done' to finish): ";
        std::getline(std::cin, stop);
        if (stop == "done") {
            break;
        }
        newBus.route.push_back(stop);
    }

    outfile << "Number: " << newBus.number << std::endl;
    outfile << "Free seats: " << newBus.numberOfVacancies << std::endl;
    outfile << "Travel time: " << newBus.time << std::endl;
    outfile << "Route: " << std::endl;
    for (const std::string& stop : newBus.route) {
        outfile << "- " << stop << std::endl;
    }
    outfile << std::endl;

    outfile.close();
    std::cout << "Bus data has been written to the file " << filename << std::endl;
}


void dellBus() {
    string tempFileBus = "temp_bus.txt";
    string busNumber;
    cout << "Enter bus number" << endl;
    cin.ignore();
    getline(cin, busNumber);
    ifstream infile(fileBus);
    ofstream outfile(tempFileBus);
    if (infile.is_open() && outfile.is_open()) {
        string line;
        bool busFound = false;
        while (getline(infile, line)) {
            if (line.find("Number: " + busNumber) != string::npos) {
                // Found the bus to delete
                busFound = true;
                // Skip this bus (i.e., do not write it to the output file)
                while (getline(infile, line) && line != "") {}
                continue;
            }
            outfile << line << endl;
        }
        infile.close();
        outfile.close();
        if (busFound) {
            // Delete the original file and rename the temporary file to the original file
            remove(fileBus.c_str());
            rename(tempFileBus.c_str(), fileBus.c_str());
            cout << "bus with number " << busNumber << " removed." << endl;
        }
        else {
            cout << "bus with number " << busNumber << " not found." << endl;
            remove(tempFileBus.c_str());
        }
    }
    else {
        cout << "Error when deleting a bus. Files not open." << endl;
    }
}


bool compareBuses(const Bus& bus1, const Bus& bus2) {
    return bus1.number > bus2.number;
}

void sortBuses(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file " << filename << " for reading" << std::endl;
        return;
    }

    std::vector<Bus> buses;
    std::string line;
    Bus bus;
    while (std::getline(infile, line)) {
        if (line.find("Number: ") == 0) {
            bus.number = line.substr(8);
        }
        else if (line.find("Free seats: ") == 0) {
            bus.numberOfVacancies = std::stoi(line.substr(12));
        }
        else if (line.find("Travel time: ") == 0) {
            bus.time = std::stoi(line.substr(13));
        }
        else if (line.find("- ") == 0) {
            bus.route.push_back(line.substr(2));
        }
        else if (line == "") {
            buses.push_back(bus);
            bus = Bus();
        }
    }
    if (!bus.number.empty()) {
        buses.push_back(bus);
    }

    std::sort(buses.begin(), buses.end(), compareBuses);

    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file " << filename << " for writing" << std::endl;
        return;
    }

    for (const Bus& bus : buses) {
        outfile << "Number: " << bus.number << std::endl;
        outfile << "Free seats: " << bus.numberOfVacancies << std::endl;
        outfile << "Travel time: " << bus.time << std::endl;
        outfile << "Route: " << std::endl;
        for (const std::string& stop : bus.route) {
            outfile << "- " << stop << std::endl;
        }
        outfile << std::endl;
    }

    std::cout << "Bus data has been sorted by number and written to the file " << filename << std::endl;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::map<std::string, Bus> buses;
    authorizationMainMenu();

    return 0;
}
