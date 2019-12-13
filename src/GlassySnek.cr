require "./lib_glassysnek.cr"

LibGlassySnek.startInterpreter()
LibGlassySnek.appendSysPath("./src/python")
LibGlassySnek.openFile("tools")
x = LibGlassySnek.add(3, 4)
pp x
pp x.class