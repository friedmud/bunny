#ifndef BUNNYAPP_H
#define BUNNYAPP_H

#include "MooseApp.h"

class bunnyApp;

template<>
InputParameters validParams<bunnyApp>();

class bunnyApp : public MooseApp
{
public:
  bunnyApp(InputParameters parameters);
  virtual ~bunnyApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* BUNNYAPP_H */
