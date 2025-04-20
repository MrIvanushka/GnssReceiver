#include <fstream>
#include <iostream>

#include "ISatelliteTable.h"
#include "ReceiverLocationEstimatorFactory.h"

class DummySatelliteParams : public ISatelliteParams
{
public:
    DummySatelliteParams(double pseudoDelay, const Vector3& location) :
        _pseudoDelay(pseudoDelay), _location(location)
    { }

    double pseudoDelay() const override { return _pseudoDelay; }

    Vector3 location() const override { return _location; }
private:
    double _pseudoDelay;
    Vector3 _location;
};

class DummySatelliteTable : public ISatelliteTable
{
public:
    DummySatelliteTable(const std::vector<SatParamsPtr>& satParams) : _satParams(satParams)
    { }

    virtual ProtocolType type() const override { return ProtocolType::Glonass; }

    virtual const std::vector<SatParamsPtr> satelliteParams() const { return _satParams; }
private:
    std::vector<SatParamsPtr> _satParams;
};

int main()
{
    //Storage contains input data
    std::vector<std::shared_ptr<ISatelliteParams>> satParams =
    {
        std::make_shared<DummySatelliteParams>(0.078468392917055, Vector3(-15127.39396, 13578.55601, 15439.89883)),
        std::make_shared<DummySatelliteParams>(0.073241217768673, Vector3(-10332.95092, 10309.08216, 20938.74277)),
        std::make_shared<DummySatelliteParams>(0.063959853789407, Vector3(9094.352734, 10099.50583, 21584.47168)),
        std::make_shared<DummySatelliteParams>(0.070031111471884, Vector3(23460.87267, 3694.756856, 9346.33086)),
        std::make_shared<DummySatelliteParams>(0.076208527072563, Vector3(-10304.08018, -3038.842641, 23112.93221)),
        std::make_shared<DummySatelliteParams>(0.076981791669830, Vector3(12543.02548, 22179.56769, -1203.471962)),
        std::make_shared<DummySatelliteParams>(0.065272271294675, Vector3(15913.93123, 12836.7792, 15296.29651)),
        std::make_shared<DummySatelliteParams>(0.066006480269953, Vector3(11437.06314, -1648.880113, 22726.81287)),
        std::make_shared<DummySatelliteParams>(0.078203448403038, Vector3(604.1925791, -16451.05345, 19430.95612)),
    };
    auto satTable = std::make_shared<DummySatelliteTable>(satParams);
    //Create estimator
    auto estimator = ReceiverLocationEstimatorFactory::makeEstimator(satTable);
    //Calculate location
    auto [location, time] = estimator->calculateLocation(28818);

    std::cout << "Receiver geocentric location: (" << location.x << ", " << location.y << ", " << location.z << ")\n";
    std::cout << "Receiver time: (" << time << ")\n";

    return 0;
}