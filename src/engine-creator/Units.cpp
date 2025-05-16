#include "Units.h"

namespace Units
{
    const std::unordered_map<UnitType, std::string> &Unit::getUnitToStringMap()
    {
        return unitToString;
    } 

    std::string Unit::operator[](UnitType unitType) noexcept
    {
        return unitToString[unitType];
    }

    UnitType Unit::operator[](std::string_view unitType) noexcept
    {
        return stringToUnit[unitType];
    }
};