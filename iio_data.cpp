#include "iio_data.h"
#include "qdebug.h"
#include <string.h>

Iio_data::Iio_data()
{

    ctx = iio_create_context_from_uri("ip:10.48.65.128");
    if (!ctx){
        qDebug()<< "Connection error, check context\n";
        shutdown();
    }

    dev = iio_context_find_device(ctx, "adxl355");
    if(!dev){
        qDebug()<< "Device error\n";
        shutdown();
    }
    qDebug()<< "Device name: "<<iio_device_get_name(dev)<<"\n";
}

void Iio_data::getData(double &x,double &y,double &z,double &temperature){

    for (int i = 0; i < iio_device_get_channels_count(dev); ++i){

        struct iio_channel *chn = iio_device_get_channel(dev, i);
        if(!chn){
            qDebug()<< "Channel error\n";
            shutdown();
        }

        double data;
        double scale;

        if (iio_channel_is_scan_element(chn))
        {
            if(!strcmp(iio_channel_get_id(chn), "accel_x"))
            {
                iio_channel_attr_read_double(chn, "raw", &data);
                iio_channel_attr_read_double(chn, "scale", &scale);
                x = data * scale;
            }
            else if(!strcmp(iio_channel_get_id(chn), "accel_y"))
            {
                iio_channel_attr_read_double(chn, "raw", &data);
                iio_channel_attr_read_double(chn, "scale", &scale);
                y = data * scale;
            }
            else if(!strcmp(iio_channel_get_id(chn), "accel_z"))
            {
                iio_channel_attr_read_double(chn, "raw", &data);
                iio_channel_attr_read_double(chn, "scale", &scale);
                z = data * scale;
            }

            else if(!strcmp(iio_channel_get_id(chn), "temp"))
            {
                double offset;
                iio_channel_attr_read_double(chn,"offset",&offset);
                iio_channel_attr_read_double(chn, "raw", &data);
                iio_channel_attr_read_double(chn, "scale", &scale);
                temperature = (data + offset) * scale/1000.0;
            }
        }
    }
}


void Iio_data:: shutdown(){
    if (ctx)
        iio_context_destroy(ctx);
}
