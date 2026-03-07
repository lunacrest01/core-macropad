Core

Core-W is a wireless 3×3 macropad with one rotary encoder and RGB underglow support. It runs custom firmware and software on an ESP32-S3 module with BLE HID and BLE GATT support.


⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻



*FEATURES*

•	9 mechanical switches


•	1 rotary encoder


•	RGB underglow lighting


•   BLE HID/GATT


⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

*CAD*


<img width="471" height="346" alt="Screenshot 2026-03-07 071358" src="https://github.com/user-attachments/assets/1efa1d98-d4b1-44ae-88f0-c19ea5c11ca7" />


⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻



PCB



<img width="460" height="506" alt="Screenshot 2026-03-07 070919" src="https://github.com/user-attachments/assets/be97630f-1f5b-4d9a-94c9-d7b0871d4ceb" />
<img width="755" height="779" alt="wireless pcb" src="https://github.com/user-attachments/assets/58c3e1c0-25c1-428b-9a10-9f4379f4854b" />

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻



*OVERVIEW*

Core-W is a wireless 3×3 macropad featuring a rotary encoder and RGB underglow. Powered by the ESP32-S3 microcontroller, it is designed to support BLE HID and BLE GATT for wireless communication, running on custom-developed firmware and software

When transitioning the device to wireless functionality, two main firmware options were considered ZMK and RMK

ZMK requires reserving a key for the studio interface and currently lacks proper support for encoders and reactive RGB lighting

RMK presents similar limitations, particularly in encoder functionality and advanced RGB features

Due to these constraints, I decided to develop my own firmware and software to fully leverage the hardware capabilities of the Core-W

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻


Idea / Approach
    •	Send key inputs to the host using BLE HID
	•	Receive data for live key remapping
	•	Communication can be done using BLE GATT services or USB

*I am currently testing features related to BLE GATT and HID services, including live key remapping. This part of the project is still under development*
