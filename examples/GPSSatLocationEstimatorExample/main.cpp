#include <iostream>

#include "SatLocationEstimatorFactory.h"
#include "IGPSEphemerisStorage.h"

using gnssRecv::satLocationEstimator::IGPSEphemerisStorage;
using gnssRecv::satLocationEstimator::SatLocationEstimatorFactory;

class DummyGPSEphemerisStorage : public IGPSEphemerisStorage
{
public:
	DummyGPSEphemerisStorage(
		double timestamp, double meanAnomaly, double semiMajor, double eccentricity,
		double longtitudeOfAscendingNode, double inclination, double argumentOfPerigee,
		double meanMotionDifference, double ascendingRate, double inclinationRate,
		double correctionSinPerigee, double correctionCosPerigee, double correctionSinRadial,
		double correctionCosRadial, double correctionSinInclination, double correctionCosInclination) :
		_timestamp(timestamp), _meanAnomaly(meanAnomaly), _semiMajor(semiMajor), _eccentricity(eccentricity),
		_longtitudeOfAscendingNode(longtitudeOfAscendingNode), _inclination(inclination),
		_argumentOfPerigee(argumentOfPerigee), _meanMotionDifference(meanMotionDifference),
		_ascendingRate(ascendingRate), _inclinationRate(inclinationRate),
		_correctionSinPerigee(correctionSinPerigee), _correctionCosPerigee(correctionCosPerigee),
		_correctionSinRadial(correctionSinRadial), _correctionCosRadial(correctionCosRadial),
		_correctionSinInclination(correctionSinInclination), _correctionCosInclination(correctionCosInclination)
	{
	}

	double timestamp() const override { return _timestamp; }

	double meanAnomaly() const override { return _meanAnomaly; }
	double semiMajorAxis() const override { return _semiMajor; }
	double eccentricity() const override { return _eccentricity; }
	double longtitudeOfAscendingNode() const override { return _longtitudeOfAscendingNode; }
	double inclination() const override { return _inclination; }
	double argumentOfPerigee() const override { return _argumentOfPerigee; }

	double meanMotionDifference() const override { return _meanMotionDifference; }
	double ascendingRate() const override { return _ascendingRate; }
	double inclinationRate() const override { return _inclinationRate; }

	double correctionSinPerigee() const override { return _correctionSinPerigee; }
	double correctionCosPerigee() const override { return _correctionCosPerigee; }
	double correctionSinRadial() const override { return _correctionSinRadial; }
	double correctionCosRadial() const override { return _correctionCosRadial; }
	double correctionSinInclination() const override { return _correctionSinInclination; }
	double correctionCosInclination() const override { return _correctionCosInclination; }
private:
	double _timestamp;
	double _meanAnomaly;
	double _semiMajor;
	double _eccentricity;
	double _longtitudeOfAscendingNode;
	double _inclination;
	double _argumentOfPerigee;
	double _meanMotionDifference;
	double _ascendingRate;
	double _inclinationRate;

	double _correctionSinPerigee;
	double _correctionCosPerigee;
	double _correctionSinRadial;
	double _correctionCosRadial;
	double _correctionSinInclination;
	double _correctionCosInclination;
};

int main()
{
        static const double pi = 3.1415926535;
        //Storage contains input data
        auto storage = std::make_shared<DummyGPSEphemerisStorage>(
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