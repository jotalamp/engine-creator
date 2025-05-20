#include "../../3rdparty/googletest/googlemock/include/gmock/gmock.h"

int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}