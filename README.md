# 💳 ATM Simulation System in C

> **Team Name:** Classic Four  
> **Project Type:** ICS Major Project  
> **Team Members:**
> - 🧑‍💻 Harsh Chaudhari (B24CM1027) 
> - 🧑‍💻 Brijesh Thakkar (B24ME1018)  
> - 🧑‍💻 Suvarn Vijay Patil (B24CS1074)   
> - 🧑‍💻 Faiz Raise (B24BB1010)

---

## 📘 Project Overview

This project is a simulation of an **ATM (Automated Teller Machine)** system using C programming. It aims to help users experience and understand basic banking operations such as:

- Cash Withdrawal  
- Cash Deposit  
- Balance Inquiry  
- PIN Change  
- Transaction Logging  

It also simulates a realistic terminal experience using **typewriter-style text display** and securely manages data using **file handling** for persistent storage.

---

## 🎯 Objective

The main objective of this project is to replicate the working of a basic ATM system with:
- User-friendly interaction
- PIN authentication
- File-based storage for balance and PIN
- Logging of all transactions with timestamps

---

## ⚙️ Features

- 🔐 **User Authentication**  
  - 3 attempts for 4-digit PIN entry  
  - Default PIN = `0000`

- 💸 **Cash Withdrawal**   
  - Balance updated and logged after withdrawal

- 💰 **Cash Deposit**  
  - Deposit any valid amount to account  
  - Balance updated and logged

- 🧾 **Balance Check**  
  - Display current balance (read from file)  

- 🔄 **Change PIN**  
  - User can change their PIN after confirmation

- 📝 **Transaction Logging**  
  - All transactions (withdrawal, deposit, balance check, PIN change) are logged in `transaction_log.txt` with timestamp

- 🎞️ **Typewriter Text Effect**  
  - Enhances user experience through a character-by-character printing effect

---

## 📁 File Handling System

The program uses the following files:

| File Name              | Purpose                                   |
|------------------------|-------------------------------------------|
| `balance.txt`          | Stores the account balance                |
| `pin.txt`              | Stores the 4-digit user PIN               |
| `transaction_log.txt`  | Logs each transaction with details        |

If any of these files are missing, the system loads default values to ensure smooth functioning.

---

## 🧠 Core C Concepts Used

- Functions and Modular Design  
- File Handling  
- Strings and Character Arrays  
- Loops (`while`, `for`)  
- Conditional Statements (`if-else`, `switch`)  
- Error Handling & Input Validation

---

## 🔐 Security Measures

- PIN verification before accessing account  
- Max 3 attempts for PIN entry  
- All actions logged for accountability and security

---
