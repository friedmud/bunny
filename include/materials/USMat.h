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

#ifndef USMAT_H
#define USMAT_H

#include "Material.h"

// Forward Declarations
class USMat;

template <>
InputParameters validParams<USMat>();

class USMat : public Material
{
public:
  USMat(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  const VariableValue & _land_use;
  const VariableValue & _elevation;
  const VariableValue & _neighbors_water;

  MaterialProperty<Real> & _D;
  MaterialProperty<Real> & _a;
  MaterialProperty<Real> & _K;

  // Bad area penalty
  std::vector<Real> bad_areas = {7., 9., 5., 6., 8., 11};
};

#endif // USMAT_H
