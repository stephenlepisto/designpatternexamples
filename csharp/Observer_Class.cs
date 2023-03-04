/// @file
/// @brief
/// The @ref DesignPatternExamples_csharp.ObserverForDecimal "ObserverForDecimal",
/// @ref DesignPatternExamples_csharp.ObserverForHexaDecimal "ObserverForHexaDecimal",
/// and @ref DesignPatternExamples_csharp.ObserverForBinary "ObserverForBinary"
/// classes used in the @ref observer_pattern "Observer pattern".

using System;
using System.Text;

namespace DesignPatternExamples_csharp
{
    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in decimal.
    /// </summary>
    public class ObserverForDecimal : IObserverNumberChanged
    {
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        private INumberProducer _numberProducer;


        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        public ObserverForDecimal(INumberProducer numberProducer)
        {
            if (numberProducer == null)
            {
                throw new ArgumentNullException("numberProducer", "The ObserverForDecimal constructor requires a valid INumberProducer object.");
            }
            _numberProducer = numberProducer;
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
        void IObserverNumberChanged.NumberChanged()
        {
            uint number = _numberProducer.FetchNumber();
            Console.WriteLine("    Decimal    : {0}", number);
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in hexadecimal.
    /// </summary>
    public class ObserverForHexaDecimal : IObserverNumberChanged
    {
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer _numberProducer;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        public ObserverForHexaDecimal(INumberProducer numberProducer)
        {
            if (numberProducer == null)
            {
                throw new ArgumentNullException("numberProducer", "The ObserverForHexaDecimal constructor requires a valid INumberProducer object.");
            }
            _numberProducer = numberProducer;
        }


        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in hexadecimal using C#'s number formatting.
        /// </remarks>
        void IObserverNumberChanged.NumberChanged()
        {
            uint number = _numberProducer.FetchNumber();
            Console.WriteLine("    Hexadecimal: 0x{0:X8}", number);
        }
    }


    //########################################################################
    //########################################################################


    /// <summary>
    /// Represents an observer that prints out the current number from the
    /// Subject in binary.
    /// </summary>
    public class ObserverForBinary : IObserverNumberChanged
    {
        /// <summary>
        /// The number producer from which to get the current number.
        /// </summary>
        INumberProducer _numberProducer;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="numberProducer">A number producer as represented by
        /// an INumberProducer interface.  Cannot be null.</param>
        public ObserverForBinary(INumberProducer numberProducer)
        {
            if (numberProducer == null)
            {
                throw new ArgumentNullException("numberProducer", "The ObserverForBinary constructor requires a valid INumberProducer object.");
            }
            _numberProducer = numberProducer;
        }


        /// <summary>
        /// Called whenever the number is changed in the number producer.
        /// This observer instance must first be subscribed to the number
        /// producer to receive calls on this method.
        /// </summary>
        /// <remarks>
        /// In this example, this notification handler prints out the current
        /// number in binary.  The value needs to be manually converted to
        /// binary as C# does not provide this support.
        /// </remarks>
        void IObserverNumberChanged.NumberChanged()
        {
            uint number = _numberProducer.FetchNumber();
            StringBuilder output = new StringBuilder();
            uint mask = (uint)1 << 31;

            for (uint index = 0; index < 32; ++index)
            {
                if ((number & mask) != 0)
                {
                    output.Append("1");
                }
                else
                {
                    output.Append("0");
                }
                mask >>= 1;
            }

            Console.WriteLine("    Binary     : {0}", output);
        }
    }
}
