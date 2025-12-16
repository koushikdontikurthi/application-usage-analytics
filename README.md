# application-usage-analytics
Application usage analytics pipeline using Python and C++
# Application Usage Analytics Pipeline

## Overview
This project simulates application usage data and generates analytical reports.
A Python script continuously produces usage logs, and a C++ program processes
the data to generate insights.

## Technologies Used
- Python
- C++
- Linux
- Git & GitHub
- Designed to run on Azure VM

## Execution Flow
1. Python script generates application usage records (`data.csv`)
2. C++ program reads the generated data
3. Analytics reports are exported as CSV files

## How to Run
```bash
python data_generator.py
g++ main.cpp -o analytics
./analytics
