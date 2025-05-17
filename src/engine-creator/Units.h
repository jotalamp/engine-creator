#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

namespace Unit
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
            Inch,
            L,
            cm2,
            lb
        };

    class Units
    {
        

    public:
        static Units units;
        std::string operator[](UnitType unitType) noexcept;
        UnitType operator[](std::string_view unitType) noexcept;
        static std::unordered_map<UnitType, std::string> &getUnitToStringMap();
        static std::unordered_map<std::string_view, UnitType> &getStringToUnitMap();

        static const inline char *unitsAsStrings[]{"units.none",
                                          "units.deg",
                                          "units.cc",
                                          "units.thou",
                                          "units.lb_ft",
                                          "units.mm",
                                          "units.g",
                                          "units.rpm",
                                          "units.inch",
                                          "units.kg",
                                          "units.L",
                                          "units.cm2",
                                          "units.lb"};

    private:
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
            {UnitType::L, "units.L"},
            {UnitType::cm2, "units.cm2"},
            {UnitType::lb, "units.lb"},
            {UnitType::Kg, "units.kg"}};

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
            {"units.L", UnitType::L},
            {"units.cm2", UnitType::cm2},
            {"units.lb", UnitType::lb},
            {"units.kg", UnitType::Kg}};
    };
}