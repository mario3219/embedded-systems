# ECG Heart-rate Detector

This project is a low deployment C++ application for ECG QRS Complex Detection. It utilizes the Pan-Tompkins Algorithm.

<https://en.wikipedia.org/wiki/Pan%E2%80%93Tompkins_algorithm>

Data:

<https://physionet.org/files/nstdb/1.0.0/>

<https://physionet.org/content/nstdb/1.0.0/old/>

DSP involved:
* Bandpass filtering
* Peak detection
* Adaptive thresholds

---

## Requirements and setup

Preferably work in a conda environment

```
conda create -n project-env python=3.14.4
conda activate project-env

conda install -c conda-forge wfdb
```

---

## Development build

Requirements and install:
```
sudo apt install \
cmake
```

There are three source directories:
* `/source`
Implementation of code.
* `/host-source`
The SoC variant of the implementation intended to compile to host.
* `/target-source`
The final SoC variant intended to compile to target.

For the `/source` variant, go into `/source/build` and run `cmake ..` to generate the Makefile and run `make` to compile.

---

## Algorithm setup

* Bandpass filter
* Derivation operator
* Squaring operator
* Moving window integration
* Decision window

---

## Development Notes

* Window array size equation:
N=W*Fs
Where W is the time window to analyze.

* Using patient data `118e00.dat`
* Sampling Frequency: 360 Hz
* 650,000 samples
* 2 channel lead

### Development stages

* Make sure ECG file stream can run through QEMU to the application
* Use a TCP stream to simulate a host process
* Create a virtual serial sensor
* Eventually replace the sensor with real hardware interfaces
