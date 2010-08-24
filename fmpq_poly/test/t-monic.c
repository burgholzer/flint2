/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart
    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    fmpz_randstate_t state;
    printf("monic/is_monic....");
    fflush(stdout);

    fmpq_poly_randinit(state);

    /* Check aliasing */
    for (i = 0; i < 10000; i++)
    {
        fmpq_poly_t f, g;

        fmpq_poly_init(f);
        fmpq_poly_init(g);
        fmpq_poly_randtest(f, state, n_randint(100), n_randint(200));

        fmpq_poly_monic(g, f);
        fmpq_poly_monic(f, f);

        result = (fmpq_poly_equal(f, g));
        if (!result)
        {
            printf("FAIL:\n");
            fmpq_poly_print(f), printf("\n");
            fmpq_poly_print(g), printf("\n");
            abort();
        }

        fmpq_poly_clear(f);
        fmpq_poly_clear(g);
    }

    /* Check that the result of "monic" has "is_monic" return 1 */
    for (i = 0; i < 10000; i++)
    {
        fmpq_poly_t f;

        fmpq_poly_init(f);
        fmpq_poly_randtest_not_zero(f, state, n_randint(100) + 1, n_randint(200) + 1);

        fmpq_poly_monic(f, f);

        result = (fmpq_poly_is_monic(f));
        if (!result)
        {
            printf("FAIL:\n");
            fmpq_poly_print(f), printf("\n");
            abort();
        }

        fmpq_poly_clear(f);
    }

    fmpq_poly_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}
