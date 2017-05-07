[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 100
[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./circle_function]
    type = ParsedFunction
    value = '(sqrt(x*x+y*y) < 0.2)*0.5'
  [../]
[]

[Kernels]
  [./diff]
    type = PopulationDiffusion
    variable = u
  [../]
  [./time]
    type = TimeDerivative
    variable = u
  [../]
  [./lg]
    type = LogisticGrowth
    variable = u
  [../]
[]

[Materials]
  [./gcm]
    type = GenericConstantMaterial
    prop_names = 'D a K'
    prop_values = '1e-5 0.01 1'
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 90
  dt = 10
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]

[ICs]
  [./starting_circle]
    function = circle_function
    variable = u
    type = FunctionIC
  [../]
[]

