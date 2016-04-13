/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains declarations of system-independant (universal size) integers
 * and float types, shortened type names for some commonly used types, and
 * enumerations.
 */

#ifndef definitions_H
#define definitions_H

#include <complex>
#include <vector>

/**
 * The type used for the enumerations.
 */
#define ENUM signed char

/**
 * A generic error constant.
 */
#define ERROR -1

typedef unsigned char byte;
typedef unsigned char uint8;
typedef signed char sint8;

typedef unsigned short uint16;
typedef signed short sint16;

typedef unsigned int uint32;
typedef signed int sint32;

typedef unsigned long long uint64;
typedef signed long long sint64;

typedef float float32;
typedef double float64;

/**
 * Complex float32's.
 */
typedef std::complex<float32> cfloat32;

/**
 * Defines a type for the filter coefficients.
 */
typedef std::vector<std::vector<float64>> fparams;

/**
 * This namespace contains all the classes, functions, and enumerations
 * used in the application.
 */
namespace radio {
	/**
	 * Describes the age of a filter (from last Pass() or in this Pass()). Not
	 * currently used.
	 */
	enum Age { OLD, NEW };

	/**
	 * Describes the numerator and denominator of a z-domain transfer function
	 */
	enum Fractional { NUM, DEN };

	/**
	 * Describes the arguments in argv. Never actually used.
	 */
	enum Argument { FREQ = 1, MODE, PL_TONE };
	
	/**
	 * Describes a form of modulation.
	 */
	enum class ModulationType {
		DSB_LC, DSB_SC,
		USB_FILTERED,
		USB_HILBERT,
		LSB_FILTERED,
		LSB_HILBERT,
		FM_NARROW,
		FM_WIDE
	};
}

#endif

// Doxygen descriptions for non-code files

/**
 * @file makefile
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains recipes to compile the main program and the tests programs as
 * well as making documentation and counting total lines of code in src/
 */

/**
 * @file doxygen.config
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains doxygen configuration
 */

/**
 * @file bbftest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs test on the baseband filter.
 */

/**
 * @file iqtest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs test on the makeIQ() function.
 */

/**
 * @file modtest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs test on the modulation of a simple sinusoid.
 */

/**
 * @file msintest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs test involving the generation of many sinusoids.
 */

/**
 * @file lsbftest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs test on the LSB filter.
 */

/**
 * @file pltest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs test on the PlTone class.
 */

/**
 * @file radio
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief The main program's script. Call this script to modulate audio!
 */

/**
 * @file sintest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs a test on the Sinusoid class.
 */

/**
 * @file usbftest
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Runs a test on the USB filter.
 */
