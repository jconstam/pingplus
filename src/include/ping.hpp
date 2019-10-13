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

        void PrintStats( void );
    private:
        int m_txCount;
        int m_rxCount;
        float m_rttMin;
        float m_rttAvg;
        float m_rttMax;
        float m_rttMDev;

        static std::string extractString( const std::string& rawData, const std::string& before, const std::string& after );

        static int extractInt( const std::string& rawData, const std::string& before, const std::string& after );
};