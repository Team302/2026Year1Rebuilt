#pragma once

namespace ctre
{
    namespace phoenix
    {
        namespace motorcontrol
        {

            enum class ControlMode
            {
                PercentOutput = 0,
                Disabled = 1,
            };

            enum class NeutralMode
            {
                Coast = 0,
                Brake = 1,
            };

            namespace can
            {
                class WPI_TalonSRX
                {
                public:
                    explicit WPI_TalonSRX(int deviceNumber)
                        : m_deviceNumber(deviceNumber)
                    {
                    }

                    ~WPI_TalonSRX() = default;

                    void ConfigFactoryDefault() {}

                    void SetInverted(bool inverted)
                    {
                        m_inverted = inverted;
                    }

                    void SetSensorPhase(bool phase)
                    {
                        m_sensorPhase = phase;
                    }

                    void SetNeutralMode(NeutralMode mode)
                    {
                        m_neutralMode = mode;
                    }

                    void ConfigOpenloopRamp(double secondsFromNeutralToFull)
                    {
                        m_openLoopRamp = secondsFromNeutralToFull;
                    }

                    void ConfigClosedloopRamp(double secondsFromNeutralToFull)
                    {
                        m_closedLoopRamp = secondsFromNeutralToFull;
                    }

                    void ConfigPeakOutputForward(double percentOutput)
                    {
                        m_peakOutputForward = percentOutput;
                    }

                    void ConfigPeakOutputReverse(double percentOutput)
                    {
                        m_peakOutputReverse = percentOutput;
                    }

                    void ConfigNominalOutputForward(double percentOutput)
                    {
                        m_nominalOutputForward = percentOutput;
                    }

                    void ConfigNominalOutputReverse(double percentOutput)
                    {
                        m_nominalOutputReverse = percentOutput;
                    }

                    void ConfigContinuousCurrentLimit(int amps)
                    {
                        m_continuousCurrentLimit = amps;
                    }

                    void ConfigPeakCurrentLimit(int amps)
                    {
                        m_peakCurrentLimit = amps;
                    }

                    void ConfigPeakCurrentDuration(int milliseconds)
                    {
                        m_peakCurrentDuration = milliseconds;
                    }

                    void EnableCurrentLimit(bool enable)
                    {
                        m_currentLimitEnabled = enable;
                    }

                    void Set(ControlMode mode, double value)
                    {
                        (void)mode;
                        m_output = value;
                        Set(value);
                    }

                    void Set(double outputValue)
                    {
                        m_output = outputValue;
                    }

                    int GetDeviceNumber() const
                    {
                        return m_deviceNumber;
                    }

                    double GetOutput() const
                    {
                        return m_output;
                    }

                private:
                    int m_deviceNumber = 0;
                    bool m_inverted = false;
                    bool m_sensorPhase = false;
                    NeutralMode m_neutralMode = NeutralMode::Coast;
                    double m_openLoopRamp = 0.0;
                    double m_closedLoopRamp = 0.0;
                    double m_peakOutputForward = 1.0;
                    double m_peakOutputReverse = -1.0;
                    double m_nominalOutputForward = 0.0;
                    double m_nominalOutputReverse = 0.0;
                    int m_continuousCurrentLimit = 0;
                    int m_peakCurrentLimit = 0;
                    int m_peakCurrentDuration = 0;
                    bool m_currentLimitEnabled = false;
                    double m_output = 0.0;
                };

            } // namespace can
        } // namespace motorcontrol
    } // namespace phoenix
} // namespace ctre
