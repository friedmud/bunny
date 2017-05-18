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
#ifndef LANDUSEUSEROBJECT_H
#define LANDUSEUSEROBJECT_H

#include "GeneralUserObject.h"
#include "libmesh/fparser.hh"

// Forward Declarations
class LandUseUserObject;

template <>
InputParameters validParams<LandUseUserObject>();

class LandUseUserObject : public GeneralUserObject
{
public:
  LandUseUserObject(const InputParameters & parameters);
  /// The LandUseUserObject DEFINITELY needs a destructor!
  virtual ~LandUseUserObject();

  virtual void initialize() override {}
  virtual void execute() override;
  virtual void finalize() override {}

  float landType(float lat, float lon) const;

protected:
  short ** _land_types;

};

#endif // LANDUSEUSEROBJECT_H
