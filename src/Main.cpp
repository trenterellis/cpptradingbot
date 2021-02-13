/////////////////////////////////////////////////////////////////////////////////
// trading bot coding exercise (c) Trent Ellis 2021
/////////////////////////////////////////////////////////////////////////////////
// main routine for running a trading bot.

#include "DvfSimulator.h"
#include "Algo.h"

#include <thread>

int main()
{
    auto* sim = DvfSimulator::Create();

    // Set up initial balances and currencies
    std::pair< double, double > balances = std::make_pair( 10, 2000 );
    
    std::pair< const std::string, const std::string > currencies = std::make_pair( "ETH", "USD" );
    
    Algo algo( sim, balances, currencies );

    // After every 6 loops (30 secs) dump balances
    int loopCount = 0;
    
    while( true )
    {
        auto ob = sim->GetOrderBook();

        algo.run();

        if( ++loopCount == 6 )
        {
            algo.dumpBalances();
            loopCount = 0;
        }
        
        // Wait for 5 seconds
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        
    }

    return true;
}

