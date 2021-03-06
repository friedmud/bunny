[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10000
  ny = 4000
  xmin = -130
  xmax = -60
  ymin = 22
  ymax = 50
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./land_use]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./elevation]
  [../]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[AuxKernels]
  [./lua]
    type = LandUseAux
    variable = land_use
    execute_on = initial
    land_use_uo = land_use
  [../]
  [./ea]
    type = ElevationAux
    variable = elevation
    execute_on = initial
    elevation_uo = elevation
  [../]
  [./dz]
    type = ElevationAux
    variable = disp_z
    execute_on = initial
    elevation_uo = elevation
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]

[UserObjects]
  [./land_use]
    type = LandUseUserObject
    data_file = ../../data/lc.bin
    execute_on = initial
  [../]
  [./elevation]
    type = ElevationUserObject
    data_file = ../../data/etopo1.xyz
    execute_on = initial
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
[]

[Executioner]
  type = Steady
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]
