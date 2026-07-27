# SConstruct - AutoTitrator-Firmware
# Bare-metal STM32F103C8T6, C++23, SCons build

import os

PROJECT = 'AutoTitrator-Firmware'
MCU     = 'cortex-m3'
CROSS   = ARGUMENTS.get('CROSS', 'arm-none-eabi-')

env = Environment(
    tools   = ['gcc', 'g++', 'gnulink', 'ar', 'as'],
    CC      = CROSS + 'gcc',
    CXX     = CROSS + 'g++',
    AS      = CROSS + 'gcc',
    AR      = CROSS + 'ar',
    LINK    = CROSS + 'g++',
    OBJCOPY = CROSS + 'objcopy',
    SIZE    = CROSS + 'size',
    OBJDUMP = CROSS + 'objdump',
    PROGSUFFIX = '.elf',   # override Windows default .exe
)

# Propagate the user's full environment into the build environment so
# cross-compiler toolchains are found even on Windows.
# Override TMP/TEMP/TMPDIR with a simple project-local path to avoid
# issues with extended-length path prefixes (\\?\...).
env['ENV'] = dict(os.environ)
env['ENV']['TMP']    = 'build/tmp'
env['ENV']['TEMP']   = 'build/tmp'
env['ENV']['TMPDIR'] = 'build/tmp'

# Ensure the temp directory exists (SCons cleans it on -c)
try:
    os.makedirs('build/tmp', exist_ok=True)
except OSError:
    pass

env.Append(
    CCFLAGS=[
        '-mcpu=%s' % MCU, '-mthumb',
        '-ffunction-sections', '-fdata-sections',
        '-O0', '-g3', '-Wall', '-Wextra',
    ],
    CXXFLAGS=[
        '-std=c++23',
        '-fno-exceptions', '-fno-rtti',
        '-fno-use-cxa-atexit',
        '-fcheck-new',           # bare-metal operator new may return null
    ],
    LINKFLAGS=[
        '-mcpu=%s' % MCU, '-mthumb',
        '-T', 'Startup/linker.ld',
        '-nostdlib',
        '-Wl,--gc-sections',
        '-Wl,-Map=build/%s.map' % PROJECT,
        '-Wl,--print-memory-usage',
    ],
    CPPPATH=['include'],
)

# ---- Variant build dirs (keeps .o out of source tree) ----
VariantDir('build/obj/src',     'src',     duplicate=0)
VariantDir('build/obj/Startup', 'Startup', duplicate=0)

# ---- Source files (from variant dirs) ----
sources  = Glob('build/obj/src/*.cpp')
sources += Glob('build/obj/src/**/*.cpp')
sources += Glob('build/obj/Startup/*.cpp')

# ---- Build targets ----
elf = env.Program('build/%s'     % PROJECT,        sources)
hex = env.Command('build/%s.hex'  % PROJECT, elf,   '$OBJCOPY -O ihex $SOURCE $TARGET')
lst = env.Command('build/%s.lst'  % PROJECT, elf,   '$OBJDUMP -S $SOURCE > $TARGET')

env.Alias('hex', hex)
env.Alias('lst', lst)

Default([elf, hex])
Clean(elf, ['build'])
