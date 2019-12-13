@[Link("glassysnek")]
@[Link(ldflags: "-L/usr/lib -lpython3.7m -lcrypt -lpthread -ldl  -lutil -lm")]
lib LibGlassySnek
  fun startInterpreter()
  fun appendSysPath(path: LibC::Char*)
  fun openFile(fileName: LibC::Char*)
  fun add(a: LibC::Int, b: LibC::Int): LibC::Int
end
