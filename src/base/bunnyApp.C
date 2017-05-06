#include "bunnyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

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
}

// External entry point for dynamic syntax association
extern "C" void bunnyApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { bunnyApp::associateSyntax(syntax, action_factory); }
void
bunnyApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
