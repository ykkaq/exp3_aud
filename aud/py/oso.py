import numpy as np
import matplotlib.pyplot as plt

# Create an array of x values from 0 to 4pi
x = np.linspace(0, 4 * np.pi, 1000)

# Create an array of y values using sin(x) and sin(x+pi)
y1 = np.sin(x)
y2 = np.sin(x + np.pi)

# Perform FFT and compute amplitude and phase spectra
# For y1
fft_y1 = np.fft.fft(y1)
amp_spectrum_y1 = np.abs(fft_y1)
phase_spectrum_y1 = np.rad2deg(np.angle(fft_y1))  # Convert from radians to degrees

# For y2
fft_y2 = np.fft.fft(y2)
amp_spectrum_y2 = np.abs(fft_y2)
phase_spectrum_y2 = np.rad2deg(np.angle(fft_y2))  # Convert from radians to degrees

# Calculate phase difference
phase_difference = phase_spectrum_y2 - phase_spectrum_y1

# Compare amplitude spectra
plt.figure(figsize=(12, 6))
plt.subplot(1, 3, 1)
plt.plot(amp_spectrum_y1, label="sin(x)")
plt.plot(amp_spectrum_y2, label="sin(x+pi)")
plt.title("Amplitude Spectrum")
plt.legend()
plt.grid(True)

# Compare phase spectra
plt.subplot(1, 3, 2)
plt.plot(phase_spectrum_y1, label="sin(x)")
plt.plot(phase_spectrum_y2, label="sin(x+pi)")
plt.title("Phase Spectrum")
plt.legend()
plt.grid(True)

# Show phase difference
plt.subplot(1, 3, 3)
plt.plot(phase_difference, label="Phase difference")
plt.title("Phase Difference")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
