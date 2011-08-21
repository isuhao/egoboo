#pragma once

//********************************************************************************************
//*
//*    This file is part of Egoboo.
//*
//*    Egoboo is free software: you can redistribute it and/or modify it
//*    under the terms of the GNU General Public License as published by
//*    the Free Software Foundation, either version 3 of the License, or
//*    (at your option) any later version.
//*
//*    Egoboo is distributed in the hope that it will be useful, but
//*    WITHOUT ANY WARRANTY; without even the implied warranty of
//*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*    General Public License for more details.
//*
//*    You should have received a copy of the GNU General Public License
//*    along with Egoboo.  If not, see <http://www.gnu.org/licenses/>.
//*
//********************************************************************************************

/// @file egolib_typedef.h
/// @details some basic types that are used throughout the game code.

#include <assert.h>

#include <SDL/SDL.h>

// this include must be the absolute last include
#include "egolib_config.h"

// this include must be the absolute last include
#include "../egolib/mem.h"

#if defined(__cplusplus)
extern "C"
{
#endif

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

    struct s_irect;
    typedef struct s_irect irect_t;

    struct s_frect;
    typedef struct s_frect frect_t;

    struct s_ego_irect;
    typedef struct s_ego_irect ego_irect_t;

    struct s_ego_frect;
    typedef struct s_ego_frect ego_frect_t;

    struct s_pair;
    typedef struct s_pair IPair;

    struct s_range;
    typedef struct s_range FRange;

//--------------------------------------------------------------------------------------------
// portable definition of assert. the c++ version can be activated below.

#   define C_EGOBOO_ASSERT(X) assert(X)

//--------------------------------------------------------------------------------------------
// a replacement for memset()
#    if !defined(BLANK_STRUCT)
#       define BLANK_STRUCT(XX)  memset( &(XX), 0, sizeof(XX) );
#    endif

#    if !defined(BLANK_STRUCT_PTR)
#       define BLANK_STRUCT_PTR(XX)  memset( XX, 0, sizeof( *(XX) ) );
#    endif

#    if !defined(BLANK_ARY)
#       define BLANK_ARY(XX)  memset( XX, 0, sizeof( XX ) );
#    endif

//--------------------------------------------------------------------------------------------
// BOOLEAN

    enum e_bool
    {
        btrue  = ( 1 == 1 ),
        bfalse = ( !btrue )
    };

    // this typedef must be after the enum definition or gcc has a fit
    typedef enum e_bool bool_t;

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

/// special return values
    enum e_egolib_rv
    {
        rv_error   = -1,
        rv_fail    = bfalse,
        rv_success = btrue
    };

    // this typedef must be after the enum definition or gcc has a fit
    typedef enum e_egolib_rv egolib_rv;

//--------------------------------------------------------------------------------------------
// 24.8 fixed point types

    typedef Uint32 UFP8_T;
    typedef Sint32 SFP8_T;

    /// fast version of V1 / 256
#   define UFP8_TO_UINT(V1)   ( ((unsigned)(V1)) >> 8 )
    /// signed version of V1 / 256
#   define SFP8_TO_SINT(V1)   ( (V1) < 0 ? -((signed)UFP8_TO_UINT(-V1)) : (signed)UFP8_TO_UINT(V1) )

    /// fast version of V1 / 256
#   define UINT_TO_UFP8(V1)   ( ((unsigned)(V1)) << 8 )
    /// signed version of V1 / 256
#   define SINT_TO_SFP8(V1)   ( (V1) < 0 ? -((signed)UINT_TO_UFP8(-V1)) : (signed)UINT_TO_UFP8(V1) )

    /// version of V1 / 256.0f
#   define FP8_TO_FLOAT(V1)   ( (float)(V1) * INV_0100 )
    /// version of V1 * 256.0f
#   define FLOAT_TO_FP8(V1)   ( (Uint32)((V1) * (float)(0x0100) ) )

#   define FP8_MUL(V1, V2)    ( ((V1)*(V2)) >> 8 )               ///< this may overflow if V1 or V2 have non-zero bits in their upper 8 bits
#   define FP8_DIV(V1, V2)    ( ((V1)<<8) / (V2) )               ///< this  will fail if V1 has bits in the upper 8 bits

//--------------------------------------------------------------------------------------------
    /// the type for the 16-bit value used to store angles
    typedef Uint16   FACING_T;

    /// the type for the 14-bit value used to store angles
    typedef FACING_T TURN_T;

#   define TO_FACING(X) ((FACING_T)(X))
#   define TO_TURN(X)   ((TURN_T)((TO_FACING(X)>>2) & TRIG_TABLE_MASK))

//--------------------------------------------------------------------------------------------
// 16.16 fixed point types

    typedef Uint32 UFP16_T;
    typedef Sint32 SFP16_T;

#   define FLOAT_TO_FP16( V1 )  ( (Uint32)((V1) * 0x00010000) )
#   define FP16_TO_FLOAT( V1 )  ( (float )((V1) * 0.0000152587890625f ) )

//--------------------------------------------------------------------------------------------
// BIT FIELDS
    typedef Uint32 BIT_FIELD;                              ///< A big string supporting 32 bits

#   define FULL_BIT_FIELD      0x7FFFFFFF                  ///< A bit string where all bits are flagged as 1
#   define EMPTY_BIT_FIELD     0                           ///< A bit string where all bits are flagged as 0
#   define FILL_BIT_FIELD(XX)  (XX) = FULL_BIT_FIELD       ///< Fills up all bits in a bit pattern
#   define RESET_BIT_FIELD(XX) (XX) = EMPTY_BIT_FIELD      ///< Resets all bits in a BIT_FIELD to 0

#    if !defined(SET_BIT)
#       define SET_BIT(XX, YY) (XX) |= (YY)
#    endif

#    if !defined(UNSET_BIT)
#       define UNSET_BIT(XX, YY) (XX) &= ~(YY)
#    endif

#    if !defined(BOOL_TO_BIT)
#       define BOOL_TO_BIT(XX)       ((XX) ? 1 : 0 )
#    endif

#    if !defined(BIT_TO_BOOL)
#       define BIT_TO_BOOL(XX)       ((1 == (XX)) ? btrue : bfalse )
#    endif

#    if !defined(HAS_SOME_BITS)
#       define HAS_SOME_BITS(XX,YY) (0 != ((XX)&(YY)))
#    endif

#    if !defined(HAS_ALL_BITS)
#       define HAS_ALL_BITS(XX,YY)  ((YY) == ((XX)&(YY)))
#    endif

#    if !defined(HAS_NO_BITS)
#       define HAS_NO_BITS(XX,YY)   (0 == ((XX)&(YY)))
#    endif

#    if !defined(MISSING_BITS)
#       define MISSING_BITS(XX,YY)  (HAS_SOME_BITS(XX,YY) && !HAS_ALL_BITS(XX,YY))
#    endif

#   define CLIP_TO_08BITS( V1 )  ( (V1) & 0xFF       )
#   define CLIP_TO_16BITS( V1 )  ( (V1) & 0xFFFF     )
#   define CLIP_TO_24BITS( V1 )  ( (V1) & 0xFFFFFF   )
#   define CLIP_TO_32BITS( V1 )  ( (V1) & 0xFFFFFFFF )

//--------------------------------------------------------------------------------------------
// RECTANGLE
    struct s_irect
    {
        int left;
        int right;
        int top;
        int bottom;
    };

    bool_t irect_point_inside( irect_t * prect, int   ix, int   iy );

    struct s_frect
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    bool_t frect_point_inside( frect_t * prect, float fx, float fy );

    struct s_ego_irect
    {
        int xmin, ymin;
        int xmax, ymax;
    };

    struct s_ego_frect
    {
        float xmin, ymin;
        float xmax, ymax;
    };

//--------------------------------------------------------------------------------------------
// PAIR AND RANGE

    /// Specifies a value between "base" and "base + rand"
    struct s_pair
    {
        int base, rand;
    };

    /// Specifies a value from "from" to "to"
    struct s_range
    {
        float from, to;
    };

    void pair_to_range( IPair pair, FRange * prange );
    void range_to_pair( FRange range, IPair * ppair );

    void ints_to_range( int base, int rand, FRange * prange );
    void floats_to_pair( float vmin, float vmax, IPair * ppair );

//--------------------------------------------------------------------------------------------
// IDSZ
    typedef Uint32 IDSZ;

#    if !defined(MAKE_IDSZ)
#       define MAKE_IDSZ(C0,C1,C2,C3) \
    ((IDSZ)( \
             ((((C0)-'A')&0x1F) << 15) |       \
             ((((C1)-'A')&0x1F) << 10) |       \
             ((((C2)-'A')&0x1F) <<  5) |       \
             ((((C3)-'A')&0x1F) <<  0)         \
           ))
#    endif

#   define IDSZ_NONE            MAKE_IDSZ('N','O','N','E')       ///< [NONE]

    const char * undo_idsz( IDSZ idsz );

//--------------------------------------------------------------------------------------------
// STRING
    typedef char STRING[256];

//--------------------------------------------------------------------------------------------
// EGO_MESSAGE
#   define MESSAGESIZE      90

    typedef char EGO_MESSAGE[MESSAGESIZE];

//--------------------------------------------------------------------------------------------

/// the "base class" of Egoboo profiles
#   define  EGO_PROFILE_STUFF \
    bool_t loaded;                  /** Was the data read in? */ \
    STRING name;                    /** Usually the source filename */ \
    int    request_count;           /** the number of attempted spawnx */ \
    int    create_count;            /** the number of successful spawns */

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
/// The latch used by the input system
    struct s_latch
    {
        float          x;         ///< the x input
        float          y;         ///< the y input
        BIT_FIELD      b;         ///< the button bits
    };
    typedef struct s_latch latch_t;

    void latch_init( latch_t * platch );

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// References

    /// base reference type
    typedef Uint16 REF_T;

//--------------------------------------------------------------------------------------------
// definition of the c-type reference

#   define C_DECLARE_REF( NAME ) typedef REF_T NAME

//--------------------------------------------------------------------------------------------
// reference conversions

// define the c implementation always
#   define C_REF_TO_INT(X) ((REF_T)(X))

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// a simple array

#   define C_DECLARE_T_ARY(TYPE, NAME, COUNT)  TYPE   NAME[COUNT]

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// a simple list structure that tracks free elements

#   define ACCESS_TYPE_NONE

#   define INVALID_UPDATE_GUID ((unsigned)(~((unsigned)0)))

#   define C_DEFINE_LIST_TYPE(TYPE, NAME, COUNT) \
    struct s_c_list__##TYPE__##NAME           \
    {                                         \
        unsigned update_guid;                 \
        int      used_count;                  \
        int      free_count;                  \
        size_t   used_ref[COUNT];             \
        size_t   free_ref[COUNT];             \
        C_DECLARE_T_ARY(TYPE, lst, COUNT);    \
    }

#   define C_DECLARE_LIST_EXTERN(TYPE, NAME, COUNT)   \
    C_DEFINE_LIST_TYPE(TYPE, NAME, COUNT);         \
    TYPE * NAME##_get_ptr( size_t );                  \
    extern struct s_c_list__##TYPE__##NAME NAME

#   define C_INSTANTIATE_LIST_STATIC(TYPE, NAME, COUNT) \
    C_DEFINE_LIST_TYPE(TYPE, NAME, COUNT);        \
    static struct s_c_list__##TYPE__##NAME NAME = {INVALID_UPDATE_GUID, 0, 0}

#   define C_INSTANTIATE_LIST(ACCESS,TYPE,NAME, COUNT) \
    ACCESS struct s_c_list__##TYPE__##NAME NAME = {INVALID_UPDATE_GUID, 0, 0}

#   define C_IMPLEMENT_LIST(TYPE, NAME, COUNT)  \
    TYPE * NAME##_get_ptr( size_t index )   { return (index >= COUNT) ? NULL : NAME.lst + index; }

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// a simple stack structure

#   define C_DEFINE_STACK_TYPE(TYPE, NAME, COUNT) \
    struct s_c_stack__##TYPE__##NAME           \
    {                                          \
        unsigned update_guid;                  \
        int  count;                            \
        C_DECLARE_T_ARY(TYPE, lst, COUNT);     \
    }

#   define C_DECLARE_STACK_EXTERN(TYPE, NAME, COUNT) \
    C_DEFINE_STACK_TYPE(TYPE, NAME, COUNT);       \
    TYPE * NAME##_get_ptr( size_t );                 \
    extern struct s_c_stack__##TYPE__##NAME NAME

#   define C_INSTANTIATE_STACK_STATIC(TYPE, NAME, COUNT) \
    C_DEFINE_STACK_TYPE(TYPE, NAME, COUNT);       \
    static struct s_c_stack__##TYPE__##NAME NAME = {0}

#   define C_INSTANTIATE_STACK(ACCESS, TYPE, NAME, COUNT) \
    ACCESS struct s_c_stack__##TYPE__##NAME NAME = {INVALID_UPDATE_GUID, 0}

#   define C_IMPLEMENT_STACK(TYPE, NAME, COUNT)  \
    TYPE * NAME##_get_ptr( size_t index )   { return (index >= COUNT) ? NULL : NAME.lst + index; }

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

/// a template-like declaration of a dynamically allocated array
#   define DECLARE_DYNAMIC_ARY(ARY_T, ELEM_T) \
    struct s_DYNAMIC_ARY_##ARY_T \
    { \
        size_t alloc; \
        int    top;  \
        ELEM_T * ary; \
    }; \
    typedef struct s_DYNAMIC_ARY_##ARY_T ARY_T##_t; \
    \
    ARY_T##_t * ARY_T##_ctor( ARY_T##_t * pary, size_t sz ); \
    ARY_T##_t * ARY_T##_dtor( ARY_T##_t * pary ); \
    bool_t      ARY_T##_alloc( ARY_T##_t * pary, size_t sz ); \
    bool_t      ARY_T##_free( ARY_T##_t * pary ); \
    void        ARY_T##_clear( ARY_T##_t * pary ); \
    size_t      ARY_T##_get_top( const ARY_T##_t * pary ); \
    size_t      ARY_T##_get_size( const ARY_T##_t * pary ); \
    ELEM_T *    ARY_T##_pop_back( ARY_T##_t * pary ); \
    bool_t      ARY_T##_push_back( ARY_T##_t * pary , ELEM_T val );

#   define DYNAMIC_ARY_INIT_VALS {0,0,NULL}

#   define INSTANTIATE_DYNAMIC_ARY(ARY_T, NAME) ARY_T##_t NAME = DYNAMIC_ARY_INIT_VALS;

#   define IMPLEMENT_DYNAMIC_ARY(ARY_T, ELEM_T) \
    bool_t      ARY_T##_alloc( ARY_T##_t * pary, size_t sz )   { if(NULL == pary) return bfalse; ARY_T##_free( pary ); pary->ary = EGOBOO_NEW_ARY( ELEM_T, sz );  pary->alloc = (NULL == pary->ary) ? 0 : sz; return btrue; } \
    bool_t      ARY_T##_free(ARY_T##_t * pary )                { if(NULL == pary) return bfalse; EGOBOO_DELETE_ARY(pary->ary); pary->alloc = 0; pary->top = 0; return btrue; } \
    ARY_T##_t * ARY_T##_ctor(ARY_T##_t * pary, size_t sz)      { if(NULL == pary) return NULL;   BLANK_STRUCT_PTR( pary ) if( !ARY_T##_alloc(pary, sz) ) return NULL; return pary; } \
    ARY_T##_t * ARY_T##_dtor(ARY_T##_t * pary )                { if(NULL == pary) return NULL;   ARY_T##_free(pary); BLANK_STRUCT_PTR( pary ) return pary; } \
    \
    void   ARY_T##_clear( ARY_T##_t * pary )                   { if(NULL != pary) pary->top = 0; } \
    size_t ARY_T##_get_top( const ARY_T##_t * pary )           { return (NULL == pary->ary) ? 0 : pary->top; } \
    size_t ARY_T##_get_size( const ARY_T##_t * pary )          { return (NULL == pary->ary) ? 0 : pary->alloc; } \
    \
    ELEM_T * ARY_T##_pop_back( ARY_T##_t * pary )              { if( NULL == pary || pary->top < 1 ) return NULL; --pary->top; return &(pary->ary[pary->top]); } \
    bool_t   ARY_T##_push_back( ARY_T##_t * pary, ELEM_T val ) { bool_t retval = bfalse; if( NULL == pary ) return bfalse; if (pary->top >= 0 && (size_t)pary->top < pary->alloc) { pary->ary[pary->top] = val; pary->top++; retval = btrue; } return retval; }

#   define DYNAMIC_ARY_INVALID(ARY) ( (NULL == (ARY)) || (0 == (ARY)->alloc) || ((ARY)->top < 0) || ((size_t)(ARY)->top >= (ARY)->alloc) )

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

/// a template-like declaration of a statically allocated array

#   define DECLARE_STATIC_ARY_TYPE(ARY_T, ELEM_T, SIZE) \
    struct s_STATIC_ARY_##ARY_T \
    { \
        int    count;     \
        ELEM_T ary[SIZE]; \
    }; \
    typedef ELEM_T ARY_T##ELEM_t; \
    typedef struct s_STATIC_ARY_##ARY_T ARY_T##_t

#   define STATIC_ARY_INIT_VALS {0}

#   define DECLARE_EXTERN_STATIC_ARY(ARY_T, NAME)       \
    ARY_T##ELEM_t * ARY_T##_get_ptr( ARY_T##_t *, size_t ); \
    extern ARY_T##_t NAME

#   define INSTANTIATE_STATIC_ARY(ARY_T, NAME) \
    ARY_T##_t NAME = STATIC_ARY_INIT_VALS;

#   define IMPLEMENT_STATIC_ARY(ARY_T, SIZE) \
    ARY_T##ELEM_t * ARY_T##_get_ptr( ARY_T##_t * pary, size_t index ) { if(NULL == pary) return NULL; return ( index >= SIZE ) ? NULL : pary->ary + index; }

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// definitions for the compiler environment

#   define EGOBOO_ASSERT(X) C_EGOBOO_ASSERT(X)
#   define _EGOBOO_ASSERT(X) C_EGOBOO_ASSERT(X)

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// implementation of forward declaration of references

#   define REF_TO_INT(X)  C_REF_TO_INT(X)

#   define DECLARE_T_ARY(TYPE, NAME, COUNT)              C_DECLARE_T_ARY(TYPE, NAME, COUNT)

#   define DECLARE_LIST_EXTERN(TYPE, NAME, COUNT)        C_DECLARE_LIST_EXTERN(TYPE, NAME, COUNT)
#   define INSTANTIATE_LIST_STATIC(TYPE, NAME, COUNT)    C_INSTANTIATE_LIST_STATIC(TYPE, NAME, COUNT)
#   define INSTANTIATE_LIST(ACCESS, TYPE, NAME, COUNT)   C_INSTANTIATE_LIST(ACCESS, TYPE, NAME, COUNT)
#   define IMPLEMENT_LIST(TYPE, NAME, COUNT)             C_IMPLEMENT_LIST(TYPE, NAME, COUNT)

#   define DECLARE_STACK_EXTERN(TYPE, NAME, COUNT)      C_DECLARE_STACK_EXTERN(TYPE, NAME, COUNT)
#   define INSTANTIATE_STACK_STATIC(TYPE, NAME, COUNT)  C_INSTANTIATE_STACK_STATIC(TYPE, NAME, COUNT)
#   define INSTANTIATE_STACK(ACCESS, TYPE, NAME, COUNT) C_INSTANTIATE_STACK(ACCESS, TYPE, NAME, COUNT)
#   define IMPLEMENT_STACK(TYPE, NAME, COUNT)           C_IMPLEMENT_STACK(TYPE, NAME, COUNT)

// use an underscore to force the c implementation
#   define _DECLARE_T_ARY(TYPE, NAME, COUNT)              C_DECLARE_T_ARY(TYPE, NAME, COUNT)

#   define _DECLARE_LIST_EXTERN(TYPE, NAME, COUNT)        C_DECLARE_LIST_EXTERN(TYPE, NAME, COUNT)
#   define _INSTANTIATE_LIST_STATIC(TYPE,NAME, COUNT)     C_INSTANTIATE_LIST_STATIC(TYPE,NAME, COUNT)
#   define _INSTANTIATE_LIST(ACCESS,TYPE,NAME, COUNT)     C_INSTANTIATE_LIST(ACCESS,TYPE,NAME, COUNT)

#   define _DECLARE_STACK_EXTERN(TYPE, NAME, COUNT)      C_DECLARE_STACK_EXTERN(TYPE, NAME, COUNT)
#   define _INSTANTIATE_STACK_STATIC(TYPE, NAME, COUNT)  C_INSTANTIATE_STACK_STATIC(TYPE, NAME, COUNT)
#   define _INSTANTIATE_STACK(ACCESS, TYPE, NAME, COUNT) C_INSTANTIATE_STACK(ACCESS, TYPE, NAME, COUNT)

    C_DECLARE_REF( CAP_REF );
    C_DECLARE_REF( CHR_REF );
    C_DECLARE_REF( TEAM_REF );
    C_DECLARE_REF( EVE_REF );
    C_DECLARE_REF( ENC_REF );
    C_DECLARE_REF( MAD_REF );
    C_DECLARE_REF( PLA_REF );
    C_DECLARE_REF( PIP_REF );
    C_DECLARE_REF( PRT_REF );
    C_DECLARE_REF( PASS_REF );
    C_DECLARE_REF( SHOP_REF );
    C_DECLARE_REF( PRO_REF );
    C_DECLARE_REF( TX_REF );
    C_DECLARE_REF( BBOARD_REF );
    C_DECLARE_REF( LOOP_REF );
    C_DECLARE_REF( MOD_REF );
    C_DECLARE_REF( TREQ_REF );
    C_DECLARE_REF( MOD_REF_REF );

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// forward declaration of standard dynamic array types

    DECLARE_DYNAMIC_ARY( char_ary,   char )
    DECLARE_DYNAMIC_ARY( short_ary,  short )
    DECLARE_DYNAMIC_ARY( int_ary,    int )
    DECLARE_DYNAMIC_ARY( float_ary,  float )
    DECLARE_DYNAMIC_ARY( double_ary, double )

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#define _egolib_typedef_h