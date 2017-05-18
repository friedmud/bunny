/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "NeighborsWaterAux.h"

template <>
InputParameters
validParams<NeighborsWaterAux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredParam<UserObjectName>("land_use_uo",
                                          "The name of the UO holding Land Use data.");

  return params;
}

NeighborsWaterAux::NeighborsWaterAux(const InputParameters & parameters)
    : AuxKernel(parameters), _land_use_uo(getUserObject<LandUseUserObject>("land_use_uo"))
{
}

Real
NeighborsWaterAux::computeValue()
{
  for (unsigned int n = 0; n < _current_elem->n_neighbors(); n++)
  {
    auto neighbor = _current_elem->neighbor_ptr(n);

    if (neighbor)
    {
      _temp_point = neighbor->centroid();

      auto type = _land_use_uo.landType(_temp_point(1), _temp_point(0));

      if (MooseUtils::absoluteFuzzyEqual(20., type))
        return 1.0;
    }
  }

  return 0.0;
}
