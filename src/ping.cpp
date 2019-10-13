#include <thread>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "ping.hpp"

using namespace std;

#define BUFFER_SIZE     ( 128U )

static void pingThread( const string& hostname );

Ping::Ping( const string& hostname ): m_hostname( hostname )
{

}

void Ping::Send( )
{
    thread doPing( &( pingThread ), m_hostname );
    doPing.join( );
}

static void pingThread( const string& hostname )
{
    string result = "";
    string cmd = "ping -q -i 0.2 -c 1 " + hostname;

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
        data.PrintStats( );
    }
}

PingData::PingData( const string& rawData )
{
    m_txCount = extractInt( rawData, "\n", "packets transmitted" );
    m_rxCount = extractInt( rawData, ",", "received" );
    sscanf( extractString( rawData, "rtt min/avg/max/mdev =", " ms" ).c_str( ), "%f/%f/%f/%f", &( m_rttMin ), &( m_rttAvg ), &( m_rttMax ), &( m_rttMDev ) );
}

void PingData::PrintStats( void )
{
    cout << "Sent: " << m_txCount << " - Received: " << m_rxCount << endl;
    cout << "Min: " << m_rttMin << " - Avg: " << m_rttAvg << " - Max: " << m_rttMax << " - MDev: " << m_rttMDev << endl;
}

string PingData::extractString( const string& rawData, const string& before, const string& after )
{
    int end = rawData.find( after );
    int start = rawData.rfind( before, end ) + strlen( before.c_str( ) );
    return rawData.substr( start, end - start );    
}

int PingData::extractInt( const std::string& rawData, const std::string& before, const std::string& after )
{
    return stoi( extractString( rawData, before, after ), nullptr );
}
