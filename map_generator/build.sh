#!/bin/sh
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B ../../build_map_generator/ . && cmake --build ../../build_map_generator --target release
