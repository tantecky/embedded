# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
set_property(GLOBAL PROPERTY CSTD gnu99)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(peripheral_ht)

FILE(GLOB app_sources src/Arduino.c src/MAX31856.cpp src/maxik.cpp src/main.c)
target_sources(app PRIVATE
  ${app_sources}
  )
