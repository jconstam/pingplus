#include <cstdio>
#include <cstring>
#include <iostream>

#include "ping.hpp"

using namespace std;

#define BUFFER_SIZE     ( 128U )

Ping::Ping( const std::string& hostname ): m_hostname( hostname )
{

}

void Ping::Send( )
{
    string result = "";
    string cmd = "ping -q -i 0.2 -c 10 " + m_hostname;

    FILE* pipe = popen( cmd.c_str( ), "r" );
    if( pipe )
    {
        while( !feof( pipe ) )
        {
            char buffer[ BUFFER_SIZE ] = { 0 };
            if( fgets( buffer, BUFFER_SIZE, pipe ) != nullptr )
            {
                result += buffer;
            }
        }
        
        PingData data( result );
    }
}

PingData::PingData( const std::string& rawData )
{
    int txEnd = rawData.find( "packets transmitted" ) - 1U;
    int txStart = rawData.rfind( "\n", txEnd ) + 1U;
    string txCountString = rawData.substr( txStart, txEnd - txStart );
    m_txCount = stoi( txCountString, nullptr );

    int rxEnd = rawData.find( "received" ) - 1U;
    int rxStart = rawData.rfind( ",", rxEnd ) + 2U;
    string rxCountString = rawData.substr( rxStart, rxEnd - rxStart );
    m_rxCount = stoi( rxCountString, nullptr );

    int rttStart = rawData.find( "rtt" ) + strlen( "rtt min/avg/max/mdev = " );
    int rttEnd = rawData.find( "\n", rttStart ) - 3U;
    string rttStats = rawData.substr( rttStart, rttEnd - rttStart );

    sscanf( rttStats.c_str( ), "%f/%f/%f/%f", &( m_rttMin ), &( m_rttAvg ), &( m_rttMax ), &( m_rttMDev ) );

    cout << "TX: " << m_txCount << endl;
    cout << "RX: " << m_rxCount << endl;
    cout << "Min: " << m_rttMin << " Avg: " << m_rttAvg << " Max: " << m_rttMax << " MDev: " << m_rttMDev << endl;
}