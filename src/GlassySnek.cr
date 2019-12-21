require "./lib_glassysnek.cr"

LibGlassySnek.startInterpreter()
LibGlassySnek.appendSysPath("./src/python")
LibGlassySnek.openFile("tools")
x = LibGlassySnek.add(3, 4)
pp x
pp x.class

LibGlassySnek.appendSysPath("./.venv/lib/python3.8/site-packages")
LibGlassySnek.openFile("housing_analyzer")
x = LibGlassySnek.build_regression_model()
pp x
