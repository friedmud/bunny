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
#ifndef ELEVATIONUSEROBJECT_H
#define ELEVATIONUSEROBJECT_H

#include "GeneralUserObject.h"
#include "libmesh/fparser.hh"

// Forward Declarations
class ElevationUserObject;

template <>
InputParameters validParams<ElevationUserObject>();

class ElevationUserObject : public GeneralUserObject
{
public:
  ElevationUserObject(const InputParameters & parameters);
  /// The ElevationUserObject DEFINITELY needs a destructor!
  virtual ~ElevationUserObject();

  virtual void initialize() override {}
  virtual void execute() override;
  virtual void finalize() override {}

  float elevation(float lat, float lon) const;

protected:
  float ** _elevations;

private:
  Point _temp_point;
};

#endif // ELEVATIONUSEROBJECT_H
