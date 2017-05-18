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

#ifndef NEIGHBORSWATERAUX_H
#define NEIGHBORSWATERAUX_H

#include "LandUseUserObject.h"

#include "AuxKernel.h"

// Forward Declarations
class NeighborsWaterAux;

template <>
InputParameters validParams<NeighborsWaterAux>();

/**
 * Constant auxiliary value
 */
class NeighborsWaterAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be
   * built using the same
   * constructor.
   */
  NeighborsWaterAux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const LandUseUserObject & _land_use_uo;

private:
  Point _temp_point;
};

#endif // NEIGHBORSWATERAUX_H
