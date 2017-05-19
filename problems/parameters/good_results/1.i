[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 600
  ny = 200
  xmin = -130
  xmax = -60
  ymin = 22
  ymax = 50
[]

[MeshModifiers]
  [./water_id]
    type = ReassignWater
    data_file = ../../data/lc.bin
    land_use_uo = land_use
  [../]
[]

[Variables]
  [./u]
    block = 0
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
  [./neighbors_water]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./pop]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./diff]
    type = PopulationDiffusion
    variable = u
    block = 0
  [../]
  [./time]
    type = TimeDerivative
    variable = u
    block = 0
  [../]
  [./lg]
    type = LogisticGrowth
    variable = u
    land_use = land_use
    block = 0
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
  [./nw]
    type = NeighborsWaterAux
    variable = neighbors_water
    land_use_uo = land_use
    execute_on = initial
    block = 0
  [../]
  [./popa]
    type = PopulationAux
    variable = pop
    execute_on = initial
    population_uo = pop_uo
    block = 0
  [../]
[]

[Materials]
  active = 'us'
  [./gcm]
    type = GenericConstantMaterial
    prop_names = 'D a K'
    prop_values = '10 0.01 1'
    block = 0
  [../]
  [./us]
    type = USMat
    output_properties = 'D a K'
    elevation = elevation
    outputs = exodus
    land_use = land_use
    block = 0
    neighbors_water = neighbors_water
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
  [./pop_uo]
    type = PopulationUserObject
    data_file = ../../data/pop.bin
  [../]
[]

[Problem]
  type = FEProblem
  material_coverage_check = false
  kernel_coverage_check = false
[]

[Executioner]
  type = Transient
  start_time = 1620
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 2017
  nl_rel_tol = 1e-7
[]

[Outputs]
  exodus = true
[]

[ICs]
  [./init_pop]
    x1 = -71.05
    y1 = 42.35
    radius = 0.4
    outvalue = 0
    variable = u
    invalue = .5
    type = SmoothCircleIC
    block = 0
  [../]
[]

