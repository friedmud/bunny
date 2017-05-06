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

#include "LogisticGrowth.h"

template <>
InputParameters
validParams<LogisticGrowth>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  return params;
}

LogisticGrowth::LogisticGrowth(const InputParameters & parameters) :
    Kernel(parameters),
    _a(getMaterialProperty<Real>("a")),
    _K(getMaterialProperty<Real>("k"))
{}

Real
LogisticGrowth::computeQpResidual()
{
  return _a[_qp] * _u[_qp] * (1. - (_u[_qp] / _K[_qp]));
}

Real
LogisticGrowth::computeQpJacobian()
{
  return _a[_qp] * _phi[_j][_qp] * (1. - (2. * _u[_qp] / _K[_qp]));
}
