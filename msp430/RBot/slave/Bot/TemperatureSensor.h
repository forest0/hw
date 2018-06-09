#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

class TemperatureSensor {
private:


public:
    TemperatureSensor();
    double read() const;
    ~TemperatureSensor();
};

#endif /* TEMPERATURESENSOR_H */
