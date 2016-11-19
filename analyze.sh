#!/bin/sh

clang++ --analyze --std=c++11 -I./src -I ./build ./src/**/*
