import SConsStandard as EnvInit

env = EnvInit.getEnvironment()
env.withConan("conanfile.py")
db = env.withCompilationDB()

env.SConscript("src/SConscript", "nova")
