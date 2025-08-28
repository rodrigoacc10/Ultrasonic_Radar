import tkinter as tk
from tkinter import ttk, messagebox
import serial
import threading
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.animation import FuncAnimation
import numpy as np

# Global variables
degrees = []
distances = []
run_plot = False  # Controls the serial communication loop

# Fixed serial port and baudrate
SERIAL_PORT = "COM4"
BAUDRATE = 115200

# Function to read data from serial port
def read_serial():
    global degrees, distances, run_plot
    try:
        ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
        while run_plot:
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8').strip()
                try:
                    # Parse the data in "Degree:xxx,Distance:xxx" format
                    if "Degree:" in data and "Distance:" in data:
                        parts = data.split(',')
                        degree = float(parts[0].split(':')[1])
                        distance = float(parts[1].split(':')[1])
                        degrees.append(degree)
                        distances.append(distance)

                        # Limit the size of the data lists for memory efficiency
                        if len(degrees) > 180:
                            degrees.pop(0)
                            distances.pop(0)
                except (ValueError, IndexError):
                    # Skip invalid data
                    pass
        ser.close()
    except serial.SerialException as e:
        messagebox.showerror("Serial Error", f"Failed to connect to {SERIAL_PORT}:\n{e}")

# Function for starting the reading process
def start_reading():
    global run_plot
    run_plot = True
    thread = threading.Thread(target=read_serial)
    thread.daemon = True
    thread.start()

# Function to stop the reading process
def stop_reading():
    global run_plot
    run_plot = False

# Function to update the plot in real-time
def update_plot(frame):
    plt.cla()  # Clear axis for updated plot
    plt.xlim(0, 180)
    plt.ylim(0, 200)
    plt.xlabel("Degrees")
    plt.ylabel("Distance")
    plt.title("Ultrasonic Radar Points Plot")
    plt.grid()
    if degrees and distances:
        plt.scatter(degrees, distances, c='b', label="Distance vs Degree")
        plt.legend()

# Function to start graphical interface
def create_gui():
    root = tk.Tk()
    root.title("Ultrasonic Radar Scatter Plot by Rodrigo Casados")

    # Remove serial port and baudrate input fields

    # Buttons
    button_frame = ttk.Frame(root, padding="10")
    button_frame.grid(row=0, column=0, sticky="EW")

    start_button = ttk.Button(button_frame, text="Start", command=start_reading)
    start_button.grid(row=0, column=0, padx=5, pady=5)

    stop_button = ttk.Button(button_frame, text="Stop", command=stop_reading)
    stop_button.grid(row=0, column=1, padx=5, pady=5)

    # Matplotlib plot
    plot_frame = ttk.Frame(root, padding="10")
    plot_frame.grid(row=1, column=0, sticky="EW")

    global fig
    fig = plt.figure(figsize=(6, 4))
    canvas = FigureCanvasTkAgg(fig, master=plot_frame)
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    ani = FuncAnimation(fig, update_plot, interval=500)
    
    root.mainloop()

# Entry point
if __name__ == "__main__":
    create_gui()