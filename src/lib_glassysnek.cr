@[Link("glassysnek")]
@[Link(ldflags: "-L/usr/lib -lpython3.6m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic")]
lib LibGlassySnek
  fun startInterpreter()
  fun appendSysPath(path: LibC::Char*)
  fun openFile(fileName: LibC::Char*)
  fun add(a: LibC::Int, b: LibC::Int)
end
