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

#ifndef ELEVATIONAUX_H
#define ELEVATIONAUX_H

#include "AuxKernel.h"

// Forward Declarations
class ElevationAux;
class ElevationUserObject;

template <>
InputParameters validParams<ElevationAux>();

/**
 * Constant auxiliary value
 */
class ElevationAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be
   * built using the same
   * constructor.
   */
  ElevationAux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const ElevationUserObject & _elevation_uo;

private:
  Point _temp_point;
};

#endif // ELEVATIONAUX_H
