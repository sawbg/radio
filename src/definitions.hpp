/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains declarations of system-independant (universal size) integers
 * and float types, shortened type names for some commonly used types, and
 * enumerations.
 */

#ifndef definitions_H
#define definitions_H

#include <complex>
#include <vector>

#define ENUM signed char
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
 * Defines a type for complex float32's.
 */
typedef std::complex<float32> cfloat32;

/**
 * Defines a type for the filter coefficients.
 */
typedef std::vector<std::vector<float64>> fparams;

/**
 * This namespace contains all the classes, functions, and enumerations used in
 * the application.
 */
namespace radio {
	/**
	 * Describes the age of a filter (from last Pass() or in this Pass())
	 */
	enum Age { OLD, NEW };

	/**
	 * Describes the numerator and denominator of a z-domain transfer function
	 */
	enum Fractional { NUM, DEN };

	/**
	 *
	 */
	enum Argument { FREQ = 1, MODE, PL_TONE };
	
	/**
	 * Describes a form of modulation.
	 */
	enum class ModulationType { DSB_LC, DSB_SC, USB_FILTERED, USB_HILBERT,
		LSB_FILTERED, LSB_HILBERT, FM_NARROW, FM_WIDE };
}

#endif
