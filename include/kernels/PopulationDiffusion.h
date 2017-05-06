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

#ifndef POPULATIONDIFFUSION_H
#define POPULATIONDIFFUSION_H

#include "Diffusion.h"

class PopulationDiffusion;

template <>
InputParameters validParams<PopulationDiffusion>();

class PopulationDiffusion : public Diffusion
{
public:
  PopulationDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _D;
};

#endif /* POPULATIONDIFFUSION_H */
