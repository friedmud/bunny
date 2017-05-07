[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
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

[Adaptivity]
  max_h_level = 5
  initial_steps = 5
  marker = efm
  initial_marker = efm
  [./Indicators]
    [./gji]
      type = GradientJumpIndicator
      variable = u
      scale_by_flux_faces = true
    [../]
  [../]
  [./Markers]
    [./efm]
      type = ErrorFractionMarker
      coarsen = 0.1
      indicator = gji
      refine = 0.8
    [../]
  [../]
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

