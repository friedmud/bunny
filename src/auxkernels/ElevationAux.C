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

#include "ElevationAux.h"

#include "ElevationUserObject.h"

template <>
InputParameters
validParams<ElevationAux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredParam<UserObjectName>("elevation_uo", "The name of the UO holding the data.");

  return params;
}

ElevationAux::ElevationAux(const InputParameters & parameters)
  : AuxKernel(parameters), _elevation_uo(getUserObject<ElevationUserObject>("elevation_uo"))
{
}

Real
ElevationAux::computeValue()
{
  _temp_point = _current_elem->centroid();

  return _elevation_uo.elevation(_temp_point(1), _temp_point(0));
}
