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

# Function to read data from serial port
def read_serial(port, baudrate):
    global degrees, distances, run_plot
    try:
        ser = serial.Serial(port, baudrate, timeout=1)
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
        messagebox.showerror("Serial Error", f"Failed to connect to {port}:\n{e}")

# Function for starting the reading process
def start_reading():
    global run_plot
    port = port_entry.get()
    try:
        baudrate = int(baud_rate_entry.get())
    except ValueError:
        messagebox.showerror("Invalid Input", "Invalid baud rate.")
        return

    run_plot = True
    thread = threading.Thread(target=read_serial, args=(port, baudrate))
    thread.daemon = True
    thread.start()

# Function to stop the reading process
def stop_reading():
    global run_plot
    run_plot = False

# Function to update the plot in real-time
def update_plot(frame):
    plt.cla()  # Clear axis for updated plot
    if degrees and distances:
        plt.plot(degrees, distances, '-o', label="Distance vs Degree")
        plt.xlabel("Degrees")
        plt.ylabel("Distance")
        plt.title("Real-time Data Plot")
        plt.legend()
        plt.grid()

# Function to start graphical interface
def create_gui():
    root = tk.Tk()
    root.title("Serial Data Plotter")

    # Serial Port configuration
    config_frame = ttk.Frame(root, padding="10")
    config_frame.grid(row=0, column=0, sticky="EW")

    ttk.Label(config_frame, text="COM Port:").grid(row=0, column=0, sticky="W")
    global port_entry
    port_entry = ttk.Entry(config_frame)
    port_entry.grid(row=0, column=1, pady=5, padx=5)

    ttk.Label(config_frame, text="Baud Rate:").grid(row=1, column=0, sticky="W")
    global baud_rate_entry
    baud_rate_entry = ttk.Entry(config_frame)
    baud_rate_entry.grid(row=1, column=1, pady=5, padx=5)

    # Buttons
    button_frame = ttk.Frame(root, padding="10")
    button_frame.grid(row=1, column=0, sticky="EW")

    start_button = ttk.Button(button_frame, text="Start", command=start_reading)
    start_button.grid(row=0, column=0, padx=5, pady=5)

    stop_button = ttk.Button(button_frame, text="Stop", command=stop_reading)
    stop_button.grid(row=0, column=1, padx=5, pady=5)

    # Matplotlib plot
    plot_frame = ttk.Frame(root, padding="10")
    plot_frame.grid(row=2, column=0, sticky="EW")

    global fig
    fig = plt.figure(figsize=(6, 4))
    canvas = FigureCanvasTkAgg(fig, master=plot_frame)
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    ani = FuncAnimation(fig, update_plot, interval=500)
    
    root.mainloop()

# Entry point
if __name__ == "__main__":
    create_gui()