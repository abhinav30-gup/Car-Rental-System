#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// -------- Sign_In Class --------
class Sign_In {
public:
    string signName;
    string signPassword;
    string signEmail;
    string signPhone;
    string signAadharcard;

    void signUp();
    bool login();
    bool userExists(const string& username);
    void insertData();
    void cleanInput();
    bool isSignedUp = false;
};

void Sign_In::signUp() {
    cout << "===== User Sign-Up =====\n";
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, signName);
    cout << "Enter your password: ";
    getline(cin, signPassword);
    cout << "Enter your email: ";
    getline(cin, signEmail);
    cout << "Enter your phone number: ";
    getline(cin, signPhone);
    cout << "Enter your Aadhar card number: ";
    getline(cin, signAadharcard);

    if (signName.empty() || signPassword.empty() || signEmail.empty() ||
        signPhone.empty() || signAadharcard.empty()) {
        cout << "Sign up failed. Please fill in all the information.\n";
    } else if (userExists(signName)) {
        cout << "This username already exists.\n";
    } else {
        insertData();
        cleanInput();
        isSignedUp = true;
    }
}

bool Sign_In::login() {
    string name, password;
    cout << "===== User Login =====\n";
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your password: ";
    getline(cin, password);

    ifstream dbFile("usersData.txt");
    string line;
    while (getline(dbFile, line)) {
        stringstream ss(line);
        string storedName, storedPassword, temp;
        getline(ss, storedName, ',');
        getline(ss, storedPassword, ',');

        if (storedName == name && storedPassword == password) {
            cout << "Login successful. Welcome back, " << storedName << "!\n";
            isSignedUp = true;
            dbFile.close();
            return true;
        }
    }
    dbFile.close();
    cout << "Login failed. Invalid username or password.\n";
    return false;
}


bool Sign_In::userExists(const string& username) {
    ifstream dbFile("usersData.txt");
    string line;
    while (getline(dbFile, line)) {
        if (line.find(username) != string::npos) {
            dbFile.close();
            return true;
        }
    }
    dbFile.close();
    return false;
}

void Sign_In::insertData() {
    ofstream dbFile("usersData.txt", ios::app);
    if (dbFile.is_open()) {
        dbFile << signName << "," << signPassword << "," << signEmail << ","
               << signPhone << "," << signAadharcard << "\n";
        dbFile.close();
        cout << "Sign-Up successful. Please proceed to the Car Rental System.\n";
    } else {
        cout << "Failed to connect to the database.\n";
    }
}

void Sign_In::cleanInput() {
    signName = signPassword = signEmail = signPhone = signAadharcard = "";
}

// ------- Car Structure -------
struct Car {
    int id;
    string model;
    string brand;
    double rentPerDay;
    bool isAvailable;

    string toString() const {
        return to_string(id) + "," + brand + "," + model + "," +
               to_string(rentPerDay) + "," + (isAvailable ? "1" : "0");
    }

    static Car fromString(const string& data) {
        Car car;
        stringstream ss(data);
        string token;

        getline(ss, token, ',');
        car.id = stoi(token);

        getline(ss, car.brand, ',');
        getline(ss, car.model, ',');

        getline(ss, token, ',');
        car.rentPerDay = stod(token);

        getline(ss, token, ',');
        car.isAvailable = (token == "1");

        return car;
    }
};

// ------- Car Functions ----------
void displayCar(const Car& car) {
    cout << left << setw(5) << car.id
         << setw(15) << car.brand
         << setw(15) << car.model
         << setw(10) << car.rentPerDay
         << setw(10) << (car.isAvailable ? "Yes" : "No") << endl;
}

void saveCars(Car cars[], int size) {
    ofstream outFile("carsData.txt");
    for (int i = 0; i < size; ++i) {
        outFile << cars[i].toString() << "\n";
    }
    outFile.close();
}

void loadCars(Car cars[], int& size) {
    ifstream inFile("carsData.txt");
    string line;
    size = 0;
    while (getline(inFile, line) && size < 100) {
        cars[size++] = Car::fromString(line);
    }
    inFile.close();
}

void listCars(Car cars[], int size) {
    cout << left << setw(5) << "ID" << setw(15) << "Brand" << setw(15)
         << "Model" << setw(10) << "Rate" << setw(10) << "Available" << endl;
    for (int i = 0; i < size; ++i) {
        displayCar(cars[i]);
    }
}

void rentCar(Car cars[], int size) {
    int id, days;
    cout << "Enter Car ID to rent: ";
    cin >> id;
    for (int i = 0; i < size; ++i) {
        if (cars[i].id == id) {
            if (!cars[i].isAvailable) {
                cout << "Sorry! This car is already rented.\n";
                return;
            }
            cout << "Enter number of days: ";
            cin >> days;
            double total = days * cars[i].rentPerDay;
            cars[i].isAvailable = false;
            cout << "Car rented successfully! Total bill: Rs." << total << "\n";
            return;
        }
    }
    cout << "Invalid Car ID!\n";
}

void returnCar(Car cars[], int size) {
    int id;
    cout << "Enter Car ID to return: ";
    cin >> id;
    for (int i = 0; i < size; ++i) {
        if (cars[i].id == id) {
            cars[i].isAvailable = true;
            cout << "Car returned successfully!\n";
            return;
        }
    }
    cout << "Invalid Car ID!\n";
}

// -------- Main Function ---------
int main() {
    Sign_In user;
    int authChoice;

    cout << "====== Welcome to Car Rental System ======\n";
    cout << "1. Sign Up\n";
    cout << "2. Log In\n";
    cout << "Enter your choice: ";
    cin >> authChoice;

    if (authChoice == 1) {
        user.signUp();
    } else if (authChoice == 2) {
        user.login();
    } else {
        cout << "Invalid choice. Exiting.\n";
        return 0;
    }

    if (!user.isSignedUp) {
        cout << "Authentication required to use the system.\n";
        return 0;
    }

   Car cars[5] = {
        {101, "Swift", "Maruti", 1500, true},
        {102, "City", "Honda", 2500, true},
        {103, "Creta", "Hyundai", 3000, true},
        {104, "Fortuner", "Toyota", 5000, true},
        {105, "XUV700", "Mahindra", 4000, true}
    };

    int choice;
    do {
        cout << "\n====== Car Rental Menu ======\n";
        cout << "1. List Available Cars\n";
        cout << "2. Rent a Car\n";
        cout << "3. Return a Car\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            listCars(cars, 5);
            break;
        case 2:
            rentCar(cars, 5);
                 break;
        case 3:
            returnCar(cars, 5);
            break;
        case 4:
            cout << "Thank you for using the Car Rental System.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}