# 🧾 Point-of-Sale (POS) and Inventory System

## 📌 Project Overview
This project is a **Point-of-Sale (POS) and Inventory System** built as a **C++ console application** for a retail shop or mini-mart.  
It simulates the core functionalities of a real-world retail management system — including product cataloging, sales tracking, and data persistence — while reinforcing key **C++ programming concepts**, **file I/O**, and **data structures**.

---

## 🎯 Objectives
- Develop a console-based POS and inventory management system.
- Practice **C++ basics**, **functions**, **arrays**, **strings**, and **file I/O**.
- Demonstrate the use of **structs**, **vectors**, and **modular programming**.
- Implement **persistent data storage** using CSV files.
- Apply **OOP principles** and structured program design.

---

## ⚙️ Features
### 🛒 Product Management
- Add, edit, remove, and list products.
- Automatically load and save products from a CSV file (`products.csv`).
- Maintain product ID, name, price, and available stock.

### 💰 Sales & Cart System
- Add products to a shopping cart.
- Calculate subtotal, tax, and total.
- Automatically update product stock levels after each sale.

### 📦 Inventory Tracking
- View product stock levels.
- Simulate supplier restock alerts when stock runs low.

### 📊 Reports
- Generate basic daily reports, including:
  - Total number of products
  - Total stock quantity
  - Total inventory value

### 💾 File I/O Persistence
- Products are stored in `products.csv` for permanent data saving.
- Data automatically loads at startup and saves on exit.

---

## 🧩 System Design
**Core Components:**
- **Main Menu:** Console-based navigation for Products, Sales, Reports, and Exit.
- **Structs:**
  - `Product`: Defines ID, name, price, and stock.
  - `CartItem`: Handles sales calculations (subtotal, tax, total).
- **Data Structures:** Uses `std::vector` for dynamic product and cart management.
- **File Handling:** Uses `fstream` for reading/writing CSV files.

---

## 📁 File Structure
