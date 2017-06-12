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

  params.addRequiredParam<Real>("base_D", "The base Diffusion coefficient to use");
  params.addRequiredParam<Real>("base_a", "The base growth coefficient to use");
  params.addRequiredParam<Real>("base_K", "The base capacity coefficient to use");

  return params;
}

USMat::USMat(const InputParameters & parameters)
  : Material(parameters),
    _land_use(coupledValue("land_use")),
    _elevation(coupledValue("elevation")),
    _elevation_grad(coupledGradient("elevation")),
    _neighbors_water(coupledValue("neighbors_water")),
    _base_D(getParam<Real>("base_D")),
    _base_a(getParam<Real>("base_a")),
    _base_K(getParam<Real>("base_K")),
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
  _D[_qp] = _base_D;
  _a[_qp] = _base_a;
  _K[_qp] = _base_K;

  // Urban
  if (MooseUtils::absoluteFuzzyEqual(18., _land_use[_qp]))
  {
    _K[_qp] *= 4;
    _a[_qp] *= 1.5;
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
  */

  for (auto ba : bad_areas)
  {
    if (MooseUtils::absoluteFuzzyEqual(ba, _land_use[_qp]))
    {
      _a[_qp] *= 0.35;
      _K[_qp] *= 0.35;
      break;
    }
  }

  // Elevation Penalty
  // This is set just beyond the height of Denver
//  if (_elevation[_qp] > 2000)
//  {
    Real elevation_penalty = (0.70 / 4000) * _elevation[_qp];

    elevation_penalty = std::min(.70, elevation_penalty);

    _D[_qp] *= 1. - elevation_penalty;
    _a[_qp] *= 1. - elevation_penalty;
    _K[_qp] *= 1. - elevation_penalty;
//  }

  // Elevation gradient penalty
  // We can't build on the side of mountains!
  if (_elevation_grad[_qp].norm() > 2000)
  {
    _D[_qp] *= 0.1;
    _a[_qp] *= 0.1;
    _K[_qp] *= 0.1;
  }

  // Water boost
  if (MooseUtils::absoluteFuzzyEqual(1.0, _neighbors_water[_qp]))
  {
    _D[_qp] *= 4;
    _a[_qp] *= 4;
  }

  // Hammer Wetland
  if (MooseUtils::absoluteFuzzyEqual(15.0, _neighbors_water[_qp]))
  {
    _K[_qp] *= 0.05;
    _a[_qp] *= 0.05;
  }

  // Ramp K up over time
  _K[_qp] *= std::max((_t - 1620.) / (2017. - 1620.), 0.01);
}
