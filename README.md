# Lab 3: Buttons & Switches - Traffic Light Controller

**School:** Ho Chi Minh City University of Technology  
**Name:** Huynh Tri Duc  
**Student ID:** 2452269  
**Group:** CC03  

---

### Project Overview  
Source code and Proteus simulation for Lab 3, implementing a 2-way traffic light control system at an intersection using STM32F103C6. The application features non-blocking Finite State Machines (FSM), 10ms hardware timer interrupts (`TIM2`), software debouncing with hold-to-repeat auto-incrementing, 4-digit 7-segment LED multiplexing, and 2Hz LED blinking in configuration modes while maintaining strict timing balance ($t_{\text{Red}} = t_{\text{Green}} + t_{\text{Yellow}}$).

### Tools & Environment  
- **Microcontroller:** STM32F103C6  
- **Development Environment:** STM32CubeIDE  
- **Simulation:** Proteus 8 Professional  

### Lab Exercises  
- **Exercise 1:** FSM logic design for button states (Debounced Press, Hold 1s Auto-Increment) and Mode transitions (Mode 1–4).  
- **Exercise 2:** Proteus schematic design featuring 12 traffic LEDs, 4 7-segment displays, and 3 push buttons.  
- **Exercise 3:** STM32 project initialization and 10ms `TIM2` timer interrupt configuration.  
- **Exercise 4:** Centralized absolute millisecond timebase (`TIMER_CYCLE_MS`) ensuring timing invariant 2Hz LED blinking.  
- **Exercise 5:** Input debouncing driver (`input_reading.c`) and Mode selection FSM via Button 1 (`input_processing.c`).  
- **Exercise 6:** 7-segment LED multiplexing display driver (`display_7seg.c`) and mode-based 2Hz blinking state machine (`traffic_light.c`).  
- **Exercise 7:** Red LED duration modification logic via Button 2 (Increment/Auto-Increment) and Button 3 (Set value & recalculate Green duration).  
- **Exercise 8:** Amber (Yellow) LED duration modification logic with automatic Red duration recalculation ($t_{\text{Red}} = t_{\text{Green}} + t_{\text{Yellow}}$).  
- **Exercise 9:** Green LED duration modification logic with automatic Red duration recalculation ($t_{\text{Red}} = t_{\text{Green}} + t_{\text{Yellow}}$).  
- **Exercise 10:** Complete system integration, super-loop orchestration, verification, and video demonstration.

### Pin Mapping  

| Component | MCU Pin | Function |
| :--- | :--- | :--- |
| **LED_RED_HOR** | PA1 | Red Traffic LED (Horizontal Road) |
| **LED_YELLOW_HOR** | PA2 | Yellow Traffic LED (Horizontal Road) |
| **LED_GREEN_HOR** | PA3 | Green Traffic LED (Horizontal Road) |
| **LED_RED_VER** | PA4 | Red Traffic LED (Vertical Road) |
| **LED_YELLOW_VER** | PA5 | Yellow Traffic LED (Vertical Road) |
| **LED_GREEN_VER** | PA6 | Green Traffic LED (Vertical Road) |
| **SEG0 – SEG6** | PA7 – PA13 | 7-Segment LED Segments (A – G) |
| **BUTTON1** | PB0 | Button 1 (Select Mode: Mode 1 $\rightarrow$ 2 $\rightarrow$ 3 $\rightarrow$ 4 $\rightarrow$ 1) |
| **BUTTON2** | PB1 | Button 2 (Increment Edit Value / Hold >1s Auto-Increment) |
| **BUTTON3** | PB2 | Button 3 (Set/Confirm Value & Recalculate Timing) |
| **EN0 – EN3** | PB3 – PB6 | 7-Segment LED Digit Enables |

---

### How to Run the Simulation  
1. Clone this repository to your local machine.  
2. Open the corresponding Proteus project located in the `schematic/` directory.  
3. Double-click the `STM32F103C6` microcontroller and select the compiled `.hex` file from the `Debug/` folder.  
4. Click **Debug > Start VSM Debugging** to run the traffic light simulation.