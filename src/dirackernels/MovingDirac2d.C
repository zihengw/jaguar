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

#include "MovingDirac2d.h"

template <>
InputParameters
validParams<MovingDirac2d>()
{
  InputParameters params = validParams<DiracKernel>();
  params.addRequiredParam<Real>("value", "The value of the point source");
  params.addRequiredParam<Point>("point", "The x,y,z coordinates of the point");
  return params;
}

MovingDirac2d::MovingDirac2d(const InputParameters & parameters)
  : DiracKernel(parameters), _value(getParam<Real>("value")), _point(getParam<Point>("point"))
{
}

void
MovingDirac2d::addPoints()
{
  // Add a point from the input file
  if ( _t <= 4 )
  {
  float locationX = _t + 0.0;
  float locationY = 0.2;
  Point custom_point(locationX, locationY, 0);
  addPoint(custom_point);
  }
  else
  if ( _t > 4 && _t <= 8 )
  {
  float locationX = _t - 4.0;
  float locationY = 0.45;
  Point custom_point(locationX, locationY, 0);
  addPoint(custom_point);
  }
  else
  if ( _t > 8 && _t <= 12 )
  {
  float locationX = _t - 8.0;
  float locationY = 0.7;
  Point custom_point(locationX, locationY, 0);
  addPoint(custom_point);
  }
  else
  {
  float locationX = _t - 12.0;
  float locationY = 0.95;
  Point custom_point(locationX, locationY, 0);
  addPoint(custom_point);
  }
}

Real
MovingDirac2d::computeQpResidual()
{
  // This is negative because it's a forcing function that has been brought over to the left side
  return -_test[_i][_qp] * _value;
}
