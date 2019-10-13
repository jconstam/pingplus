#include <string>

class Ping
{
    public:
        explicit Ping( const std::string& hostname );
        void Send( );
    private:
        std::string m_hostname;
};

class PingData
{
    public:
        explicit PingData( const std::string& rawData );
    private:
        int m_txCount;
        int m_rxCount;
        float m_rttMin;
        float m_rttAvg;
        float m_rttMax;
        float m_rttMDev;
};