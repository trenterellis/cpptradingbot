/////////////////////////////////////////////////////////////////////////////////
// trading bot coding exercise (c) Trent Ellis 2021
/////////////////////////////////////////////////////////////////////////////////
// AlgoOrders - Store for orders associated with a trading algorithm

#pragma once

#include <map>
#include <vector>
#include <memory>

#include "DvfSimulator.h"

// Class representing a single order
class AlgoOrder
{
public:
    using OrderID = uint32_t;
    
    // Constructor
    AlgoOrder( const OrderID orderID,
               const double amount,
               const double price );

    //! Destructor
    virtual ~AlgoOrder() noexcept;

    bool isBid() const noexcept;

    const double amount() const noexcept;
    const double price() const noexcept;
    const OrderID orderID() const noexcept;

    // Fill the order
    std::pair< double, double> fill() noexcept;
    
protected:
    
private:

    OrderID orderID_;
    double amount_;
    double price_;
    
    
    //! Default constructor
    AlgoOrder() = delete;

    //! Copy constructor
    AlgoOrder(const AlgoOrder &other) = delete;

    //! Move constructor
    AlgoOrder(AlgoOrder &&other) noexcept = delete;

    //! Copy assignment operator
    AlgoOrder& operator=(const AlgoOrder &other) = delete;

    //! Move assignment operator
    AlgoOrder& operator=(AlgoOrder &&other) noexcept = delete;

};

// Store of algoOrders associated with trading algo    
class AlgoOrders
{
public:
    using OrderID = uint32_t;

    //! Default constructor
    AlgoOrders();

    //! Destructor
    virtual ~AlgoOrders() noexcept;

    void addOrder( OrderID orderID,
              double amount,
              double price );
    
    const std::vector< std::shared_ptr< AlgoOrder > >& allOrders() const;

    void clear();

    std::pair< double, double > processFills( IDvfSimulator::OrderBook& book ) noexcept;
    
protected:

    void remove_( OrderID orderID ) noexcept;
    
private:

    std::multimap< double, std::shared_ptr< AlgoOrder > > bidsByPrice_;
    std::multimap< double, std::shared_ptr< AlgoOrder > > offersByPrice_;
    std::vector< std::shared_ptr< AlgoOrder > > allOrders_;
    
    //! Copy constructor
    AlgoOrders(const AlgoOrders &other) = delete;

    //! Move constructor
    AlgoOrders(AlgoOrders &&other) noexcept = delete;

    //! Copy assignment operator
    AlgoOrders& operator=(const AlgoOrders &other) = delete;

    //! Move assignment operator
    AlgoOrders& operator=(AlgoOrders &&other) noexcept = delete;

};
