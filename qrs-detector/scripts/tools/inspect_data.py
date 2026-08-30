import matplotlib.pyplot as plt
import os
import pandas as pd
from scipy.signal import find_peaks
import numpy as np

SRC_DIR = os.path.abspath(os.path.join(os.getcwd(),"..",".."))
OUTPUT_PATH = os.path.join(SRC_DIR,"data","output.csv")
print(OUTPUT_PATH)

thresI = 0.003
thresF = 0.015
fs = 250;

start=0
end=2*fs

df = (
    pd.read_csv(OUTPUT_PATH)
    .iloc[start:end, :]
    .reset_index(drop=True)
)

peaksI,_ = find_peaks(
    df.iloc[:,4],
    height=thresI,
    distance=int(0.2*fs)
)

peaksF,_ = find_peaks(
    df.iloc[:,3],
    height=thresF,
    distance=int(0.2*fs)
)

print(f"{len(peaksF)},{len(peaksI)}")

plt.subplot(5,1,1)
plt.plot(df.iloc[:,0])
plt.title("Raw data")

plt.subplot(5,1,2)
plt.plot(df.iloc[:,1])
plt.title("Bandpass filtered")

plt.subplot(5,1,3)
plt.plot(df.iloc[:,2])
plt.title("Differentiated")

plt.subplot(5,1,4)
plt.plot(df.iloc[:,3])
plt.plot(peaksF, df.iloc[peaksI,3],'x')
plt.title("Squared")

plt.subplot(5,1,5)
plt.plot(df.iloc[:,4])
plt.plot(peaksI, df.iloc[peaksI,4],'x')
plt.title("Moving average")

plt.tight_layout()
plt.show()

df = (
    pd.read_csv(OUTPUT_PATH)
    .reset_index(drop=True)
)

thresI = 0.003
thresF = 0.015
fs = 250
T = 2

peaksI,_ = find_peaks(
    df.iloc[0:2*fs,4],
    height=thresI,
    distance=int(0.2*fs)
)

peaksF,_ = find_peaks(
    df.iloc[0:2*fs,3],
    height=thresF,
    distance=int(0.2*fs)
)

print(f"{len(peaksF)},{len(peaksI)}")

delays = []
for i,peakF in enumerate(peaksF):
    delays.append(peaksI[i]-peakF)
delays = np.array(delays)
print(f"Mean: {np.mean(delays)}")
