# Multithreaded Telemetry Server

This project was developed for **educational purposes** to practice low-level systems programming, network communication, and concurrency in the C programming language. 

It features a multithreaded client-server architecture where a simulated rocket transmits telemetry data (altitude and speed) to a ground station (panel) via UDP sockets. A thread-safe ring buffer is utilized to ensure data integrity during asynchronous read/write operations.

## 🚀 Features

*   **UDP Communication:** Fast, connectionless data transmission between the client (rocket) and server (panel) via `127.0.0.1:8080`.
*   **Multithreading (POSIX Threads):** Asynchronous management of data enqueue and dequeue operations utilizing the `pthread` library.
*   **Thread-Safe Ring Buffer:** A circular queue design with a 5-element capacity, implementing `pthread_mutex_t` to prevent race conditions and ensure thread synchronization.
*   **Real-Time Simulation:** Live tracking of a free-falling rocket's altitude and velocity metrics, culminating in automated impact detection.

## 📂 File Structure

As configured in the development environment, the core components of the project are:

*   **`rocket.c`**: The client module that generates the simulated telemetry data and transmits it to the server over UDP.
*   **`panel.c`**: The server module (ground station) that listens on port 8080, processes the incoming data, and outputs it to the console.
*   **`ringbuffer.c`**: Contains the mutex-protected enqueue and dequeue functions shared between the client and server.
*   **`buffer.h`**: The header file defining the shared data structures (`Structs`) and function prototypes.
*   **`Makefile`**: The build automation script to streamline the compilation process.

## 🛠️ Build and Run Instructions

To compile and run this project, ensure you have the `gcc` compiler and the `make` utility installed (Linux or macOS environments are recommended).

**1. Compile the Project:**
Navigate to the project directory in your terminal and execute:
```bash
make
```
*This command will generate two executable binaries: `panel` and `rocket`.*

**2. Start the Server (Ground Station):**
Initialize the ground station to start listening for incoming UDP packets:
```bash
./panel
```

**3. Launch the Rocket Simulation:**
Open a new terminal window or tab, and execute the client:
```bash
./rocket
```

## 📝 Simulation Scenario

Upon execution, the `rocket` program initializes at an altitude of 1000 units. During each loop iteration, it decrements the altitude and increments the speed. This data is concurrently written to the Ring Buffer and transmitted over the network via UDP. Once the altitude reaches `0` while maintaining a positive speed value, the `panel` program accurately detects a crash (impact) event and automatically terminates the simulation loop.
