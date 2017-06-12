#include "bunnyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// Kernels
#include "LogisticGrowth.h"
#include "PopulationDiffusion.h"

// AuxKernels
#include "ElevationAux.h"
#include "LandUseAux.h"
#include "NeighborsWaterAux.h"
#include "PopulationAux.h"
#include "ElevationGradient.h"

// Materials
#include "USMat.h"

// UserObjects
#include "ElevationUserObject.h"
#include "LandUseUserObject.h"
#include "PopulationUserObject.h"

// MeshModifiers
#include "ReassignWater.h"

template<>
InputParameters validParams<bunnyApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

bunnyApp::bunnyApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  bunnyApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  bunnyApp::associateSyntax(_syntax, _action_factory);
}

bunnyApp::~bunnyApp()
{
}

// External entry point for dynamic application loading
extern "C" void bunnyApp__registerApps() { bunnyApp::registerApps(); }
void
bunnyApp::registerApps()
{
  registerApp(bunnyApp);
}

// External entry point for dynamic object registration
extern "C" void bunnyApp__registerObjects(Factory & factory) { bunnyApp::registerObjects(factory); }
void
bunnyApp::registerObjects(Factory & factory)
{
  registerKernel(LogisticGrowth);
  registerKernel(PopulationDiffusion);

  registerAux(ElevationAux);
  registerAux(LandUseAux);
  registerAux(NeighborsWaterAux);
  registerAux(PopulationAux);
  registerAux(ElevationGradient);

  registerMaterial(USMat);

  registerUserObject(ElevationUserObject);
  registerUserObject(LandUseUserObject);
  registerUserObject(PopulationUserObject);

  registerMeshModifier(ReassignWater);
}

// External entry point for dynamic syntax association
extern "C" void bunnyApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { bunnyApp::associateSyntax(syntax, action_factory); }
void
bunnyApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
