#!/bin/sh
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B ../../build_client/ . && bear -- cmake --build ../../build_client --target release
