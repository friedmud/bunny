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
#include "ElevationGradient.h"

template <>
InputParameters
validParams<ElevationGradient>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("elevation", "The variable holding the elevation.");

  return params;
}

ElevationGradient::ElevationGradient(const InputParameters & parameters)
  : AuxKernel(parameters), _gradient(coupledGradient("elevation"))
{
}

Real
ElevationGradient::computeValue()
{
  return _gradient[_qp].norm();
}
