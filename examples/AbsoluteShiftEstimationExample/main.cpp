#include <fstream>
#include <iostream>

#include "FrameParserFactory.h"
#include "IGPSSatelliteStorage.h"

using gnssRecv::frameParser::IGPSSatelliteStorage;
using gnssRecv::frameParser::FrameParserFactory;
using gnssRecv::frameParser::IFrameParser;
using gnssRecv::frameParser::SatClockHeader;
using gnssRecv::frameParser::EphemerisHeader;

class DummyGPSSatelliteStorage : public IGPSSatelliteStorage
{
public:
    void setZCounter(uint32_t value) { _zCounter = value; }
    void setSatelliteClock(const SatClockHeader& head) { _satelliteClock = head; }
    void setEphemeris(const EphemerisHeader& head) { _ephemeris = head; }

    uint32_t zCounter() const { return _zCounter; }
    const SatClockHeader& satelliteClock() const { return _satelliteClock; }
    const EphemerisHeader& ephemeris() const { return _ephemeris; }
private:
    uint32_t _zCounter;
    SatClockHeader _satelliteClock;
    EphemerisHeader _ephemeris;
};

int main()
{

        //Open some file, be sure it is located in build/ folder
        std::string inFileName = "sig.txt";
        std::ifstream inFile;
        inFile.open(inFileName.c_str());
        std::vector<double> corrValues;

        if (!inFile.is_open())
        {
                LOG_ERROR("Couldn't open signal file");
                return 1;
        }

        //Storage will contain the result
        std::vector<std::shared_ptr<DummyGPSSatelliteStorage>> storages =
        {
            std::make_shared<DummyGPSSatelliteStorage>(),
            std::make_shared<DummyGPSSatelliteStorage>(),
            std::make_shared<DummyGPSSatelliteStorage>(),
            std::make_shared<DummyGPSSatelliteStorage>(),
            std::make_shared<DummyGPSSatelliteStorage>(),
            std::make_shared<DummyGPSSatelliteStorage>()
        };
        //Create a parser
        std::vector<std::unique_ptr<IFrameParser>> parser;
        parser.emplace_back(FrameParserFactory::makeParser(storages[0]));
        parser.emplace_back(FrameParserFactory::makeParser(storages[1]));
        parser.emplace_back(FrameParserFactory::makeParser(storages[2]));
        parser.emplace_back(FrameParserFactory::makeParser(storages[3]));
        parser.emplace_back(FrameParserFactory::makeParser(storages[4]));
        parser.emplace_back(FrameParserFactory::makeParser(storages[5]));

        //Pass previously received signal. Here we are using its imaginary part
        auto currentParserIndex = 0;
        int sigCount = 0;
        for (double value = 1; inFile >> value;)
        {
            ++sigCount;
            parser[currentParserIndex]->handleSignal(value);
            ++currentParserIndex;
            if (currentParserIndex >= 6)
                currentParserIndex = 0;
        }
        for (auto i = 0u; i < 6; ++i)
        {
            std::cout << "SATELLITE " << i << " Z Counter " << storages[i]->zCounter() << " signal shift " << parser[i]->bitsAfterLastSuperframe() << std::endl;
        }
        LOG_INFO("Ended");
        return 0;
}