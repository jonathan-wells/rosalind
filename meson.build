project(
  'rosalind',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3', 'bindir=bin'],
)

inc = include_directories('include')

sources = files(
  'src/cons.c',
  'src/dna.c',
  'src/fib.c',
  'src/file_utils.c',
  'src/gc.c',
  'src/grph.c',
  'src/hamm.c',
  'src/iprb.c',
  'src/main.c',
  'src/prot.c',
  'src/revc.c',
  'src/rna.c',
  'src/subs.c',
)

exe = executable(
  'rosalind',
  sources,
  include_directories : inc,
  install : true,
)

smoke_test = find_program(
  'tests/smoke_test.sh',
)
test(
  'smoke_test',
  smoke_test,
  workdir: meson.project_source_root(),
)
