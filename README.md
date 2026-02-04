# 🏠 House Price Prediction Project (BP Course)

## 📌 Overview
This repository contains the final project for the **Basics of Programming (BP)** course.
The project is implemented in **C language** using a **modular and structured programming approach**.

The main goal of this project is to analyze house-related data and predict house prices using **statistical analysis** and **basic machine learning algorithms** implemented **from scratch**, without using external libraries.

---

## 🎯 Objectives
The objectives of this project are:
- Learning modular programming in C
- Working with CSV files and file I/O
- Dynamic memory management
- Data preprocessing and cleaning
- Exploratory Data Analysis (EDA)
- Implementing Linear Regression and Gradient Descent
- Understanding error metrics
- Teamwork using Git & GitHub
- Writing clean, maintainable, and documented code

---

## 🧠 Features
- CSV data loading and parsing
- Handling missing values:
  - Mean Imputation
  - Median Imputation
  - Mode Imputation
- Statistical analysis (mean, min, max, etc.)
- Feature normalization (Min-Max Scaling)
- Linear Regression (analytical solution)
- Gradient Descent with adjustable learning rate
- Error evaluation:
  - MSE
  - MAE
  - MAPE
- Data visualization using **Gnuplot**
- Fully modular C project structure

---

## 📂 Project Structure
```plaintext  
bp-project/
│
├── data/
│ ├── raw/ # Original CSV files
│ └── processed/ # Preprocessed data
│
├── include/ # Header files (.h)
│ ├── config.h
│ ├── csv.h
│ ├── feature_engineering.h
│ ├── impute.h
│ ├── linear_regression.h
│ ├── metrics.h
│ ├── outlier.h
│ ├── plot.h
│ ├── scaling.h
│ ├── split.h
│ ├── stats.h
│ └── utils.h
│
├── src/ # Source files (.c)
│ ├── csv_numeric.c
│ ├── csv_ohe.c
│ ├── csv.c
│ ├── feature_engineering.c
│ ├── impute.c
│ ├── linear_regression.c
│ ├── main.c
│ ├── metrics.c
│ ├── outlier.c
│ ├── plot.c
│ ├── scaling.c
│ ├── split.c
│ ├── stats.c
│ └── utils.c
│
├── plots/ # Gnuplot scripts & outputs (.gp)
│
├── Makefile
└── README.md

```

---

## ⚙️ Build & Run Guide

### 🔧 Requirements
- GCC Compiler
- Make
- Gnuplot (optional, for plotting)

> ⚠️ On Windows, it is recommended to use **MinGW-w64** with `make` installed.

---

### 🛠 Compile the Project
From the project root directory, run:
```bash
make
```
or
```bash
mingw32-make
```
This command:
-Compiles all source files
-Links object files
-Produces the final executable

### ▶️ Run the Program
```bash
./project
```
(On Windows:)
```bash
project.exe
```

### 🧹 Clean Build Files
```bash
make clean
```
or
```bash
mingw32-make clean
```
This removes:
- Object files (.o)
- Executable files

---

## 🔄 Teamwork & Git Workflow
This project is developed collaboratively using GitHub.

### Workflow Rules:
- Each feature is implemented in a separate branch
- No direct commits to main
- Pull Requests are used for merging
- Small and meaningful commits are encouraged
Example:
```bash
git checkout -b csv-module
git commit -m "Implement CSV file loader"
git push origin csv-module
```

---

## 📊 Data Visualization
Gnuplot is used to visualize relationships between features such as:
- House size vs price
- Normalized vs raw data
Plots are generated using data files exported from the program.

---

## 📚 Course Information
- Course Name: Basics of Programming (BP)
- Programming Language: C
- Academic Level: Undergraduate
- Field: Computer Science / Software Engineering

---

## ✨ Authors
- MohammadAmin Babaie
- Project Team Members

---

## 🏁 Final Notes
This project focuses on learning core programming concepts, not using ready-made libraries. All algorithms and data processing techniques are implemented manually to ensure a deep understanding of the fundamentals.