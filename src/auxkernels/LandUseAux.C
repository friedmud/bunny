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

#include "LandUseAux.h"

template <>
InputParameters
validParams<LandUseAux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredParam<UserObjectName>("land_use_uo",
                                          "The name of the UO holding Land Use data.");

  return params;
}

LandUseAux::LandUseAux(const InputParameters & parameters)
    : AuxKernel(parameters), _land_use_uo(getUserObject<LandUseUserObject>("land_use_uo"))
{
}

Real
LandUseAux::computeValue()
{
  _temp_point = _current_elem->centroid();

  return _land_use_uo.landType(_temp_point(1), _temp_point(0));
}
