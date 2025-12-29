import os
import time
import subprocess
import serial.tools.list_ports
import threading

FIRMWARE = "firmware_ESP32-S3-Mini-1 DevKit.bin"
FLASH_ADDR = "0x0000"

def log(msg):
    timestamp = time.strftime("[%H:%Ms:%S] ")
    print(timestamp + msg)

def flash_device(port):
    log(f"START Flashing on {port}...")

    cmd = [
        "python", "-m", "esptool",
        "--chip", "esp32s3",
        "--port", port,
        "--baud", "1500000",
        "write_flash",
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
    log("=== PARALLEL ESP32-S3 FLASHER STARTED ===")

    previous_ports = set(p.device for p in serial.tools.list_ports.comports())

    while True:
        time.sleep(0.2)  # fast detection

        current_ports = set(p.device for p in serial.tools.list_ports.comports())
        new_ports = current_ports - previous_ports

        for port in new_ports:
            log(f"Detected {port} → Starting parallel flash")
            flash_in_parallel(port)

        previous_ports = current_ports

if __name__ == "__main__":
    main()
