# Firmware Auto-Flasher ESP-Family

A **Python-based automated firmware flashing tool** for **ESP-family microcontrollers**.
This utility continuously monitors available UART ports and **automatically flashes a firmware binary** as soon as a supported ESP device is connected.

The tool supports **parallel flashing**, making it suitable for **production lines, batch testing, and rapid firmware deployment**.

---

##  Key Features

* Automatic detection of newly connected ESP devices
* Parallel flashing of multiple boards simultaneously
* No manual COM port selection
* High-speed flashing using `esptool`
* Real-time console status and progress logs
* Easily extensible for new ESP devices

---

##  Supported Devices (Current)

The following ESP devices are officially supported in this project:

1. **ESP32-S3-Mini-1 DevKit**
2. **ESP32-WROOM-32D-N4**
3. **ESP32-WROOM-32D-N8**

> More ESP-family devices can be added by updating the configuration inside the script.

---

##  Project Structure

```
.
├── auto_flasher_ESP-Device.py   # Main Python auto-flashing script
├── firmware_ESP-Device.bin     # Firmware binary to be flashed
├── ESP_Device.ino              # Reference Arduino source code
└── README.md                   # Project documentation
```

---

##  System Requirements

### Software

* **Python 3.8 or newer**
* **esptool**
* **pyserial**

Install dependencies using:

```bash
pip install esptool pyserial
```

---

##  Configuration Parameters

The following parameters are defined inside the Python script and can be modified if required:

| Parameter    | Description               | Default Value  |
| ------------ | ------------------------- | -------------- |
| `FIRMWARE`   | Firmware binary file name | `firmware.bin` |
| `FLASH_ADDR` | Flash start address       | `0x0000`       |
| `CHIP`       | Target ESP device family  | `ESP-Device`   |
| `BAUD_RATE`  | UART flashing speed       | `1500000`      |

---

##  Operational Workflow

1. Script continuously scans available UART ports
2. Detects newly connected ESP devices
3. Automatically starts flashing in a separate thread
4. Supports multiple devices flashing in parallel
5. Displays flashing status and results in real time

---

## ▶️ Usage Instructions

1. Place the compiled firmware binary in the project directory:

   ```
   firmware.bin
   ```

2. Run the auto-flasher script:

   ```bash
   python auto_flasher_ESP-Device.py
   ```

3. Connect one or more ESP devices via USB

4. Flashing starts automatically upon detection

---

## 📟 Example Console Output

```
[14:32:10] === PARALLEL ESP-DEVICE FLASHER STARTED ===
[14:32:15] Detected COM42 → Starting parallel flash
[14:32:15] START Flashing on COM42...
[14:32:21] SUCCESS on COM42
```

---

## ⚠️ Important Notes

* Some ESP32-S3 boards may require **BOOT mode** for flashing
* Ensure `firmware.bin` is present before running the script
* Avoid disconnecting devices during flashing
* Use powered USB hubs for large-scale parallel flashing

---

## Intended Use Cases

* Production firmware flashing
* R&D lab automation
* Manufacturing end-of-line testing
* Educational and institutional labs

```

---
