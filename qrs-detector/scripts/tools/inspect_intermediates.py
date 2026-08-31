import matplotlib.pyplot as plt
import os
import pandas as pd
from scipy.signal import find_peaks
import numpy as np

SRC_DIR = os.path.abspath(os.path.join(os.getcwd(),"..",".."))
OUTPUT_PATH = os.path.join(SRC_DIR,"data","output.csv")
print(OUTPUT_PATH)

start=10000
end=start+2000

df = (
    pd.read_csv(OUTPUT_PATH)
    .iloc[start:end, :]
    .reset_index(drop=True)
)

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
plt.title("Squared")


plt.subplot(5,1,5)
plt.plot(df.iloc[:,4])
plt.title("Moving average")

plt.tight_layout()
plt.show()
