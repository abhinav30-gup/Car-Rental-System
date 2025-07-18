# 🚗 Car Rental System in C++  

![Language](https://img.shields.io/badge/C%2B%2B-Project-blue.svg)  
![Status](https://img.shields.io/badge/Status-Working-green)  
![License](https://img.shields.io/badge/License-MIT-green.svg)

---

## 📌 Project Description

This **Car Rental System** is a beginner-friendly console application built in **C++** that allows users to:

- ✅ Sign Up and Log In securely  
- 🚘 View a list of available cars  
- 🔑 Rent and Return cars  
- 🗂 Store and retrieve user and car data using text files  

The system mimics a real-world car rental process using basic Object-Oriented Programming principles, file handling, and structured menus.

---

## 💡 Features

🔐 **User Authentication**  
- Sign Up with details like Name, Password, Email, Phone, Aadhar  
- Login to access the system securely

🚗 **Car Management**  
- View all cars with details (Brand, Model, Price, Availability)  
- Rent cars based on ID and duration  
- Return rented cars  

💾 **Data Persistence**  
- User data saved in `usersData.txt`  
- Car data managed in memory and optionally can be saved in `carsData.txt`  

---

## 🧠 Technologies Used

| Tool / Language | Purpose |
|------------------|---------|
| 🟦 C++ | Core programming |
| 📁 File I/O | Store and manage user and car data |
| 🧱 Object-Oriented Programming | Class-based design (Sign_In, Car) |
| 🧾 Text Files | Persistent data storage |

---

## 🧪 How It Works

1. **Clone this repository**
   ```bash
   git clone https://github.com/yourusername/car-rental-cpp.git
   ```

2. **Compile the code**
   ```bash
   g++ main.cpp -o car_rental
   ```

3. **Run the program**
   ```bash
   ./car_rental
   ```

---

## 🧾 Sample Credentials

To test login after signup, use:
- **Username**: your full name  
- **Password**: the one you entered during signup  

Data is stored in `usersData.txt` in CSV format:
```
Name,Password,Email,Phone,Aadhar
```

---

## 🛠 Future Improvements

- Add Admin panel to manage car inventory  
- Link car data with persistent storage (`carsData.txt`)  
- Encrypt passwords for better security  
- Create GUI using C++ frameworks like Qt or external web-based interface  

---

## 🙌 Credits

This project is created as part of a **learning journey** in C++ and system design.

---

## 📄 License

This project is licensed under the **MIT License**

---

# Author
Developed by Abhinav Kumar Gupta

> **"Driven by code, powered by creativity!"**
