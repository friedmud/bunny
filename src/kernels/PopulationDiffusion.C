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

#include "PopulationDiffusion.h"

template <>
InputParameters
validParams<PopulationDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addClassDescription("The Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
                             "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  return params;
}

PopulationDiffusion::PopulationDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),
    _D(getMaterialProperty<Real>("D"))
{}

Real
PopulationDiffusion::computeQpResidual()
{
  return _D[_qp] * Diffusion::computeQpResidual();
}

Real
PopulationDiffusion::computeQpJacobian()
{
  return _D[_qp] * Diffusion::computeQpJacobian();
}
