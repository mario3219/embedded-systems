#include <fstream>
#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    fs::path ROOT = fs::current_path();
    for (int i = 0; i < 3; i++) {ROOT = ROOT.parent_path();}
    fs::path INPUT = ROOT / "data" / "118e00.raw";

    std::ifstream input(INPUT, std::ios::binary);

    if (!input) {
        std::cerr << "Could not open ECG file\n";
        return 1;
    }

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/ecg.sock");

    std::cout << "Waiting for connection, start the QEMU QRS Detector" << "\n";

    while (connect(
        sock,
        reinterpret_cast<sockaddr*>(&addr),
        sizeof(addr)
    ) < 0) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }

    constexpr double fs = 250.0;

    auto sample_period =
        std::chrono::duration<double>(1.0 / fs);

    int16_t sample;

    while (input.read(
        reinterpret_cast<char*>(&sample),
        sizeof(sample)
    )) {
        std::cout << sample << "\n";

        write(sock, &sample, sizeof(sample));

        std::this_thread::sleep_for(sample_period);
    }

    close(sock);
}
