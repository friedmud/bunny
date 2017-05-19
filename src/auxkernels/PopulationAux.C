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

#include "PopulationAux.h"

#include "PopulationUserObject.h"

template <>
InputParameters
validParams<PopulationAux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredParam<UserObjectName>("population_uo", "The name of the UO holding the data.");

  return params;
}

PopulationAux::PopulationAux(const InputParameters & parameters)
  : AuxKernel(parameters), _population_uo(getUserObject<PopulationUserObject>("population_uo"))
{
}

Real
PopulationAux::computeValue()
{
  _temp_point = _current_elem->centroid();

  return _population_uo.population(_temp_point(1), _temp_point(0));
}
