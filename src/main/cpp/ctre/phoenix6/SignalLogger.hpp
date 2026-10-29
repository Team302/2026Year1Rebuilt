#pragma once

#include <array>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "wpi/units/time.hpp"

namespace ctre
{
    namespace phoenix6
    {
        class SignalLogger
        {
        public:
            static void SetPath(const char *path) { (void)path; }
            static void Start() {}
            static void Stop() {}
            static void EnableAutoLogging(bool enable) { (void)enable; }

            static void WriteBoolean(std::string_view /*signalID*/, bool /*value*/, wpi::units::time::second_t /*timestamp*/) {}
            static void WriteDouble(std::string_view /*signalID*/, double /*value*/, std::string_view /*units*/, wpi::units::time::second_t /*timestamp*/) {}
            static void WriteInteger(std::string_view /*signalID*/, int64_t /*value*/, std::string_view /*units*/, wpi::units::time::second_t /*timestamp*/) {}
            static void WriteString(std::string_view /*signalID*/, const std::string & /*value*/, wpi::units::time::second_t /*timestamp*/) {}
            static void WriteDoubleArray(std::string_view /*signalID*/, const std::vector<double> & /*value*/, std::string_view /*units*/, wpi::units::time::second_t /*timestamp*/) {}
            static void WriteBooleanArray(std::string_view /*signalID*/, std::span<const bool> /*value*/, wpi::units::time::second_t /*timestamp*/) {}

            template <typename T>
            static void WriteStruct(std::string_view /*signalID*/, const T & /*value*/, wpi::units::time::second_t /*timestamp*/) {}

            template <typename T>
            static void WriteStructArray(std::string_view /*signalID*/, const std::array<T, 4> & /*value*/, wpi::units::time::second_t /*timestamp*/) {}
        };

    } // namespace phoenix6
} // namespace ctre
