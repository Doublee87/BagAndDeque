/*	type.h
	
	Defines the type to be stored in the data structure.  These macros
	are for convenience to avoid having to search and replace/dup code
	when you want to build a structure of doubles as opposed to ints
	for example.

	NOTE: When you pass a value to any ADT of type TYPE, it is advised to typecast it explicitly to TYPE
*/
#include <float.h>

#ifndef __TYPE_H
#define __TYPE_H

# ifndef TYPE
# define TYPE      double
# define TYPE_SIZE sizeof(double)
/*This is the value used for the sentinel. 
 *DBL_MAX is an in-built constant that denotes the maximum value of a double*/
# define TYPE_SENTINEL_VALUE DBL_MAX 
# endif

#define TYPE1 char

# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
/*Modify this to an epsilon test for better accuracy*/
# define EQ(A, B) ((A) == (B))
# endif


#endif
