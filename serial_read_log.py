import serial
from datetime import datetime

# Replace with your serial port and baud rate
SERIAL_PORT = 'COM3'  # Example for Windows. Use '/dev/ttyUSB0' or '/dev/ttyACM0' on Linux.
BAUD_RATE = 9600
LOG_FILE = 'serial_log.txt'

def read_serial_data():
    # Open the serial connection
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        print(f'Connected to {SERIAL_PORT} at {BAUD_RATE} baud.')
        # Open the log file
        with open(LOG_FILE, 'a') as log:
            while True:
                try:
                    # Read data from the serial port
                    if ser.in_waiting > 0:
                        data = ser.readline().decode('utf-8').strip()
                        # Get current timestamp with microseconds
                        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
                        print(f'{timestamp} - {data}')  # Display the data with timestamp including microseconds
                        
                        # Log data to file with a timestamp including microseconds
                        log_entry = f'{timestamp} - {data}\n'
                        log.write(log_entry)
                        log.flush()  # Ensure data is written to file immediately

                except KeyboardInterrupt:
                    print("Logging stopped.")
                    break
                except Exception as e:
                    print(f"Error: {e}")
                    break

if __name__ == "__main__":
    read_serial_data()