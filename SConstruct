import SConsStandard as EnvInit

env = EnvInit.getEnvironment()
env.withConan("conanfile.py")
db = env.withCompilationDB()
env.AlwaysBuild(db)

env.addHelp("""
Welcome to Nova's build system!

This is where you generate a Nova binary. There's a number of options for the build:
""")

env.addVariableHelp()

env.addHelp("""
The following targets are available:
  <default, used for no target specified>   -- build Nova
  test                                      -- runs tests, and builds Nova if necessary
  install                                   -- Currently not implemented
  package                                   -- Currently not implemented
""")

env.SConscript("src/SConscript", "nova")
env.SConscript("test/SConscript", "test")

env.Depends(BUILD_TARGETS, db)
