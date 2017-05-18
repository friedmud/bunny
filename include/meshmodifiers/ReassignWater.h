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

#ifndef REASSIGNWATER_H
#define REASSIGNWATER_H

// MOOSE includes
#include "MeshModifier.h"

// Forward declerations
class ReassignWater;

template <>
InputParameters validParams<ReassignWater>();

/**
 * MeshModifier for assigning a subdomain ID to all elements
 */
class ReassignWater : public MeshModifier
{
public:
  ReassignWater(const InputParameters & parameters);

  ~ReassignWater();

protected:
  float landType(float lat, float lon) const;

  virtual void modify() override;

  short ** _land_types;

  Point _temp_point;
};

#endif // REASSIGNWATER_H
