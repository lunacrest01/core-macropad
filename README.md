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
<img width="326" height="309" alt="Screenshot 2026-03-08 160731" src="https://github.com/user-attachments/assets/bbd8ea77-3ad3-4df8-a067-f58c97a02a4d" />


⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻



PCB

The PCB manages the switch and encoder matrix, controls the RGB features, and handles battery charging.



<img width="460" height="506" alt="Screenshot 2026-03-07 070919" src="https://github.com/user-attachments/assets/be97630f-1f5b-4d9a-94c9-d7b0871d4ceb" />
<img width="755" height="779" alt="wireless pcb" src="https://github.com/user-attachments/assets/58c3e1c0-25c1-428b-9a10-9f4379f4854b" />
<img width="559" height="540" alt="Screenshot 2026-03-08 202248" src="https://github.com/user-attachments/assets/924277f1-cdbb-4452-9277-122910433658" />

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

*HANDWIRING*

The columns of the switches need to be hand-wired, while the encoder and the switch rows will be connected individually on the PCB.



<img width="182" height="182" alt="Screenshot 2026-03-08 155058" src="https://github.com/user-attachments/assets/19f2bef1-767e-48ed-8256-0e27bc869336" />

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
	
⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

*HOW TO USE*

Enter Flash Mode: Connect your ESP32-S3 to your computer. Press and hold the BOOT button, then press and release the RESET button. Finally, release the BOOT button. The device is now ready to receive new firmware.

Select Board in Arduino IDE: Open the Arduino IDE. Go to Tools > Board > Board Manager, search for and install the ESP32 platform if you haven't already. Then, navigate to Tools > Board > ESP32 Arduino and select the "ESP32S3 Dev Module" .

Customize Your Layout: To modify the key functions, open the keymap.cpp file in the Arduino IDE. Edit the keymap array to assign the desired keystrokes or actions to each key and encoder. Upload the sketch to your device.

