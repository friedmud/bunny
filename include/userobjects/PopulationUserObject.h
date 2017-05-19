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
#ifndef POPULATIONUSEROBJECT_H
#define POPULATIONUSEROBJECT_H

#include "GeneralUserObject.h"
#include "libmesh/fparser.hh"

// Forward Declarations
class PopulationUserObject;

template <>
InputParameters validParams<PopulationUserObject>();

class PopulationUserObject : public GeneralUserObject
{
public:
  PopulationUserObject(const InputParameters & parameters);
  /// The PopulationUserObject DEFINITELY needs a destructor!
  virtual ~PopulationUserObject();

  virtual void initialize() override {}
  virtual void execute() override;
  virtual void finalize() override {}

  float population(float lat, float lon) const;

protected:
  float ** _populations;

private:
  Point _temp_point;
};

#endif // POPULATIONUSEROBJECT_H
