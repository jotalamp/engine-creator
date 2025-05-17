#include "Units.h"

namespace Unit
{
    std::string Units::operator[](UnitType unitType) noexcept
    {
        return unitToString[unitType];
    }

    UnitType Units::operator[](std::string_view unitType) noexcept
    {
        return stringToUnit[unitType];
    }

    std::unordered_map<UnitType, std::string> &Units::getUnitToStringMap()
    {
        return unitToString;
    }

    std::unordered_map<std::string_view, UnitType> &Units::getStringToUnitMap()
    {
        return stringToUnit;
    }
};