import matplotlib.pyplot as plt
import os
import pandas as pd
from scipy.signal import find_peaks
import numpy as np

SRC_DIR = os.path.abspath(os.path.join(os.getcwd(),"..",".."))
OUTPUT_PATH = os.path.join(SRC_DIR,"data","output.csv")
print(OUTPUT_PATH)

start=2000
end=start+10000
fs=250

df = (
    pd.read_csv(OUTPUT_PATH)
    .iloc[start:end, :]
    .reset_index(drop=True)
)

plt.subplot(2,1,1)
plt.plot(df.iloc[:,1])
plt.title("Bandpass filtered data")

plt.subplot(5, 1, 5)
x = df.iloc[:,5].to_numpy()
idxs = np.where(x == 1)[0]
RR = np.diff(idxs)/fs
plt.plot(RR)
plt.title("Heartrate")
#plt.tight_layout()
plt.show()
