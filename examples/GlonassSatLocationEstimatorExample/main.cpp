#include <iostream>

#include "SatLocationEstimatorFactory.h"
#include "IGlonassEphemerisStorage.h"

using gnssRecv::satLocationEstimator::IGlonassEphemerisStorage;
using gnssRecv::satLocationEstimator::SatLocationEstimatorFactory;

class DummyGlonassEphemerisStorage : public IGlonassEphemerisStorage
{
public:
	DummyGlonassEphemerisStorage(
		double timestamp,
		const std::array<double, 6>& locationAndVelocity,
		const std::array<double, 3>& acceleration,
		double satTimeToMdv, double gamma) :
		_timestamp(timestamp), _locationAndVelocity(locationAndVelocity), _acceleration(acceleration),
		_satTimeToMdv(satTimeToMdv), _gamma(gamma)
	{
	}

	double timestamp() const override { return _timestamp; }

	const std::array<double, 6>& locationAndVelocity() const override { return _locationAndVelocity; }

	const std::array<double, 3>& acceleration() const override { return _acceleration; }

	double satTimeToMdv() const { return _satTimeToMdv; }

	double gamma() const { return _gamma; }

	void updateLocationAndVelocity(
		const std::array<double, 6>& locationAndVelocity,
		double timestamp) override
	{
		_locationAndVelocity = locationAndVelocity;
		_timestamp = timestamp;
	}
private:
	double _timestamp;
	std::array<double, 6> _locationAndVelocity;
	std::array<double, 3> _acceleration;

	double _satTimeToMdv;
	double _gamma;
};

int main()
{
        //init storage
        std::array<double, 6> locationAndVelocity =
        {
            -16050.5732421875, 14867.69921875, 13161.53955078125,
            1.122589111328125, -1.430501937866211, 2.971652984619141
        };
        std::array<double, 3> acceleration =
        {
            -0.000000001862645, -0.000000000931323, 0
        };
        auto storage = std::make_shared<DummyGlonassEphemerisStorage>(
            78300,
            locationAndVelocity,
            acceleration,
            12.326985597e-6,
            0.909e-12        
        );
        //Create estimator
        auto estimator = SatLocationEstimatorFactory::makeEstimator(storage);
        //Calculate location
        auto location = estimator->calculateLocation(79103 - 0.078468392917055);

		std::cout << "Current satellite location: (" << storage->locationAndVelocity()[0] << ", " << storage->locationAndVelocity()[1] << ", " << storage->locationAndVelocity()[2] <<  ")\n";
        std::cout << "Current satellite velocity: (" << storage->locationAndVelocity()[3] << ", " << storage->locationAndVelocity()[4] << ", " << storage->locationAndVelocity()[5] << ")\n";
        std::cout << "Current sattelite geocentric location: (" << location.x << ", " << location.y << ", " << location.z << ")\n";

        return 0;
}