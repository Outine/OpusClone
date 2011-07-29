/***********************************************************************
Copyright (c) 2006-2011, Skype Limited. All rights reserved. 
Redistribution and use in source and binary forms, with or without 
modification, (subject to the limitations in the disclaimer below) 
are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright 
notice, this list of conditions and the following disclaimer in the 
documentation and/or other materials provided with the distribution.
- Neither the name of Skype Limited, nor the names of specific 
contributors, may be used to endorse or promote products derived from 
this software without specific prior written permission.
NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED 
BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
CONTRIBUTORS ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************/

#include "silk_SigProc_FIX.h"

/* sum= for(i=0;i<len;i++)inVec1[i]*inVec2[i];      ---        inner product    */
/* Note for ARM asm:                                                            */
/*        * inVec1 and inVec2 should be at least 2 byte aligned.    (Or defined as short/int16) */
/*        * len should be positive 16bit integer.                               */
/*        * only when len>6, memory access can be reduced by half.              */

opus_int32 silk_inner_prod_aligned(
    const opus_int16 *const  inVec1,     /*    I input vector 1    */
    const opus_int16 *const  inVec2,     /*    I input vector 2    */
    const opus_int           len         /*    I vector lengths    */
)
{
    opus_int   i; 
    opus_int32 sum = 0;
    for( i = 0; i < len; i++ ) {
        sum = SKP_SMLABB( sum, inVec1[ i ], inVec2[ i ] );
    }
    return sum;
}

opus_int32 silk_inner_prod_aligned_scale(
    const opus_int16 *const  inVec1,     /*    I input vector 1          */
    const opus_int16 *const  inVec2,     /*    I input vector 2          */
    const opus_int           scale,      /*    I number of bits to shift */
    const opus_int           len         /*    I vector lengths          */
)
{
    opus_int   i; 
    opus_int32 sum = 0;
    for( i = 0; i < len; i++ ) {
        sum = SKP_ADD_RSHIFT32( sum, SKP_SMULBB( inVec1[ i ], inVec2[ i ] ), scale );
    }
    return sum;
}

opus_int64 silk_inner_prod16_aligned_64(
    const opus_int16         *inVec1,    /*    I input vector 1    */ 
    const opus_int16         *inVec2,    /*    I input vector 2    */
    const opus_int           len         /*    I vector lengths    */
)
{
    opus_int   i; 
    opus_int64 sum = 0;
    for( i = 0; i < len; i++ ) {
        sum = SKP_SMLALBB( sum, inVec1[ i ], inVec2[ i ] );
    }
    return sum;
}
