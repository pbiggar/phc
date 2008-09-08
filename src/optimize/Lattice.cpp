#include "Lattice.h"

/*		VisitPhi:
 *		The lattice of the phis output variable is the meet of all the inputs
 *		(non-execable means TOP), with the meet function:
 *			any + TOP = any
 *			any + BOTTOM = BOTTOM
 *			ci + cj = ci if i == j (? surely if c_i == c_j?)
 *			c1 + c2 = BOTTOM if i != j (this can be improved with VRP, using a similar algorithm).
 */
// TODO move this into SCCP
Lattice_cell meet (Lattice_cell l1, Lattice_cell l2)
{
	switch (l1)
	{
		case TOP:
			return l2;

		case CONST:
		{
			switch (l2)
			{
				case TOP:
					return l1;

				case CONST:
					// TODO
					return CONST;

				case BOTTOM:
					return BOTTOM;

				default:
					assert (0);
			}
			break;
		}

		case BOTTOM:
			return BOTTOM;

		default:
			assert (0);
	}
}
