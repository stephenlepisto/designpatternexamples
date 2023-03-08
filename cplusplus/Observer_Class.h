/// @file
/// @brief
/// Implementation for the @ref DesignPatternExamples_cpp::ObserverForDecimal "ObserverForDecimal",
/// @ref DesignPatternExamples_cpp::ObserverForHexaDecimal "ObserverForHexaDecimal",
/// and @ref DesignPatternExamples_cpp::ObserverForBinary "ObserverForBinary"
/// classes used in the @ref observer_pattern "Observer pattern".

#pragma once
#ifndef __OBSERVER_CLASS_H__
#define __OBSERVER_CLASS_H__

// This test requires /Zc:__cplusplus to be specified on the build command line.
#if !defined(__cplusplus) || __cplusplus < 202002L
#error Requires C++ 20 or later to compile!
#endif
#include <format> // Requires C++20

#include <iostream>
#include <string>

#include "helpers/argumentnull_error.h"

#include "ObserverSubject_NumberProducer.h"

namespace DesignPatternExamples_cpp
{

    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in decimal.
    /// </summary>
    class ObserverForDecimal : public IObserverNumberChanged
    {
    private:
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer::shared_ptr_t _numberProducer;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        ObserverForDecimal(INumberProducer::shared_ptr_t numberProducer)
            : _numberProducer(numberProducer)
        {
            if (!numberProducer)
            {
                throw Helpers::argumentnull_error("numberProducer",
                    "The ObserverForDecimal constructor requires a valid INumberProducer object.");
            }
        }

        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in decimal.
        /// </remarks>
        void NumberChanged()
        {
            uint32_t number = _numberProducer->FetchNumber();
            std::cout << std::format("    Decimal    : {0}", number) << std::endl;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in hexadecimal.
    /// </summary>
    class ObserverForHexaDecimal : public IObserverNumberChanged
    {
    private:
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer::shared_ptr_t _numberProducer;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        ObserverForHexaDecimal(INumberProducer::shared_ptr_t numberProducer)
            : _numberProducer(numberProducer)
        {
            if (!numberProducer)
            {
                throw Helpers::argumentnull_error("numberProducer", "The ObserverForHexaDecimal constructor requires a valid INumberProducer object.");
            }
        }


        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in hexadecimal using C++'s std::format to make the conversion.
        /// </remarks>
        void NumberChanged()
        {
            uint32_t number = _numberProducer->FetchNumber();
            std::cout << std::format("    Hexadecimal: {0:#08X}", number) << std::endl;
        }
    };


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in binary.
    /// </summary>
    class ObserverForBinary : public IObserverNumberChanged
    {
    private:
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer::shared_ptr_t _numberProducer;

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        ObserverForBinary(INumberProducer::shared_ptr_t numberProducer)
            : _numberProducer(numberProducer)
        {
            if (!numberProducer)
            {
                throw Helpers::argumentnull_error("numberProducer", "The ObserverForBinary constructor requires a valid INumberProducer object.");
            }
        }


        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in binary, using C++'s std::format() to make the conversion.
        /// </remarks>
        void NumberChanged()
        {
            uint32_t number = _numberProducer->FetchNumber();

            std::cout << std::format("    Binary     : {0:#032b}", number) << std::endl;
        }
    };

} // end namespace

#endif // __OBSERVER_CLASS_H__

