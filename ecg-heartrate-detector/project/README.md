# ECG Heart-rate Detector

This project is a low deployment C++ application for ECG QRS Complex Detection. It utilizes the Pan-Tompkins Algorithm.

<https://en.wikipedia.org/wiki/Pan%E2%80%93Tompkins_algorithm>

Data:
<https://physionet.org/files/nstdb/1.0.0/>

DSP involved:
* Bandpass filtering
* Peak detection
* Adaptive thresholds

---

Dev build
```
make
```

---

## Development Notes

* Using patient data `118e00.dat`

### Development stages

* Make sure ECG file stream can run through QEMU to the application
* Use a TCP stream to simulate a host process
* Create a virtual serial sensor
* Eventually replace the sensor with real hardware interfaces
