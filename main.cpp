#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <thread>

#define TRIG 4  // GPIO23
#define ECHO 5  // GPIO24

void setup() {
    wiringPiSetup();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    digitalWrite(TRIG, LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

double getDistance() {
    // Send trig pulse
    digitalWrite(TRIG, HIGH);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    digitalWrite(TRIG, LOW);

    // Wait for echo start
    while (digitalRead(ECHO) == LOW);

    // Wait for echo end
    auto start = std::chrono::high_resolution_clock::now();
    while (digitalRead(ECHO) == HIGH);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate distance
    std::chrono::duration<double> elapsed = end - start;
    double distance = (elapsed.count() * 34300) / 2;

    return distance;
}

int main() {
    setup();
    while (true) {
        double distance = getDistance();
        std::cout << "Distance: " << distance << " cm" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
