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

## Development build

(Empty for now)

---

## Development Notes

* Using patient data `118e00.dat`
* Sampling Frequency: 250 Hz

### Development stages

* Make sure ECG file stream can run through QEMU to the application
* Use a TCP stream to simulate a host process
* Create a virtual serial sensor
* Eventually replace the sensor with real hardware interfaces
