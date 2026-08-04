import wfdb
import numpy as np
import os

SRC_DIR = os.getcwd()
PATH = os.path.join(SRC_DIR,"data","physionet.org","files","nstdb","1.0.0","118e00")

record = wfdb.rdrecord(PATH)
ecg = record.p_signal

print(PATH)
print(ecg.shape)
print(record.fs)

lead = ecg[:, 0]
lead.astype(np.int16).tofile(
        os.path.join(SRC_DIR,"data","118e00.raw")
        )
