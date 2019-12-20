@[Link("glassysnek")]
@[Link(ldflags: "-L/usr/lib -lpython3.8 -lcrypt -lpthread -ldl  -lutil -lm -lm")]
lib LibGlassySnek
  struct Stat_t
    name: LibC::Char*
    desc: LibC::Char*
    coef: LibC::Float
    min: LibC::Float
    max: LibC::Float
    mean: LibC::Float
    median: LibC::Float
    std: LibC::Float
    first: LibC::Float
    third: LibC::Float
    value: LibC::Float
  end

  struct Indep_variables_t
    med_inc: Stat_t
    house_age: Stat_t
    ave_rooms: Stat_t
    ave_bedrms: Stat_t
    latitude: Stat_t
    longitudee: Stat_t
  end

  struct Output_t
    intercept: LibC::Float
    indep_variables: Indep_variables_t
    dep_variable: Stat_t
  end

  fun startInterpreter()
  fun appendSysPath(path: LibC::Char*)
  fun openFile(fileName: LibC::Char*)
  fun add(a: LibC::Int, b: LibC::Int): LibC::Int
  fun build_regression_model(): Output_t
end
