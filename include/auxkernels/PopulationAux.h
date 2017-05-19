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

#ifndef POPULATIONAUX_H
#define POPULATIONAUX_H

#include "AuxKernel.h"

// Forward Declarations
class PopulationAux;
class PopulationUserObject;

template <>
InputParameters validParams<PopulationAux>();

/**
 * Constant auxiliary value
 */
class PopulationAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be
   * built using the same
   * constructor.
   */
  PopulationAux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const PopulationUserObject & _population_uo;

private:
  Point _temp_point;
};

#endif // POPULATIONAUX_H
