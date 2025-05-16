#pragma once

#include <unordered_map>
#include <string>

namespace Units
{
    enum class UnitType
    {
        None,
        Rpm,
        Deg,
        Cc,
        Thou,
        Lb_ft,
        mm,
        g,
        Kg,
        Inch
    };

    struct Unit
    {
    public:
        std::string operator[](UnitType unitType) noexcept;
        UnitType operator[](std::string_view unitType) noexcept;
        const std::unordered_map<UnitType, std::string> &getUnitToStringMap();

    private:
        static inline std::unordered_map<std::string_view, UnitType> stringToUnit = {
            {"units.none", UnitType::None},
            {"units.deg", UnitType::Deg},
            {"units.cc", UnitType::Cc},
            {"units.thou", UnitType::Thou},
            {"units.lb_ft", UnitType::Lb_ft},
            {"units.mm", UnitType::mm},
            {"units.g", UnitType::g},
            {"units.rpm", UnitType::Rpm},
            {"units.inch", UnitType::Inch},
            {"units.kg", UnitType::Kg}};

        static inline std::unordered_map<UnitType, std::string> unitToString = {
            {UnitType::None, "units.none"},
            {UnitType::Deg, "units.deg"},
            {UnitType::Cc, "units.cc"},
            {UnitType::Thou, "units.thou"},
            {UnitType::Lb_ft, "units.lb_ft"},
            {UnitType::mm, "units.mm"},
            {UnitType::g, "units.g"},
            {UnitType::Rpm, "units.rpm"},
            {UnitType::Inch, "units.inch"},
            {UnitType::Kg, "units.kg"}};
    };
}