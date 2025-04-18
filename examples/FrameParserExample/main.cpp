#include <fstream>
#include <iostream>

#include "CommonGPSSatelliteStorage.h"
#include "FrameParserFactory.h"

int main()
{
        //Open some file, be sure it is located in build/ folder
        std::string inFileName = "FrameParserExampleSignal.txt";
        std::ifstream inFile;
        inFile.open(inFileName.c_str());
        std::vector<double> corrValues;

        if (!inFile.is_open())
        {
                LOG_ERROR("Couldn't open signal file");
                return 1;
        }

        //Storage will contain the result
        auto storage = std::make_shared<CommonGPSSatelliteStorage>();
        //Create a parser
        auto parser = FrameParserFactory::makeParser(storage);

        //Pass previously received signal. Here we are using its imaginary part
        for (double value = 1; inFile >> value;)
        {
            parser->handleSignal(value);
        }

        //Extract parsed data
        std::cout << "=================== HOW ====================" << std::endl;
        std::cout << "Z counter: " << (uint32_t)storage->zCounter() << std::endl;
        std::cout << "============ SATELLITE CLOCK ===============" << std::endl;
        std::cout << "Week number: " << (uint32_t)storage->satelliteClock().weekNumber() << std::endl;
        std::cout << "URA index: " << (uint32_t)storage->satelliteClock().uraIndex() << std::endl;
        std::cout << "SV Health: " << (uint32_t)storage->satelliteClock().svHealth() << std::endl;
        std::cout << "L2 P Data Flag: " << (uint32_t)storage->satelliteClock().l2pDataFlag() << std::endl;
        std::cout << "t_GD: " << (uint32_t)storage->satelliteClock().tGD() << std::endl;
        std::cout << "IODC: " << (uint32_t)storage->satelliteClock().iodc() << std::endl;
        std::cout << "t_OC: " << (uint32_t)storage->satelliteClock().tOC() << std::endl;
        std::cout << "t_f2: " << (uint32_t)storage->satelliteClock().af2() << std::endl;
        std::cout << "a_f1: " << (uint32_t)storage->satelliteClock().af1() << std::endl;
        std::cout << "a_f0: " << (uint32_t)storage->satelliteClock().af0() << std::endl;
        std::cout << "=============== EPHEMERIS ==================" << std::endl;
        std::cout << "IODE: " << (uint32_t)storage->ephemeris().iode() << std::endl;
        std::cout << "Delta_N: " << storage->ephemeris().deltaN() << std::endl;
        std::cout << "M_0: " << storage->ephemeris().m0() << std::endl;
        std::cout << "Eccentricity: " << storage->ephemeris().e() << std::endl;
        std::cout << "Sqrt of Semimajor: " << storage->ephemeris().sqrtOfA() << std::endl;
        std::cout << "t_OE: " << storage->ephemeris().tOE() << std::endl;
        std::cout << "AODO: " << (uint32_t)storage->ephemeris().aodo() << std::endl;
        std::cout << "Longtitude of ascending node: " << storage->ephemeris().omega0() << std::endl;
        std::cout << "Inclination: " << storage->ephemeris().i0() << std::endl;
        std::cout << "Argument of periapsis: " << storage->ephemeris().omega() << std::endl;
        std::cout << "Ascending rate: " << storage->ephemeris().ascendingRate() << std::endl;
        std::cout << "IDOT: " << (uint32_t)storage->ephemeris().idot() << std::endl;
        std::cout << "C_RS: " << storage->ephemeris().cRS() << std::endl;
        std::cout << "C_UC: " << storage->ephemeris().cUC() << std::endl;
        std::cout << "C_US: " << storage->ephemeris().cUS() << std::endl;
        std::cout << "C_IC: " << storage->ephemeris().cIC() << std::endl;
        std::cout << "C_IS: " << storage->ephemeris().cIS() << std::endl;
        std::cout << "C_RC: " << storage->ephemeris().cRC() << std::endl;
        std::cout << "============================================" << std::endl << std::endl;

        //To measure algorithm duration
        LOG_INFO("All data is successfully presented");

        return 0;
}