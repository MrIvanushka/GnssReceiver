#include <fstream>
#include <iostream>

#include "CommonGlonassEphemerisStorage.h"
#include "SatLocationEstimatorFactory.h"

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
        auto storage = std::make_shared<CommonGlonassEphemerisStorage>(
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