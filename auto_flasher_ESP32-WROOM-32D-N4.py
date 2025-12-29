import os
import time
import subprocess
import serial.tools.list_ports
import threading

FIRMWARE = "firmware_ESP32-WROOM-32D-N4.bin"
FLASH_ADDR = "0x0000"

def log(msg):
    timestamp = time.strftime("[%H:%M:%S] ")
    print(timestamp + msg)

def flash_device(port):
    log(f"START Flashing on {port}...")

    cmd = [
        "python", "-m", "esptool",
        "--chip", "esp32",        # FIXED for WROOM-32D
        "--port", port,
        "--baud", "1500000",
        "write-flash",            # OR write-flash (new command)
        FLASH_ADDR,
        FIRMWARE
    ]

    result = subprocess.run(cmd, capture_output=True, text=True)

    if "Hash of data verified" in result.stdout:
        log(f"SUCCESS on {port}")
    else:
        log(f"FAIL on {port}:\n{result.stdout}")

def flash_in_parallel(port):
    thread = threading.Thread(target=flash_device, args=(port,))
    thread.start()

def main():
    log("=== PARALLEL ESP32-WROOM-32D FLASHER STARTED ===")

    previous_ports = set(p.device for p in serial.tools.list_ports.comports())

    while True:
        time.sleep(0.2)

        current_ports = set(p.device for p in serial.tools.list_ports.comports())
        new_ports = current_ports - previous_ports

        for port in new_ports:
            log(f"Detected {port} → Starting flash")
            flash_in_parallel(port)

        previous_ports = current_ports

if __name__ == "__main__":
    main()
