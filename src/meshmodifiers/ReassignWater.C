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

#include "ReassignWater.h"
#include "MooseMesh.h"

#include "land.h"

template <>
InputParameters
validParams<ReassignWater>()
{
  InputParameters params = validParams<MeshModifier>();

  params.addRequiredParam<FileName>("data_file", "Path to the land use data file");

  return params;
}

ReassignWater::ReassignWater(const InputParameters & parameters)
  : MeshModifier(parameters),
    _land_types(read_land_file(const_cast<char *>(getParam<FileName>("data_file").c_str())))
{
}

ReassignWater::~ReassignWater()
{
  free(_land_types[0]);
  free(_land_types);
}

void
ReassignWater::modify()
{
  auto & mesh = _mesh_ptr->getMesh();

  auto elem_it = mesh.elements_begin();
  const auto end_it = mesh.elements_end();

  for (; elem_it != end_it; ++elem_it)
  {
    auto elem = *elem_it;

    _temp_point = elem->centroid();

    auto type = landType(_temp_point(1), _temp_point(0));

    if (MooseUtils::absoluteFuzzyEqual(20., type))
      elem->subdomain_id() = 1;
  }
}

float
ReassignWater::landType(float lat, float lon) const
{
  return get_land_type(lat, lon, _land_types);
}
