#include "sensor.hpp"

SensorAdapter::SensorAdapter(Proxies::AnalogInputObj &adc, Proxies::Timeout timeout) 
{
  this->adaptee_ = new AnalogInput(adc, timeout);
};

SensorAdapter::~SensorAdapter() 
{
  delete this->adaptee_;
};
