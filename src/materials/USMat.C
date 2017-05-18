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

#include "USMat.h"

#include "MooseUtils.h"

// libMesh includes
#include "libmesh/quadrature.h"

template <>
InputParameters
validParams<USMat>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredCoupledVar("land_use", "The land-use field");

  params.addRequiredCoupledVar("elevation", "The elevation field");

  params.addRequiredCoupledVar("neighbors_water", "Whether or not the element neighbors water");

  return params;
}

USMat::USMat(const InputParameters & parameters)
  : Material(parameters),
    _land_use(coupledValue("land_use")),
    _elevation(coupledValue("elevation")),
    _neighbors_water(coupledValue("neighbors_water")),
    _D(declareProperty<Real>("D")),
    _a(declareProperty<Real>("a")),
    _K(declareProperty<Real>("K"))
{
}

void
USMat::initQpStatefulProperties()
{
}

void
USMat::computeQpProperties()
{
  _D[_qp] = 2;
  _a[_qp] = 0.02;
  _K[_qp] = 100;

  // Urban
  if (MooseUtils::absoluteFuzzyEqual(18., _land_use[_qp]))
  {
    _K[_qp] *= 1000;
    _a[_qp] *= 2;
  }

  // Hammer water
  if (MooseUtils::absoluteFuzzyEqual(20., _land_use[_qp]))
  {
    _D[_qp] *= 1e-2;
    _a[_qp] = 1e-5;
    _K[_qp] = 1e-4;
  }

  /*
  Real latitude = _q_point[_qp](1);

  Real latitude_penalty = (-1. / 28.) * latitude + (25. / 14.);

  latitude_penalty = std::max(latitude_penalty, 0.1);

  _D[_qp] *= latitude_penalty;
  _a[_qp] *= latitude_penalty;
  _K[_qp] *= latitude_penalty;

  for (auto ba : bad_areas)
  {
    if (MooseUtils::absoluteFuzzyEqual(ba, _land_use[_qp]))
    {
      _a[_qp] *= 0.2;
      _K[_qp] *= 0.2;
      break;
    }
  }
  */

  // Elevation Penalty
  Real elevation_penalty = (0.75 / 3000) * _elevation[_qp];

  elevation_penalty = std::min(.75, elevation_penalty);

  _D[_qp] *= 1. - elevation_penalty;
  _a[_qp] *= 1. - elevation_penalty;
  _K[_qp] *= 1. - elevation_penalty;

  // Water boost
  if (MooseUtils::absoluteFuzzyEqual(1.0, _neighbors_water[_qp]))
  {
    _D[_qp] *= 1.5;
    _a[_qp] *= 4;
  }
}
