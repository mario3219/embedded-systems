#include <iostream>
#include <fstream>
#include <cstdint>
#include <fcntl.h>
#include <unistd.h>

#include "PanTomp.h"

int main()
{
    constexpr double fs = 250;
    constexpr double T = 0.150;
    constexpr int T_train = 2;
    constexpr int searchRadius = 10;

    constexpr int trainingSamples = static_cast<int>(fs * T_train);
    int counter = 0;
    bool trained = false;

    PanTomp pt(fs, T, T_train, searchRadius);

    //std::ofstream outputFile("output.csv");
    std::ofstream outputFile("/mnt/host/output.csv");

    if (!outputFile) {
        std::cerr << "Could not open output file\n";
        return 1;
    }

    int fd = open("/dev/vport1p1", O_RDONLY);

    if (fd < 0) {
        std::cerr << "Could not open ECG input device\n";
        return 1;
    }

    while (true) {
        int16_t x;

        ssize_t n = read(fd, &x, sizeof(x));

        if (n < 0) {
            perror("read");
            break;
        }

        if (n == 0) {
            std::cerr << "ECG stream closed\n";
            break;
        }

        if (n != sizeof(x)) {
            std::cerr << "Partial ECG sample received\n";
            continue;
        }

        double sample = static_cast<double>(x);

        pt.process(sample);

        if (!trained) {
            pt.add_pretrain();

            ++counter;

            if (counter >= trainingSamples) {
                pt.pretrain();
                trained = true;

                std::cout << "Training complete\n";
            }
        }
        else {
            pt.analyze();
        }

        pt.write(outputFile, sample);
    }

    close(fd);

    return 0;
}
