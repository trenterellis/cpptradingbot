/////////////////////////////////////////////////////////////////////////////////
// trading bot coding exercise (c) Trent Ellis 2021
/////////////////////////////////////////////////////////////////////////////////

#include "AlgoOrders.h"

// AlgoOrders methods

AlgoOrders::AlgoOrders()
    : bidsByPrice_(),
      offersByPrice_()
{
}

AlgoOrders::~AlgoOrders() noexcept
{
}

// Add an order to the algoOrders store.
void AlgoOrders::addOrder( OrderID orderID,
                      double amount,
                      double price )
{
    auto order = std::make_shared< AlgoOrder >( orderID, amount, price );
    
    if( amount > 0 )
    {
        bidsByPrice_.insert( std::make_pair( price, order ));
    }
    else
    {
        offersByPrice_.insert( std::make_pair( price, order ));
    }

    allOrders_.push_back( order );
}

// Return a list of all orders by OrderID
const std::vector< std::shared_ptr< AlgoOrder > >& AlgoOrders::allOrders() const
{
    return allOrders_;
}

// Clear all orders from the store
void AlgoOrders::clear()
{
    bidsByPrice_.clear();
    offersByPrice_.clear();
    allOrders_.clear();
}

// Calculate order fills from the current order book state.  This is necessary as the
// exchange does not publish a list of fills, nor the best bid/offer used to generate fills.
// Returns a pair of balance updates calculated from the accumulated fills.
std::pair< double, double > AlgoOrders::processFills( IDvfSimulator::OrderBook& book ) noexcept
{
    std::pair< double, double > balanceUpdates = std::make_pair( 0, 0 );

    std::set< OrderID > unfilledOrders;

    for( auto &bookItem : book )
    {
        if( bookItem.second > 0 ) // bid
        {
            auto found = bidsByPrice_.find( bookItem.first );
            
            if( found != bidsByPrice_.end() )
            {
                if( found->second->amount() == bookItem.second )  // amount matches
                {
                    unfilledOrders.insert( found->second->orderID() );  // add order to unfilled list
                }
                
            }
        }
        else
        {
            // offer
            auto found = offersByPrice_.find( bookItem.first );
            
            if( found != offersByPrice_.end() )
            {
                if( found->second->amount() == bookItem.second )  // amount matches
                {
                    unfilledOrders.insert( found->second->orderID() );  // add order to unfilled list
                }
                
            }
        }
    }

    // For each order, if it is NOT unfilled, then update balances and remove it.

    std::vector< OrderID > filledOrders;
    
    for( auto &order : allOrders_ )
    {
        auto found = unfilledOrders.find( order->orderID() );
        
        if( found == unfilledOrders.end() )
        {
            // This order has filled.
            auto orderBalances = order->fill();
            balanceUpdates.first += orderBalances.first;
            balanceUpdates.second += orderBalances.second;

            filledOrders.push_back( order->orderID() );
         }
    }

    // Finally tidy up by removing filled orders.
    for( auto &orderID : filledOrders )
    {
        remove_( orderID );
    }
    
    return balanceUpdates;
    
}

void AlgoOrders::remove_( OrderID orderID ) noexcept
{
    // Currently does nothing as this Algo clears all unfilled
    // orders from the exchange after each update.
    
}

// AlgoOrder methods
AlgoOrder::AlgoOrder( const OrderID orderID,
                      const double amount,
                      const double price )
    : orderID_( orderID ),
      amount_( amount ),
      price_( price )
{
}

AlgoOrder::~AlgoOrder() noexcept
{
}

bool AlgoOrder::isBid() const noexcept
{
    return amount_ > 0;
}

const double AlgoOrder::amount() const noexcept
{
    return amount_;
}

const double AlgoOrder::price() const noexcept
{
    return price_;
}

const AlgoOrder::OrderID AlgoOrder::orderID() const noexcept
{
    return orderID_;
}

// Calculate the balance updates and return them when this order is filled.
std::pair< double, double > AlgoOrder::fill() noexcept
{
    double first = 0;
    double second = 0;

    first = amount_;
    second = amount_ * price_ * -1;

    return std::make_pair( first, second );
    
}

