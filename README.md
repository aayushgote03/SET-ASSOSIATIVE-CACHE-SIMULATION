
# Set-Associative Cache Simulation

This C++ program simulates a **Set-Associative Cache**, demonstrating operations like **read** and **write-through**. It uses random and normal distribution-based address generation and implements a **random replacement policy**. The simulation tracks cache performance metrics such as **hit/miss counts** and calculates the **hit ratio** over a user-defined duration.

---

## 🛠 Features
- **Custom Cache Design**:  
  - 64 sets with 8 lines per set.
  - Each line includes:
    - **2-bit state** (valid/invalid).
    - **28-bit tag**.
- **Random Replacement Policy**:  
  - Handles cache misses by randomly selecting a victim line for replacement when the set is full.
- **Random Address Generation**:  
  - Simulates 40-bit memory addresses using uniform and normal distribution methods.
- **Hit/Miss Tracking**:  
  - Accurately tracks the number of cache hits and misses.
  - Calculates the **hit ratio** for performance analysis.

---

## 📂 File Structure
```
📦 SetAssociativeCache
┣ 📜 main.cpp       # Source code for the cache simulation
┣ 📜 README.md      # Project documentation (this file)
```

---

## 🧮 How It Works
1. **Cache Initialization**:  
   - 64 sets, each with 8 lines. Initially, all lines are invalid (state `00`).
2. **Address Breakdown**:  
   - A 40-bit address is divided into:
     - **28-bit tag**.
     - **6-bit set number**.
     - **6-bit block offset** (ignored in simulation).
3. **Cache Operations**:  
   - **Read**: Checks if the requested data is in the cache (hit) or not (miss).
   - **Write-Through**: Always updates the main memory on a write.
4. **Replacement Policy**:  
   - If no invalid line is found during a miss, a random line in the set is replaced.

---

## 🔧 Usage
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/SetAssociativeCache.git
   ```
2. Compile the program:
   ```bash
   g++ main.cpp -o cache_simulation
   ```
3. Run the simulation:
   ```bash
   ./cache_simulation
   ```
4. Enter the duration (in seconds) for which you want the cache to simulate operations.

---

## 📊 Example Output
```
Enter the duration for the loop to run (in seconds): 10
cache implementation begin: **************************************
total no of access: 152432
no of hits: 120543
no of misses: 31889
hit ratio: 79.06%
```

---

## 🚀 Future Enhancements
- Implement additional replacement policies (e.g., LRU, FIFO).
- Add support for configurable cache sizes and associativity.
- Provide detailed cache performance logs.

---

## 📝 License
This project is licensed under the MIT License. Feel free to use and modify it!

---

## 🤝 Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue for any improvements or suggestions.
