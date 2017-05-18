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
#include "ElevationUserObject.h"

#include "elevation.h"

template <>
InputParameters
validParams<ElevationUserObject>()
{
  InputParameters params = validParams<GeneralUserObject>();

  params.addRequiredParam<FileName>("data_file", "Path to the data file");

  return params;
}

ElevationUserObject::ElevationUserObject(const InputParameters & parameters)
    : GeneralUserObject(parameters),
      _elevations(read_elevation_file(const_cast<char *>(getParam<FileName>("data_file").c_str())))
{
}

ElevationUserObject::~ElevationUserObject()
{
}

void
ElevationUserObject::execute()
{
}

float
ElevationUserObject::elevation(float lat, float lon) const
{
  return get_elevation(lat, lon, _elevations);
}
