Import("env")

env.Append(
  LINKFLAGS=[
      "-mfloat-abi=hard",
      "-mfpu=fpv4-sp-d16"
  ]
)

env.Append(
  CCFLAGS=[
      "-std=gnu11"
  ]
)

env.Append(
  CXXFLAGS=[
      "-std=gnu++17"
  ]
)