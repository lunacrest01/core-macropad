Core

Core is a 3×3 macropad with an encoder and RGB underglow, built using QMK firmware. It was designed as a productivity and desk accessory tool. The current version is wired, and the goal of this project is to convert it into a wireless device.

![adbc08ed-dc87-4d06-af57-05eb94f75345](https://github.com/user-attachments/assets/ce54abe9-e284-4a15-92bb-e9c3b203d6f2)


⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻



*FEATURES*

•	9 mechanical switches


•	1 rotary encoder


•	RGB underglow lighting

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

CAD
<img width="471" height="346" alt="Screenshot 2026-03-07 071358" src="https://github.com/user-attachments/assets/1efa1d98-d4b1-44ae-88f0-c19ea5c11ca7" />
⸻⸻⸻
PCB
<img width="460" height="506" alt="Screenshot 2026-03-07 070919" src="https://github.com/user-attachments/assets/be97630f-1f5b-4d9a-94c9-d7b0871d4ceb" />
<img width="755" height="779" alt="wireless pcb" src="https://github.com/user-attachments/assets/58c3e1c0-25c1-428b-9a10-9f4379f4854b" />

⸻⸻⸻
Overview

Core is a 9-key macropad developed using QMK firmware. The existing version works in wired mode.

When converting it to wireless, there are mainly two firmware options available: ZMK and RMK.
	•	ZMK – Requires reserving a key for the studio interface, and it currently does not support encoders or reactive RGB properly.
	•	RMK – Has similar limitations, especially regarding encoder support and advanced RGB features.

Because of these limitations, I decided to develop my own firmware and software to fully support the hardware features.

Currently, the testing is being done using the Arduino IDE, but the project will later shift to ESP-IDF for better performance and control.

⸻⸻⸻

Idea / Approach
	•	Send key inputs to the host using BLE HID.
	•	Receive data for live key remapping.
	•	Communication can be done using BLE GATT services or USB.

*For the wireless version, I am currently testing features related to BLE GATT and HID services, including live key remapping. This part of the project is still under development. The wired version, however, is ready to use.*
