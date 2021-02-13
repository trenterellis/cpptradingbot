/////////////////////////////////////////////////////////////////////////////////
// trading bot coding exercise (c) Trent Ellis 2021
/////////////////////////////////////////////////////////////////////////////////
// Algo - Base class for trading / market making algorithms

#pragma once

#include "DvfSimulator.h"
#include <memory>

class AlgoOrders;

class Algo
{
public:
    // Constructor
    Algo( IDvfSimulator *sim,
          const std::pair< double, double >& initialBalances,
          const std::pair< const std::string, const std::string >& currencies );

    // Destructor
    virtual ~Algo() noexcept;

    // The main body of the algo. Gets updated order book,
    // deals with fills and updates balances then cancels
    // unfilled orders and enters new orders based on best bid and ask.
    void run() noexcept;

    // Dump out the current balances.
    void dumpBalances() const noexcept;

    // Check balances are still positive
   bool positiveBalances() const noexcept;
    
protected:

    // Work out best bid and offer based upon the current order book
    std::pair< double, double > bestBidOffer_( IDvfSimulator::OrderBook& book ) const noexcept;

    // Cancel all orders from the exchange
    void cancelOrders_() noexcept;

    IDvfSimulator* sim_;
    
private:

    // Currency pair names that we are trading
    const std::pair< const std::string, const std::string > currencies_;

    // balances of each currency 
    std::pair< double, double > balances_;

    // Store of orders belonging to this algo
    std::unique_ptr< AlgoOrders > orders_;

    // Deleted default ctrs / operators
    // Default constructor
    Algo() = delete;

    //! Copy constructor
    Algo(const Algo &other) = delete;

    //! Move constructor
    Algo(Algo &&other) noexcept = delete;

    //! Copy assignment operator
    Algo& operator=(const Algo &other) = delete;

    //! Move assignment operator
    Algo& operator=(Algo &&other) noexcept = delete;

   
};
