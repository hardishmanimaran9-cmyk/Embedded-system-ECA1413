import serial
import time
import subprocess

# Serial testing
ser = serial.Serial('COM3', 9600, timeout=2)
time.sleep(2)

ser.write(b'TEST\n')
response = ser.readline().decode().strip()

if response == "PASS":
    print("Test Passed")
else:
    print("Test Failed")

ser.close()

# Firmware flashing
subprocess.run([
    "arduino-cli", "upload",
    "-p", "COM3",
    "--fqbn", "esp32:esp32:esp32",
    "TestCode"
])

print("Firmware Flashing Completed")
