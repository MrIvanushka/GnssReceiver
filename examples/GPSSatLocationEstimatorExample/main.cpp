#include <fstream>
#include <iostream>

#include "CommonGPSEphemerisStorage.h"
#include "SatLocationEstimatorFactory.h"

int main()
{
        static const double pi = 3.1415926535;
        //Storage contains input data
        auto storage = std::make_shared<CommonGPSEphemerisStorage>(
            201584.0,                           //t_oe
            0.304183455184102 * pi,             //mean anomaly
            pow(5153.762765884399414, 2),       //semi major axis
            0.010925623239018,                  //eccentricity
            -0.207362390588969 * pi,            //longtitude of ascending node
            0.306331528816372 * pi,             //inclination
            0.514487708918750 * pi,             //argument of perigee
            0.000000001370950 * pi,             //mean motion difference
            -0.000000002564661 * pi,            //longtitude of ascending node rate
            0.000000000002956 * pi,             //inclination rate
            0.000010803341866,                  //C_us
            -0.000007700175047,                 //C_uc
            -148.875000000000000,               //C_rs
            177.031250000000000,                //C_rc
            -0.000000111758709,                 //C_is
            -0.000000176951289                  //C_ic
        );
        //Create estimator
        auto estimator = SatLocationEstimatorFactory::makeEstimator(storage);
        //Calculate location
        auto location = estimator->calculateLocation(28818);

        std::cout << "Sattelite geocentric location: (" << location.x << ", " << location.y << ", " << location.z << ")\n";

        return 0;
}