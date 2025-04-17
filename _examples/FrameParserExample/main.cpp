#include <fstream>
#include <iostream>
#include "GPSFrameParser.h"

int main()
{
        //Open some file, be sure it is located in build/ folder
        std::string inFileName = "signal.txt";
        std::ifstream inFile;
        inFile.open(inFileName.c_str());
        std::vector<double> corrValues;

        if (!inFile.is_open())
        {
                LOG_ERROR("Couldn't open signal file");
                return 1;
        }
        
        //Context will contain the result. It will also have more feates in future releases
        auto context = std::make_shared<GPSContext>();
        //Create a parser
        GPSFrameParser parser(context);
        //Specify satellite ID. Let it be PRN=7
        auto prn = 7;

        //Pass previously received signal. Here we are using its imaginary part
        for (double value = 1; inFile >> value;)
        {
            parser.handleSignal(value, prn);
        }

        //Extract parsed data
        auto storage = std::dynamic_pointer_cast<GPSSatelliteStorage>(context->storage(prn));

        std::cout << "=================== HOW ====================" << std::endl;
        std::cout << "Z counter: " << (uint32_t)storage->lastHow.zCounter() << std::endl;
        std::cout << "============ SATELLITE CLOCK ===============" << std::endl;
        std::cout << "Week number: " << (uint32_t)storage->lastSatClock.weekNumber() << std::endl;
        std::cout << "URA index: " << (uint32_t)storage->lastSatClock.uraIndex() << std::endl;
        std::cout << "SV Health: " << (uint32_t)storage->lastSatClock.svHealth() << std::endl;
        std::cout << "L2 P Data Flag: " << (uint32_t)storage->lastSatClock.l2pDataFlag() << std::endl;
        std::cout << "t_GD: " << (uint32_t)storage->lastSatClock.tGD() << std::endl;
        std::cout << "IODC: " << (uint32_t)storage->lastSatClock.iodc() << std::endl;
        std::cout << "t_OC: " << (uint32_t)storage->lastSatClock.tOC() << std::endl;
        std::cout << "t_f2: " << (uint32_t)storage->lastSatClock.af2() << std::endl;
        std::cout << "a_f1: " << (uint32_t)storage->lastSatClock.af1() << std::endl;
        std::cout << "a_f0: " << (uint32_t)storage->lastSatClock.af0() << std::endl;
        std::cout << "=============== EPHEMERIS ==================" << std::endl;
        std::cout << "IODE: " << (uint32_t)storage->lastEphemeris.iode() << std::endl;
        std::cout << "Delta_N: " << storage->lastEphemeris.deltaN() << std::endl;
        std::cout << "M_0: " << storage->lastEphemeris.m0() << std::endl;
        std::cout << "Eccentricity: " << storage->lastEphemeris.e() << std::endl;
        std::cout << "Sqrt of Semimajor: " << storage->lastEphemeris.sqrtOfA() << std::endl;
        std::cout << "t_OE: " << storage->lastEphemeris.tOE() << std::endl;
        std::cout << "AODO: " << (uint32_t)storage->lastEphemeris.aodo() << std::endl;
        std::cout << "Longtitude of ascending node: " << storage->lastEphemeris.omega0() << std::endl;
        std::cout << "Inclination: " << storage->lastEphemeris.i0() << std::endl;
        std::cout << "Argument of periapsis: " << storage->lastEphemeris.omega() << std::endl;
        std::cout << "Ascending rate: " << storage->lastEphemeris.ascendingRate() << std::endl;
        std::cout << "IDOT: " << (uint32_t)storage->lastEphemeris.idot() << std::endl;
        std::cout << "C_RS: " << storage->lastEphemeris.cRS() << std::endl;
        std::cout << "C_UC: " << storage->lastEphemeris.cUC() << std::endl;
        std::cout << "C_US: " << storage->lastEphemeris.cUS() << std::endl;
        std::cout << "C_IC: " << storage->lastEphemeris.cIC() << std::endl;
        std::cout << "C_IS: " << storage->lastEphemeris.cIS() << std::endl;
        std::cout << "C_RC: " << storage->lastEphemeris.cRC() << std::endl;
        std::cout << "============================================" << std::endl << std::endl;

        return 0;
}