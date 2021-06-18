project('libyggdrasil',
    [ 'c', 'cpp' ],
    license: [ 'GPLv2' ],
    default_options: [ 'c_std=c11', 'cpp_std=c++2a', 'b_asneeded=false', 'b_lundef=false'],
    version: '1.0.0'
)

c_args = [ '-DBOARD=ASGARD', '-DYGGDRASIL_PERIPHERAL_DEFS' ]
cpp_args = [ ] + c_args

# Make sure the project gets cross compiled
    assert(meson.is_cross_build(), 'This project can only be cross-compiled. Make sure to call meson with the "--cross-file=asgard" option!')


# Available portlib libraries 
    sysroot = meson.get_cross_property('sys_root')

    libstdcpp = declare_dependency(link_args : [ '-L' + sysroot + '/lib/libc.a', '-static-libstdc++', '-static-libgcc' ])

    linux_headers = sysroot + '/usr/include'


# Source files and include directories
    source_files = [
        'Src/c/asgard/driver/gpio.cpp',
        'Src/c/asgard/driver/i2c.cpp',
        'Src/c/asgard/driver/display.cpp',

        'Src/c/yggdrasil/peripherals/color_sensor.cpp',
        'Src/c/yggdrasil/peripherals/humidity_sensor.cpp',
        'Src/c/yggdrasil/peripherals/joystick.cpp',
        'Src/c/yggdrasil/peripherals/rtc.cpp',
        'Src/c/yggdrasil/peripherals/six_axis_sensor.cpp',

        'Src/common/resources/fonts/font8.c',
        'Src/common/resources/fonts/font12.c',
        'Src/common/resources/fonts/font16.c',
        'Src/common/resources/fonts/font20.c',
        'Src/common/resources/fonts/font24.c',
    ]

    include_dirs = include_directories('Inc', linux_headers)


# Executable building
    library = static_library(
        'libyggdrasil.a',
        source_files,
        native: false,
        c_args: c_args,
        cpp_args: cpp_args,
        name_prefix: '',
        dependencies: [ libstdcpp ],
        include_directories: include_dirs
    )

    dep = declare_dependency(include_directories: include_dirs, link_with: library)