/*
    Copyright (C) 2017 Luca De Feo

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifndef FMPZ_MOD_MAT_H
#define FMPZ_MOD_MAT_H

#ifdef FMPZ_MOD_MAT_INLINES_C
#define FMPZ_MOD_MAT_INLINE FLINT_DLL
#else
#define FMPZ_MOD_MAT_INLINE static __inline__
#endif

#include "flint.h"
#include "fmpz_mat.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
    fmpz_mat_t mat;
    fmpz_t mod;
}
fmpz_mod_mat_struct;

/* fmpz_mod_mat_t allows reference-like semantics for fmpz_mod_mat_struct */
typedef fmpz_mod_mat_struct fmpz_mod_mat_t[1];

/* Memory management  ********************************************************/

FMPZ_MOD_MAT_INLINE
fmpz * fmpz_mod_mat_entry(const fmpz_mod_mat_t mat, slong i, slong j)
{
    return fmpz_mat_entry(mat->mat, i, j);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_set_entry(fmpz_mod_mat_t mat, slong i, slong j, const fmpz_t val)
{
    fmpz_set(fmpz_mat_entry(mat->mat, i, j), val);
}

FMPZ_MOD_MAT_INLINE
slong fmpz_mod_mat_nrows(const fmpz_mod_mat_t mat)
{
    return fmpz_mat_nrows(mat->mat);
}

FMPZ_MOD_MAT_INLINE
slong fmpz_mod_mat_ncols(const fmpz_mod_mat_t mat)
{
    return fmpz_mat_ncols(mat->mat);
}

FMPZ_MOD_MAT_INLINE
void _fmpz_mod_mat_set_mod(fmpz_mod_mat_t mat, const fmpz_t n)
{
    fmpz_set(mat->mod, n);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_init(fmpz_mod_mat_t mat, slong rows, slong cols, const fmpz_t n)
{
    fmpz_mat_init(mat->mat, rows, cols);
    fmpz_init(mat->mod);
    _fmpz_mod_mat_set_mod(mat, n);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_init_set(fmpz_mod_mat_t mat, const fmpz_mod_mat_t src)
{
    fmpz_mat_init_set(mat->mat, src->mat);
    fmpz_init_set(mat->mod, src->mod);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_clear(fmpz_mod_mat_t mat)
{
    fmpz_mat_clear(mat->mat);
    fmpz_clear(mat->mod);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_one(fmpz_mod_mat_t mat)
{
    fmpz_mat_one(mat->mat);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_zero(fmpz_mod_mat_t mat)
{
    fmpz_mat_zero(mat->mat);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_swap(fmpz_mod_mat_t mat1, fmpz_mod_mat_t mat2)
{
    if (mat1 != mat2)
    {
        fmpz_mod_mat_struct tmp;

        tmp = *mat1;
        *mat1 = *mat2;
        *mat2 = tmp;
    }
}


FMPZ_MOD_MAT_INLINE
void _fmpz_mod_mat_reduce(fmpz_mod_mat_t mat)
{
    slong i, j;
    fmpz *entry;
    for (i = 0; i < mat->mat->r; i++)
    {
        for (j = 0; j < mat->mat->c; j++)
        {
            entry = fmpz_mod_mat_entry(mat, i, j);
            fmpz_mod(entry, entry, mat->mod);
        }
    }
}

/* Random matrix generation */
FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_randtest(fmpz_mod_mat_t mat, flint_rand_t state)
{
    fmpz_mat_randtest(mat->mat, state, fmpz_bits(mat->mod));
    _fmpz_mod_mat_reduce(mat);
}

/* Windows and concatenation */

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_window_init(fmpz_mod_mat_t window, const fmpz_mod_mat_t mat,
                              slong r1, slong c1, slong r2, slong c2)
{
    fmpz_mat_window_init(window->mat, mat->mat, r1, c1, r2, c2);
    fmpz_init_set(window->mod, mat->mod);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_window_clear(fmpz_mod_mat_t window)
{
    fmpz_mat_window_clear(window->mat);
    fmpz_clear(window->mod);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_concat_horizontal(fmpz_mod_mat_t res,
                                    const fmpz_mod_mat_t mat1,
                                    const fmpz_mod_mat_t mat2)
{
    fmpz_mat_concat_horizontal(res->mat, mat1->mat, mat2->mat);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_concat_vertical(fmpz_mod_mat_t res,
                                  const fmpz_mod_mat_t mat1,
                                  const fmpz_mod_mat_t mat2)
{
    fmpz_mat_concat_vertical(res->mat, mat1->mat, mat2->mat);
}

/* Inupt - Output */
FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_print_pretty(const fmpz_mod_mat_t mat)
{
    fmpz_mat_print_pretty(mat->mat);
}

FMPZ_MOD_MAT_INLINE
int fmpz_mod_mat_equal(const fmpz_mod_mat_t mat1, const fmpz_mod_mat_t mat2)
{
    return fmpz_equal(mat1->mod, mat2->mod) && fmpz_mat_equal(mat1->mat, mat2->mat);
}

FMPZ_MOD_MAT_INLINE
int fmpz_mod_mat_is_zero(const fmpz_mod_mat_t mat)
{
    return fmpz_mat_is_zero(mat->mat);
}


FMPZ_MOD_MAT_INLINE
int fmpz_mod_mat_is_empty(const fmpz_mod_mat_t mat)
{
    return fmpz_mat_is_empty(mat->mat);
}

FMPZ_MOD_MAT_INLINE
int fmpz_mod_mat_is_square(const fmpz_mod_mat_t mat)
{
    return fmpz_mat_is_square(mat->mat);
}


FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_set(fmpz_mod_mat_t B, const fmpz_mod_mat_t A)
{
    fmpz_set(B->mod, A->mod);
    fmpz_mat_set(B->mat, A->mat);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_transpose(fmpz_mod_mat_t B, const fmpz_mod_mat_t A)
{
    fmpz_mat_transpose(B->mat, A->mat);
}


/* Addition and subtraction */

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_add(fmpz_mod_mat_t C, const fmpz_mod_mat_t A, const fmpz_mod_mat_t B)
{
    fmpz_mat_add(C->mat, A->mat, B->mat);
    _fmpz_mod_mat_reduce(C);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_sub(fmpz_mod_mat_t C, const fmpz_mod_mat_t A, const fmpz_mod_mat_t B)
{
    fmpz_mat_sub(C->mat, A->mat, B->mat);
    _fmpz_mod_mat_reduce(C);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_neg(fmpz_mod_mat_t B, const fmpz_mod_mat_t A)
{
    fmpz_mat_neg(B->mat, A->mat);
    _fmpz_mod_mat_reduce(B);
}

/* Matrix-scalar arithmetic */

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_scalar_mul_si(fmpz_mod_mat_t B, const fmpz_mod_mat_t A, slong c)
{
    fmpz_mat_scalar_mul_si(B->mat, A->mat, c);
    _fmpz_mod_mat_reduce(B);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_scalar_mul_ui(fmpz_mod_mat_t B, const fmpz_mod_mat_t A, ulong c)
{
    fmpz_mat_scalar_mul_ui(B->mat, A->mat, c);
    _fmpz_mod_mat_reduce(B);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_scalar_mul_fmpz(fmpz_mod_mat_t B, const fmpz_mod_mat_t A, fmpz_t c)
{
    fmpz_mat_scalar_mul_fmpz(B->mat, A->mat, c);
    _fmpz_mod_mat_reduce(B);
}

/* Matrix multiplication */

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_mul(fmpz_mod_mat_t C, const fmpz_mod_mat_t A, const fmpz_mod_mat_t B)
{
    fmpz_mat_mul(C->mat, A->mat, B->mat);
    _fmpz_mod_mat_reduce(C);
}

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_sqr(fmpz_mod_mat_t B, const fmpz_mod_mat_t A)
{
    fmpz_mat_sqr(B->mat, A->mat);
    _fmpz_mod_mat_reduce(B);
}

/* Trace */

FMPZ_MOD_MAT_INLINE
void fmpz_mod_mat_trace(fmpz_t trace, const fmpz_mod_mat_t mat)
{
    fmpz_mat_trace(trace, mat->mat);
    fmpz_mod(trace, trace, mat->mod);
}

#ifdef __cplusplus
}
#endif

#endif

