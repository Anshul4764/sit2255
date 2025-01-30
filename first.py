import serial
import random
import time

baud_rate = 9600
port = 'COM11'  # Change this to your port

# Initialize serial communication
ser = serial.Serial(port, baud_rate, timeout=5)

while True:
    # Generate a random number of blinks
    blink_count = random.randint(1, 2)

    # Send blink count to Arduino
    ser.write(bytes(str(blink_count), 'utf-8'))
    print(f"Sent >>> {blink_count} blinks")

    # Wait for Arduino to respond
    time.sleep(0.5)
    response = ser.readline().decode('utf-8').strip()

    if response.isdigit():
        delay = int(response)
        print(f"Received <<< {delay} seconds delay")

        # Simulate delay on Python side
        time.sleep(delay)
        print(f"Sleeping for {delay} seconds")
        print("--------------------------------")
