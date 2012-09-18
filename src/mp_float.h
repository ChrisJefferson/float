/****************************************************************************
**
*W  mp_float.h                    GAP source                Laurent Bartholdi
**
*H  @(#)$Id$
**
*Y  Copyright (C) 2008 Laurent Bartholdi
**
**  This file declares the functions for the floating point package
*/
#ifdef BANNER_MP_FLOAT_H
static const char *Revision_mp_float_h =
   "@(#)$Id$";
#endif

#ifndef USE_GMP
#error Float requires a GAP version with built-in GMP support
#endif

Obj MPZ_LONGINT (Obj obj);
Obj INT_mpz(mpz_ptr z);
mpz_ptr mpz_MPZ (Obj obj);

#define VAL_MACFLOAT(obj) (*(Double *)ADDR_OBJ(obj))
#define IS_MACFLOAT(obj) (TNUM_OBJ(obj) == T_MACFLOAT)

#define TEST_IS_INTOBJ(mp_name,obj)					\
  while (!IS_INTOBJ(obj))						\
    obj = ErrorReturnObj(mp_name ": expected a small integer, not a %s", \
			 (Int)(InfoBags[TNUM_OBJ(obj)].name),0,		\
			 "You can return an integer to continue");

extern Obj FLOAT_INFINITY_STRING,
  FLOAT_EMPTYSET_STRING,
  FLOAT_REAL_STRING,
  FLOAT_I_STRING;

/****************************************************************
 * mpfr
 ****************************************************************/
#ifdef WITH_MPFR
#include <mpfr.h>

/****************************************************************
 * mpfr's are stored as follows:
 * +-----------+----------------------------------+-------------+
 * | TYPE_MPFR |           __mpfr_struct          | mp_limb_t[] |
 * |           | precision exponent sign mantissa |             |
 * +-----------+----------------------------------+-------------+
 *                                          \_______^
 ****************************************************************/
#define MPFR_OBJ(obj) ((mpfr_ptr) (ADDR_OBJ(obj)+1))
inline Obj NEW_MPFR (mp_prec_t prec);
inline mpfr_ptr GET_MPFR(Obj obj);

int PRINT_MPFR(char *s, mp_exp_t *exp, int digits, mpfr_ptr f, mpfr_rnd_t rnd);

int InitMPFRKernel (void);
int InitMPFRLibrary (void);
#endif

/****************************************************************
 * mpfi
 ****************************************************************/
#ifdef WITH_MPFI
#include <mpfi.h>

/****************************************************************
 * mpfi's are stored as follows:
 * +-----------+-----------------------------------------+---------------------+
 * | TYPE_MPFI |             __mpfi_struct               |    __mp_limb_t[]    |
 * |           | __mpfr_struct left         right        | limbl ... limbr ... |
 * |           | prec exp sign mant   prec exp sign mant |                     |
 * +-----------+-----------------------------------------+---------------------+
 *                               \____________________\____^         ^
 *                                                     \____________/
 * it is assumed that the left and right mpfr's are allocated with the
 * same precision
 ****************************************************************/
#define MPFI_OBJ(obj) ((mpfi_ptr) (ADDR_OBJ(obj)+1))

int InitMPFIKernel (void);
int InitMPFILibrary (void);
#endif

/****************************************************************
 * mpc
 ****************************************************************/
#ifdef WITH_MPC
#include <mpc.h>

int InitMPCKernel (void);
int InitMPCLibrary (void);
#endif

/****************************************************************
 * fplll
 ****************************************************************/
#ifdef WITH_FPLLL
int InitFPLLLKernel (void);
int InitFPLLLLibrary (void);
#endif

/****************************************************************
 * mpd
 ****************************************************************/
#ifdef WITH_MPD
int InitMPDKernel (void);
int InitMPDLibrary (void);
#endif

/****************************************************************************
**
*E  mp_float.h  . . . . . . . . . . . . . . . . . . . . . . . . . . ends here
*/
