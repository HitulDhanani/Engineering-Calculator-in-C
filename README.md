# ⚙️ Engineering Calculator in C

<div align="center">

![C](https://img.shields.io/badge/Language-C99%20%7C%20C11-00599C?style=for-the-badge&logo=c&logoColor=white)
![Domain](https://img.shields.io/badge/Field-Instrumentation%20%26%20Control%20Engineering-FF6F00?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed%20%26%20Verified-2EA44F?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![First Repo](https://img.shields.io/badge/Milestone-My%201st%20Coding%20Repository-blueviolet?style=for-the-badge)

<p align="center">
  <b>A modular, robust, menu-driven CLI engineering calculator built entirely in C.</b><br>
  <i>Bridging computer programming fundamentals with real-world Instrumentation, Electronics, and Process Control engineering.</i>
</p>

[Explore Features](#-features) • [Architecture](#-project-architecture) • [How to Run](#-how-to-compile-and-run) • [What I Learned](#-knowledge--skills-gained) • [Future Roadmap](#-future-roadmap)

---

</div>

## 🌟 About This Project (My 1st Coding Repository!)

Welcome to my very first GitHub repository! 🚀

As a **1st-year Instrumentation & Control Engineering (ICE) student**, I wanted my first coding project to be more than just a typical beginner calculator. I wanted to build something that:
1. **Solves real engineering problems** encountered in instrumentation, electronics, and process control labs.
2. **Deepens my core C programming knowledge** beyond basic syntax into modular architecture, memory safety, and pointer arithmetic.
3. **Serves as an authentic portfolio foundation** showcasing clean coding habits, professional documentation, and build automation.

This calculator handles everything from standard arithmetic to industrial **4–20 mA transmitter current loop scaling**, **Ohm's Law**, **AC motor synchronous speed**, **process pressure conversion**, and **sensor statistical analysis**.

---

## ✨ Features

The application is structured into specialized engineering modules:

### 1. 🔢 Basic Arithmetic & Safe Mathematics
- Standard operations: Addition ($+$), Subtraction ($-$), Multiplication ($\times$), Division ($/$), Power ($a^b$), Square Root ($\sqrt{a}$), and Modulo ($a \pmod b$).
- **Zero-Division & Domain Safety**: Explicitly prevents undefined division by zero and rejects negative square roots for real numbers.

### 2. 🌡️ Industrial Temperature Conversion
- Bidirectional conversions across **Celsius ($^\circ\text{C}$)**, **Fahrenheit ($^\circ\text{F}$)**, and **Kelvin ($\text{K}$)**.
- Formulated using exact thermodynamic scale equations.

### 3. ⚡ Ohm's Law Calculator
- Solves for any missing parameter given the other two:
  - Voltage: $V = I \times R$
  - Current: $I = \frac{V}{R}$ (includes automatic short-circuit warnings)
  - Resistance: $R = \frac{V}{I}$ (includes open-circuit zero-current detection)
- Provides automatic unit scaling into $\text{mA}$ and $\text{k}\Omega$.

### 4. 🔌 Electrical Power Calculator
- Calculates dissipated power using three distinct fundamental circuit formulations:
  $$P = V \times I \quad\big|\quad P = I^2 \times R \quad\big|\quad P = \frac{V^2}{R}$$
- Outputs power in Watts ($\text{W}$), Kilowatts ($\text{kW}$), and Milliwatts ($\text{mW}$).

### 5. 📐 Instrumentation Unit Conversion
- **Process Pressure Units**: Pascal ($\text{Pa}$), Kilopascal ($\text{kPa}$), $\text{Bar}$, $\text{PSI}$ ($\text{lbf/in}^2$), and Millimeters of Mercury ($\text{mmHg}$ / Torr).
- **Dimensional Units**: Meters ($\text{m}$), Millimeters ($\text{mm}$), Centimeters ($\text{cm}$), Inches ($\text{in}$), and Feet ($\text{ft}$).

### 6. ⚙️ RPM & Motor Speed Calculations
- **Optical / Digital Tachometer**:
  $$\text{RPM} = \frac{\text{Pulses per Second} \times 60}{\text{Pulses per Revolution (PPR)}}$$
- **AC Synchronous Motor Speed**:
  $$N_s = \frac{120 \times f}{P} \quad (f = \text{Line Frequency in Hz},\, P = \text{Stator Poles})$$
- **Linear Conveyor to Rotational Shaft Velocity**:
  $$N = \frac{v \times 60}{\pi \times D} \quad (v = \text{Velocity m/s},\, D = \text{Diameter in m})$$

### 7. 📊 Sensor Data Analytics & Transducer Statistics
- Reads an array of $N$ sensor samples (such as thermocouple mV readings or strain gauge outputs).
- Dynamically computes:
  - **Minimum & Maximum**
  - **Span (Dynamic Range)**: $\text{Span} = \text{Max} - \text{Min}$
  - **Sample Mean ($\mu$)**: $\mu = \frac{1}{N}\sum_{i=1}^N x_i$
  - **Sample Standard Deviation ($\sigma$)**:
    $$\sigma = \sqrt{\frac{1}{N - 1}\sum_{i=1}^N (x_i - \mu)^2}$$

### 8. 🎛️ 4–20 mA Industrial Current Loop Scaler *(ICE Special)*
The 4–20 mA analog signal is the global standard for industrial transmitters (pressure, level, flow, temperature).
- **Current to Process Variable ($PV$)**:
  $$PV = \text{LRV} + \left(\frac{I_{\text{mA}} - 4}{16}\right) \times (\text{URV} - \text{LRV})$$
- **Process Variable ($PV$) to Current**:
  $$I_{\text{mA}} = 4 + \left(\frac{PV - \text{LRV}}{\text{URV} - \text{LRV}}\right) \times 16$$
- Includes out-of-bounds warnings conforming to the **NAMUR NE43** standard.

---

## 🗂️ Project Architecture

```text
Engineering-Calculator-in-C/
├── .gitignore                  # Excludes binaries, object files, and IDE caches
├── LICENSE                     # Open-source MIT License
├── Makefile                    # GCC / Clang makefile for Linux, macOS & MSYS2
├── build.bat                   # 1-click compile & launch script for Windows
├── README.md                   # Complete repository documentation
├── calculator_single_file.c    # Standalone single-file version (for OnlineGDB / college labs)
│
├── include/                    # Header files (function prototypes & structs)
│   ├── calculator.h            # Arithmetic declarations
│   ├── electrical.h            # Ohm's Law & Power declarations
│   ├── ice_sensors.h           # RPM, 4-20mA scaler, and SensorStats struct
│   ├── units.h                 # Pressure, temperature, and length headers
│   └── utils.h                 # Safe input readers & UI utilities
│
└── src/                        # Modular C source files
    ├── main.c                  # Master interactive menu and program lifecycle
    ├── arithmetic.c            # Arithmetic functions with safety checks
    ├── electrical.c            # Electrical circuit calculations
    ├── ice_sensors.c           # Sensor stats, RPM tachometer & 4-20mA logic
    ├── units.c                 # Process pressure, temperature, and length math
    └── utils.c                 # Buffer flushing & robust input sanitation
```

---

## 🧠 Knowledge & Skills Gained

Building this repository was a huge leap in my development journey. Here are the core concepts I learned and practiced:

### 1. Modular C Programming & Header Files
- Learned why monolithic single-file code becomes unmaintainable.
- Structured code into logical `.h` interfaces and `.c` translation units.
- Used **header guards** (`#ifndef`, `#define`, `#endif`) to prevent duplicate symbol errors.

### 2. Pointers & Pass-by-Reference
- Implemented error-handling patterns where functions return a `bool` status and write calculated output via pointer:
  ```c
  bool divide(double a, double b, double *result);
  bool ohms_law_current(double voltage, double resistance, double *current);
  ```
- Understood the difference between passing values by copy vs. passing memory addresses.

### 3. Bulletproof Input Sanitation
- Discovered that using `scanf("%d", ...)` directly can crash or cause **infinite loops** when a user accidentally types letters.
- Implemented robust `fgets()` buffers paired with `strtod()` and `strtol()` to validate input and flush `stdin`.

### 4. Dynamic Memory Allocation
- Allocated and freed heap memory safely using `malloc()` and `free()` when accepting user-defined sensor sample sizes ($N$).

### 5. Instrumentation & Process Control Realities
- Connected classroom theory to software logic:
  - How industrial transmitters represent 0% to 100% process variables using 4–20 mA current loops.
  - Why standard deviation ($\sigma$) and span matter when evaluating sensor noise and calibration drift.
  - How tachometers convert optical encoder pulses into rotational RPM.

### 6. Build Systems & Git Workflow
- Created a platform-independent `Makefile` and an automated Windows `build.bat` script.
- Configured `.gitignore` to keep git commits clean of compiled `.exe` and `.o` binaries.

---

## 💻 How to Compile and Run

### Option 1: Windows (1-Click)
Double-click [`build.bat`](build.bat) or run from Command Prompt / PowerShell:
```cmd
.\build.bat
```
*The script automatically detects GCC or Clang, compiles all modules into `bin\calculator.exe`, and launches the program.*

### Option 2: Command Line (GCC or Clang)
```bash
# Create binary output directory
mkdir bin

# Compile all modules with C99 flags and math library
gcc -Wall -Wextra -std=c99 -Iinclude src/*.c -o bin/calculator.exe -lm

# Run the calculator
.\bin\calculator.exe
```

### Option 3: Linux / macOS / MSYS2 (`make`)
```bash
make
make run
```

### Option 4: Standalone Single-File (OnlineGDB / College Labs)
For quick lab experiments or online compilers where multi-file projects are inconvenient:
1. Open [`calculator_single_file.c`](calculator_single_file.c).
2. Copy and paste the entire source into [OnlineGDB](https://www.onlinegdb.com/) or Code::Blocks.
3. Click **Run** — zero configuration required!

---

## 🖥️ Sample Run Preview

```text
================================================================
     ENGINEERING CALCULATOR IN C - INSTRUMENTATION EDITION     
       [ Designed for Instrumentation & Control Engineers ]     
================================================================
 1. 🔢 Basic Arithmetic & Math Operations
 2. 🌡️  Temperature Conversion (Celsius, Fahrenheit, Kelvin)
 3. ⚡ Ohm's Law Calculator (V = I * R)
 4. 🔌 Electrical Power Calculator (P = V*I, I^2*R, V^2/R)
 5. 📐 Unit Conversion (Pressure: Bar, PSI, Pa, mmHg & Length)
 6. ⚙️  RPM & Motor Speed Calculation (Tachometer, AC Motor)
 7. 📊 Sensor Readings Analytics (Mean, Min, Max, Std Dev)
 8. 🎛️  4-20 mA Process Signal Scaler (Current Loop to PV)
 0. 🚪 Exit
----------------------------------------------------------------
 Enter your choice [0-8]: 8

==========================================================
  4-20 mA INDUSTRIAL PROCESS SIGNAL SCALER
==========================================================
 1. Convert 4-20 mA Loop Current -> Process Variable (PV)
 2. Convert Process Variable (PV) -> 4-20 mA Loop Current
 0. Back to Main Menu
----------------------------------------------------------
 Select option (0-2): 1

 Transmitter Calibration Range:
 - Enter Lower Range Value (LRV / 0%): 0
 - Enter Upper Range Value (URV / 100%): 150
 Enter signal current (4.0 to 20.0 mA): 12

 [✓] Scaled Process Variable (PV): 75.0000
     Process Percentage:          50.00 %

Press [ENTER] to return to the menu...
```

---

## 🔮 Future Roadmap

As I advance further in my Instrumentation & Control curriculum, I plan to expand this repository with:
- [ ] **PID Controller Simulation**: Discrete time proportional-integral-derivative loop simulation.
- [ ] **Thermocouple Lookup Engine**: Polynomial cold-junction compensation tables for Type-K and Type-J thermocouples.
- [ ] **CSV Data Logger**: Exporting sensor statistics and calibration runs directly to `.csv` files.
- [ ] **Filter Implementations**: Simple Moving Average (SMA) and Exponential Moving Average (EMA) digital filters for noisy sensor readings.

---

## 🤝 Contributing & Feedback

Since this is my first coding repository, suggestions, code reviews, and feedback from senior developers and fellow engineering students are warmly welcomed!

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/NewFeature`)
3. **Commit** your changes (`git commit -m 'Add some NewFeature'`)
4. **Push** to the branch (`git push origin feature/NewFeature`)
5. **Open** a Pull Request

---

## 📜 License

This project is licensed under the [MIT License](LICENSE) — feel free to use, modify, and learn from this codebase for your own projects and academic studies!

---

<div align="center">

⭐ **If you found this project helpful or inspiring for your own coding journey, please consider giving it a star!** ⭐

*Built with passion by a 1st-year Instrumentation & Control Engineering student.*

</div>
