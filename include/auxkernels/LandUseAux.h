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

#ifndef LANDUSEAUX_H
#define LANDUSEAUX_H

#include "LandUseUserObject.h"

#include "AuxKernel.h"

// Forward Declarations
class LandUseAux;

template <>
InputParameters validParams<LandUseAux>();

/**
 * Constant auxiliary value
 */
class LandUseAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be
   * built using the same
   * constructor.
   */
  LandUseAux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const LandUseUserObject & _land_use_uo;

private:
  Point _temp_point;
};

#endif // LANDUSEAUX_H
