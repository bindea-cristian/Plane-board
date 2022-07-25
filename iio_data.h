#ifndef IIO_DATA_H
#define IIO_DATA_H
#include "iio.h"

class Iio_data
{
public:
    Iio_data();
    void showData();

    struct iio_device *dev;
    struct iio_context *ctx;

    void getData(double &x,double &y,double &z,double &temperature);

    void shutdown();
};

#endif // IIO_DATA_H
