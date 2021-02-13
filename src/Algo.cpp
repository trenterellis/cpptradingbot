/////////////////////////////////////////////////////////////////////////////////
// trading bot coding exercise (c) Trent Ellis 2021
/////////////////////////////////////////////////////////////////////////////////

#include "Algo.h"
#include "AlgoOrders.h"

// Algo constructor
Algo::Algo( IDvfSimulator *sim,
            const std::pair< double, double>& initialBalances,
           const std::pair< const std::string, const std::string >& currencies )
    : sim_( sim ),
      balances_( initialBalances ),
      currencies_( currencies )
{
    orders_ = std::make_unique< AlgoOrders >();
}

Algo::~Algo() noexcept
{
    // Cancel unfilled orders
    cancelOrders_();
}

// The main body of the algo. Gets updated order book,
// deals with fills and updates balances then cancels
// unfilled orders and enters new orders based on best bid and ask.
void Algo::run() noexcept
{
    // Get current order book
    auto book = sim_->GetOrderBook();

    // Deal with fills
    auto balanceChanges = orders_->processFills( book );

    // Update balances from changes
    balances_.first += balanceChanges.first;
    balances_.second += balanceChanges.second;
    
    // Cancel unfilled orders
    cancelOrders_();
    
    // Defensive market making. Enter orders just below best bid, and just above best offer
    // based on current book
    auto bestPrices = bestBidOffer_( book );

    auto bestBid = bestPrices.first;
    auto bestOffer = bestPrices.second;

    const double defaultVolume = 1;
    const auto depth = 0.06;

    for( double i = 0.01; i < depth; i+=0.01 )
    {
        double bidPrice = ( 0.95 + i ) * bestBid;
        double offerPrice = ( 1.05 - i ) * bestOffer;

        auto placedBid = sim_->PlaceOrder( bidPrice, defaultVolume );

        if( placedBid )
        {
            orders_->addOrder( placedBid.value(), defaultVolume, bidPrice );
        }
        else
        {
            std::cout << "Failed to place bid order : " << defaultVolume << " @ " << bidPrice << std::endl;
        }
        
        auto placedOffer = sim_->PlaceOrder( offerPrice, defaultVolume * -1 );

        if( placedOffer )
        {
            orders_->addOrder( placedOffer.value(), defaultVolume * -1, offerPrice );
        }
        else
        {
            std::cout << "Failed to place offer order : " << defaultVolume << " @ " << offerPrice << std::endl;
        }
               
    }
    
}

// Dump out the current balances.
void Algo::dumpBalances() const noexcept
{
    std::cout << "****************" << std::endl
              << "Current balances : "
              << balances_.first << ' ' << currencies_.first << ' '
              << balances_.second << ' ' << currencies_.second << std::endl
              << "****************" << std::endl;
}

// Check balances are still positive
bool Algo::positiveBalances() const noexcept
{
    return balances_.first > 0.0
        && balances_.second > 0.0;
}

// Work out best bid and offer based upon the current order book
std::pair< double , double > Algo::bestBidOffer_( IDvfSimulator::OrderBook& book ) const noexcept
{
    double bestBid = 0;
    double bestOffer = 0;    for( auto &entry : book )
    {
        auto &price = entry.first;
        auto &volume = entry.second;
        
        if( volume > 0 )
        {
            if( price > bestBid )
            {
                bestBid = price;
            }
        }
        else
        {
            if( bestOffer == 0 || price < bestOffer )
            {
                bestOffer = price;
            }
        }
    }

    return std::make_pair( bestBid, bestOffer );
    
}

// Cancel all orders from the exchange
void Algo::cancelOrders_() noexcept
{
    auto toCancel = orders_->allOrders();

    for( auto &order : toCancel )
    {
        sim_->CancelOrder( order->orderID() );
    }

    orders_->clear();
}

