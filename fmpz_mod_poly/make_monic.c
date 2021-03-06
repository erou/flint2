/*
    Copyright (C) 2011 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "flint.h"
#include "fmpz.h"
#include "fmpz_mod_poly.h"

void fmpz_mod_poly_make_monic(fmpz_mod_poly_t res, const fmpz_mod_poly_t poly)
{
    const slong len = poly->length;
    fmpz_t inv;

    if (len == 0)
    {
        fmpz_mod_poly_zero(res);
        return;
    }

    fmpz_init(inv);
    fmpz_invmod(inv, fmpz_mod_poly_lead(poly), &(poly->p));

    fmpz_mod_poly_fit_length(res, len);
    _fmpz_mod_poly_set_length(res, len);

    _fmpz_mod_poly_scalar_mul_fmpz(res->coeffs, 
                                   poly->coeffs, len, inv, &(poly->p));

    fmpz_clear(inv);
}

