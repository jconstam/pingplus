#include <iostream>

#include "ping.hpp"

using namespace std;

int main( int argc, char* argv[ ] ) 
{
    Ping myPing( "127.0.0.1" );
    myPing.Send( );

    return 0;
}