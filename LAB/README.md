# Embedded Systems Lab – Reordered Experiments 01–17
This folder set is reorganized to match the supplied 17-item college experiment list. Original repository files and screenshots are copied without altering their contents. Status notes describe what the source files actually implement.
01. **Arduino Uno-Based Smart Home Safety and Occupancy Monitoring** — MATCHED. Gas, PIR and ultrasonic sensor program and its original screenshots.
02. **Formal Design of an Embedded Controller Using State Machine (Statechart) – Traffic Light Controller** — PARTIAL. Repository contains a six-LED sequence program and traffic-light-like circuit screenshots; the code does not implement a formal state machine.
03. **I2C-Based Health Monitoring Node for Pulse and Temperature Acquisition** — PARTIAL. Repository contains LM75 I2C temperature acquisition and screenshots; no pulse-sensor acquisition code was found.
04. **CAN Error Detection and Error Counter Monitoring** — MISSING. No matching CAN error-detection source or output was found in the repository.
05. **CAN Bus Signal Measurement and Termination Verification** — MISSING. No matching CAN signal measurement/termination source or output was found in the repository.
06. **Industrial HVAC Control Firmware – ADC Temperature Acquisition and Timer-Interrupt PWM Fan Control** — PARTIAL. Existing code reads analog temperature and controls PWM fan speed, but uses delay-based polling rather than timer-interrupt control.
07. **GPIO Configuration, Switch Input and LED Output with Bit-Level Manipulation Using LPC2148 Kit** — MATCHED. LPC2148 GPIO switch input and LED output source.
08. **Structured Embedded C – Modular Header/Source Driver for Seven-Segment Display Using LPC2148 Kit** — MISSING. No matching seven-segment driver source or output was found.
09. **Interrupt-Driven Serial Transmission and Reception Using On-Chip UART of LPC2148 Kit** — PARTIAL. Both folders contain the same UART0 polling/echo program; no interrupt-driven UART implementation was found.
10. **Modeling Clock-Driven Concurrent Processes Using SC_THREAD and wait() in SystemC** — MATCHED. SystemC clock-driven SC_THREAD processes.
11. **Transaction Level Modeling (TLM) and SystemC-Based Production Line Simulator** — PARTIAL. Production-line simulator using SystemC FIFO channels is present; explicit TLM sockets/interfaces were not found in the source.
12. **Python Scripting for Embedded Test Automation (PySerial) and Scripted Firmware Flashing Using esptool** — PARTIAL. PySerial test script and Arduino test firmware are present; flashing command uses arduino-cli, not esptool.
13. **RTOS Task Creation, Task States and Priority Assignment Using FreeRTOS** — MATCHED. FreeRTOS task creation with three priorities.
14. **Task Synchronization and Shared Data Protection Using Binary Semaphore, Counting Semaphore and Mutex using FreeRTOS** — MATCHED. Binary semaphore, counting semaphore and mutex examples.
15. **Inter-Task Communication Using Message Queues, Mailboxes and Pipes (Stream Buffers) – Producer–Consumer using FreeRTOS** — MATCHED. Queue, mailbox and stream-buffer producer/consumer tasks.
16. **RTOS Timer Functions and Event Groups using FreeRTOS** — MATCHED. Software timer and event-group synchronization.
17. **Interrupt Service Routines in an RTOS Environment – Deferred Processing and Interrupt Priority Handling using FreeRTOS** — MATCHED. GPIO ISR defers work to a FreeRTOS task through a queue.
