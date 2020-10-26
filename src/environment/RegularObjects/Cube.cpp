//
// Created by lilian on 15/10/2020.
//

#include "Cube.h"

Cube::Cube(double size) : size(size)
{

}

void Cube::Tesselate()
{
  this->tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, size / 2, size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, size / 2, -size / 2), Point3D(-size / 2, size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, size / 2, -size / 2), Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(-size / 2, -size / 2, size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(-size / 2, size / 2, -size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2)));
  this->tessels.push_back(new Tessel(Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2)));
  this->tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2), Point3D(size / 2, size / 2, -size / 2)));
  this->tessels.push_back(new Tessel(Point3D(-size / 2, size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2), Point3D(size / 2, size / 2, -size / 2)));
}