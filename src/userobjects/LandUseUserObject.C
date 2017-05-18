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
#include "LandUseUserObject.h"

#include "land.h"

template <>
InputParameters
validParams<LandUseUserObject>()
{
  InputParameters params = validParams<GeneralUserObject>();

  params.addRequiredParam<FileName>("data_file", "Path to the land use data file");

  return params;
}

LandUseUserObject::LandUseUserObject(const InputParameters & parameters)
    : GeneralUserObject(parameters),
      _land_types(read_land_file(const_cast<char *>(getParam<FileName>("data_file").c_str())))
{
}

LandUseUserObject::~LandUseUserObject()
{
  free(_land_types[0]);
  free(_land_types);
}

void
LandUseUserObject::execute()
{
}

float
LandUseUserObject::landType(float lat, float lon) const
{
  return get_land_type(lat, lon, _land_types);
}
