import matplotlib.pyplot as plt
import os
import pandas as pd
from scipy.signal import find_peaks
import numpy as np
import argparse

def intermediates(df):
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

def detections(df):
    plt.subplot(2,1,1)
    plt.plot(df.iloc[:,1])
    plt.title("Bandpass filtered data")

    plt.subplot(5, 1, 5)
    x = df.iloc[:,5].to_numpy()
    idxs = np.where(x == 1)[0]

    plt.vlines(
        idxs,
        ymin=0,
        ymax=0.015,
        linestyles='--'
    )
    plt.plot(df.iloc[:,4])
    plt.plot(df.iloc[:,6])
    plt.plot(df.iloc[:,7])

    plt.title("Moving average")

    plt.tight_layout()
    plt.show()

def heartrate(df):
    plt.subplot(2,1,1)
    plt.plot(df.iloc[:,1])
    plt.title("Bandpass filtered data")

    plt.subplot(5, 1, 5)
    x = df.iloc[:,5].to_numpy()
    idxs = np.where(x == 1)[0]
    RR = np.diff(idxs)/fs
    plt.plot(RR)
    plt.title("Heartrate")
    plt.tight_layout()
    plt.show()

def parse_args():
	parser = argparse.ArgumentParser(
		description="Inspect output"
	)
	parser.add_argument("--start", type=int, default=2000, help="Start sample")
	parser.add_argument("--end", type=int, default=6000, help="End sample")
	parser.add_argument("--show", type=str, default="intermediates", help="What to output")
	parser.add_argument("--input", type=str, default="", help="Input data absolute path")
	return parser.parse_args()

def main(**args):
    INPUT = args["input"]
    start = args["start"]
    end = args["end"]

    df = (
        pd.read_csv(INPUT)
        .iloc[start:end, :]
        .reset_index(drop=True)
    )

    if args["show"] == "intermediates":
        intermediates(df)
    if args["show"] == "detections":
        detections(df)
    if args["show"] == "heartrate":
        heartrate(df)

if __name__ == '__main__':
	args = vars(parse_args())
	main(**args)
