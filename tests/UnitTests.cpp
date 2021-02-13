/////////////////////////////////////////////////////////////////////////////////
// trading bot coding exercise (c) Trent Ellis 2021
/////////////////////////////////////////////////////////////////////////////////
// A unit tests file.

// NOTE I would use Boost::Test normally, but I don't want
// to assume that Boost is available on every build environment...

// Many more tests should be written if not under time constraints...

#include <iostream>

#define private public
#include <AlgoOrders.h>
#include "DvfSimulator.h"

using namespace std;

int test_Fills()
{

    {
        IDvfSimulator::OrderBook book = {
            {
                20, 2 
            }
            ,
            {
                19, 3
            }
            ,
            {
                18, 4
            }
            ,
            {
                22, -2
            },
            {
                23, -3
            }
            ,
            {
                24, -4
            }
        };

        AlgoOrders orders;

        orders.addOrder( 10001, 4, 21 );  // filled
        orders.addOrder( 10002, 2, 20 );  // unfilled
        orders.addOrder( 10003, -1, 22 ); //filled
        orders.addOrder( 10004, -4, 24 ); // unfilled
        

        auto balances = orders.processFills( book );
        std::cout << "Filled ETH are : " << balances.first  << std::endl;
        std::cout << "Filled USD are : " << balances.second << std::endl;

        if( balances.first == 3 && balances.second == -62 )
        {
            std::cout << "PASSED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
        }
        
    }
    
    return 0;
    
}


int test_AlgoOrders()
{
    {
        // Buy 12ETH at 5.5
        AlgoOrder testOrder1( 1, 12, 5.5 );

        auto fill1 = testOrder1.fill();

        std::cout << "Filled ETH are : " << fill1.first  << std::endl;
        std::cout << "Filled USD are : " << fill1.second << std::endl;

        if( fill1.first == 12 && fill1.second == -66 )
        {
           std::cout << "PASSED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
        }
        
    }
    
    {
        // Sell 15ETH at 4.5
        AlgoOrder testOrder2( 1, -15, 4.5 );

        auto fill2 = testOrder2.fill();

        std::cout << "Filled ETH are : " << fill2.first  << std::endl;
        std::cout << "Filled USD are : " << fill2.second << std::endl;

        if( fill2.first == -15 && fill2.second == (15 * 4.5) )
        {
           std::cout << "PASSED" << std::endl;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
        }
        
    }
      
    // {
        
    //     AlgoOrders testOrders;

    //     testOrders.addOrder( 1, 100, 10 );   // 100 @ 10      -1000 USD  100 ETH  
    //     testOrders.addOrder( 2, 1100, 11 );  // 1100 @ 11     -12100 USD 1100 ETH FILLED
    //     testOrders.addOrder( 3, 50, 11  );   // 50 @ 11       -550 USD   50 ETH   FILLED
    //     testOrders.addOrder( 4, 1200, 12 );  // 1200 @ 12     -14400 USD 1200 ETH FILLED

    //     auto filled = testOrders.fillBids( 11 );
    
    //     std::cout << "Filled USD are : " << filled.first << std::endl;
    //     std::cout << "Filled ETH are : " << filled.second << std::endl;

    //     if( filled.first == ( (1100 * 11) + (50 * 11 ) + (1200 * 12))    // 27050
    //         && filled.second == ( 1100 + 50 + 1200 )    // 2350
    //         && testOrders.bidsByPrice_.size() == 1 )
    //     {
    //         std::cout << "PASSED" << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "FAILED" << std::endl;
    //     }
           
        
    // }
    
    // {
        
    //     AlgoOrders testOrders;

    //     testOrders.addOrder( 1, 100, 10 );   // 100 @ 10      -1000 USD  100 ETH
    //     testOrders.addOrder( 2, 1100, 11 );  // 1100 @ 11     -12100 USD 1100 ETH
    //     testOrders.addOrder( 3, 50, 11  );   // 50 @ 11       -550 USD   50 ETH  
    //     testOrders.addOrder( 4, 1200, 12 );  // 1200 @ 12     -14400 USD 1200 ETH 

    //     auto filled = testOrders.fillBids( 14 );
    
    //     std::cout << "Filled USD are : " << filled.first << std::endl;
    //     std::cout << "Filled ETH are : " << filled.second << std::endl;

    //     if( filled.first == 0 && filled.second == 0 && testOrders.bidsByPrice_.size() == 4 )
    //     {
    //         std::cout << "PASSED" << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "FAILED" << std::endl;
    //     }
           
        
    // }

    // {
        
    //     AlgoOrders testOrders;

    //     testOrders.addOrder( 1, -100, 10 );    // 100 @ 10      -1000 USD  100 ETH  FILLED
    //     testOrders.addOrder( 2, -1100, 11 );   // 1100 @ 11     -12100 USD 1100 ETH FILLED
    //     testOrders.addOrder( 3, -50, 11  );    // 50 @ 11       -550 USD   50 ETH   FILLED
    //     testOrders.addOrder( 4, -1200, 12 );   // 1200 @ 12     -14400 USD 1200 ETH 

    //     auto filled = testOrders.fillOffers( 11 );
        
    //     std::cout << "Filled USD are : " << filled.first << std::endl;
    //     std::cout << "Filled ETH are : " << filled.second << std::endl;
    
    //     if( filled.first == ((100 * 10) + (1100 * 11 ) + (50 * 11))  // 13650
    //         && filled.second == (100 + 1100 + 50)                    // 1250
    //         && testOrders.offersByPrice_.size() == 1 )
    //     {
    //         std::cout << "PASSED" << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "FAILED" << std::endl;
    //     }
    // }
    
    // {
        
    //     AlgoOrders testOrders;

    //     testOrders.addOrder( 1, -100, 10 );   // 100 @ 10      -1000 USD  100 ETH  
    //     testOrders.addOrder( 2, -1100, 11 );  // 1100 @ 11     -12100 USD 1100 ETH 
    //     testOrders.addOrder( 3, -50, 11  );   // 50 @ 11       -550 USD   50 ETH   
    //     testOrders.addOrder( 4, -1200, 12 );  // 1200 @ 12     -14400 USD 1200 ETH 

    //     auto filled = testOrders.fillOffers( 9 );
    
    //     std::cout << "Filled USD are : " << filled.first << std::endl;
    //     std::cout << "Filled ETH are : " << filled.second << std::endl;
 
    //     if( filled.first == 0 &&
    //         filled.second == 0 &&
    //         testOrders.offersByPrice_.size() == 4 )
    //     {
    //         std::cout << "PASSED" << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "FAILED" << std::endl;
    //     }
    // }
             
    return 0;
}


int main()
{
    test_AlgoOrders();

    test_Fills();
    
    return 0;
    
}


