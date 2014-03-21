/*
 * Introduction to Computer Graphics
 *
 * TestRead.cpp
 *
 */

#include "TestRead.h"

#include "BezierPatch.h"
#include "ReadBezierPatches.h"

TestRead::TestRead()
{
    // constructor
}

TestRead::~TestRead()
{
    // destructor
}

int TestRead::init()
{
    return 0;
}

int TestRead::run()
{
    try {
        std::vector<BezierPatch> BezierPatches;

        std::cout << "Reading data file: teapot.data - " << std::endl;

        int result = ReadBezierPatches("resources/data/teapot.data", BezierPatches);

        if (result == 0)
            std::cout << "succeded";
        else {
            std::cout << "failed";
        }
        std::cout << " - Number of Bezier Patches: " << BezierPatches.size() << std::endl;
        std::cout << "The Bezier Patches read:" << std::endl;
        std::cout << "========================" << std::endl;
        for (int i = 0; i < (int)BezierPatches.size(); ++i) {
            std::cout << "Bezier Patch[" << std::setw(2) << i+1 << "]:" << std::endl;
            std::cout << "[" << std::endl;
            std::cout << BezierPatches[i] << "]" << std::endl << std::endl;
        }
        std::cout << std::endl;

        return result;
    }
    catch (std::exception const& Exception) {
        std::cout << "Exception: " << Exception.what() << std::endl;
    }
    return 0;
}

