Mustache library for Staticlibs
===============================

[![travis](https://travis-ci.org/staticlibs/staticlib_mustache.svg?branch=master)](https://travis-ci.org/staticlibs/staticlib_mustache)
[![appveyor](https://ci.appveyor.com/api/projects/status/github/staticlibs/staticlib_mustache?svg=true)](https://ci.appveyor.com/project/staticlibs/staticlib-mustache)

This project is a part of [Staticlibs](http://staticlibs.net/).

This project contains a [PIMPL](https://github.com/staticlibs/staticlib_pimpl) wrapper
for a [mstch](https://github.com/no1msd/mstch) library. [mstch_cpp11](https://github.com/staticlibs/mstch_cpp11).

Library uses `JsonValue`s from [staticlib_serialization](https://github.com/staticlibs/staticlib_serialization)
library for passing parameters to Mustache engine.

Link to the [API documentation](http://staticlibs.github.io/staticlib_mustache/docs/html/namespacestaticlib_1_1mustache.html).

See usage examples in [tests](https://github.com/staticlibs/staticlib_mustache/tree/master/test);

How to build
------------

[CMake](http://cmake.org/) is required for building.

[pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config/) utility is used for dependency management.
For Windows users ready-to-use binary version of `pkg-config` can be obtained from [tools_windows_pkgconfig](https://github.com/staticlibs/tools_windows_pkgconfig) repository.
See [StaticlibsPkgConfig](https://github.com/staticlibs/wiki/wiki/StaticlibsPkgConfig) for Staticlibs-specific details about `pkg-config` usage.

To build the library on Windows using Visual Studio 2013 Express run the following commands using
Visual Studio development command prompt 
(`C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts\VS2013 x86 Native Tools Command Prompt`):

    git clone --recursive https://github.com/staticlibs/external_jansson.git
    git clone https://github.com/staticlibs/staticlib_config.git
    git clone https://github.com/staticlibs/staticlib_support.git
    git clone https://github.com/staticlibs/staticlib_io.git
    git clone https://github.com/staticlibs/staticlib_ranges.git
    git clone https://github.com/staticlibs/staticlib_utils.git
    git clone https://github.com/staticlibs/staticlib_pimpl.git
    git clone https://github.com/staticlibs/staticlib_tinydir.git
    git clone https://github.com/staticlibs/staticlib_json.git
    git clone https://github.com/staticlibs/staticlib_mustache.git
    cd staticlib_mustache
    mkdir build
    cd build
    cmake ..
    msbuild staticlib_mustache.sln

Cloning of [external_jansson](https://github.com/staticlibs/external_jansson) is not required on Linux - 
system [Jansson](http://www.digip.org/jansson/) library will be used instead.

See [StaticlibsToolchains](https://github.com/staticlibs/wiki/wiki/StaticlibsToolchains) for 
more information about the toolchain setup and cross-compilation.

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2017-12-24**

 * version 1.0.2
 * vs2017 support

**2015-05-19**

 * version 1.0.1
 * deps update

**2016-10-28**

 * version 1.0
 * initial public version
