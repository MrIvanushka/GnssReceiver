#pragma once

namespace gnssRecv
{

class IDataInput
{
public:
	virtual bool getSignal(double* signal, double* timestamp, int* PRN) = 0;
};

} //namespace gnssRecv