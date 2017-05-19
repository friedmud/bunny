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
#include "PopulationUserObject.h"

#include "population.h"

template <>
InputParameters
validParams<PopulationUserObject>()
{
  InputParameters params = validParams<GeneralUserObject>();

  params.addRequiredParam<FileName>("data_file", "Path to the data file");

  return params;
}

PopulationUserObject::PopulationUserObject(const InputParameters & parameters)
    : GeneralUserObject(parameters),
      _populations(read_population_file(const_cast<char *>(getParam<FileName>("data_file").c_str())))
{
}

PopulationUserObject::~PopulationUserObject()
{
}

void
PopulationUserObject::execute()
{
}

float
PopulationUserObject::population(float lat, float lon) const
{
  return get_population(lat, lon, _populations);
}
