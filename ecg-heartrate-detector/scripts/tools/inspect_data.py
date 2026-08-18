import matplotlib.pyplot as plt
import os
import pandas as pd

SRC_DIR = os.path.abspath(os.path.join(os.getcwd(),"..",".."))
OUTPUT_PATH = os.path.join(SRC_DIR,"data","output.csv")
print(OUTPUT_PATH)

df = pd.read_csv(OUTPUT_PATH).iloc[103000:105000,:]

plt.subplot(2,1,1)
plt.plot(df.iloc[:,0])

plt.subplot(2,1,2)
plt.plot(df.iloc[:,1])

plt.tight_layout()
plt.show()
