#!/bin/bash

# Clean up
rm -r ../installer/src/packages/com.littledogbiguniverse.app/data/*
rm -r ../installer/src/packages/com.littledogbiguniverse.examples/data/*

# Copy
cp -r ../dist/dist-apps/* ../installer/src/packages/com.littledogbiguniverse.app/data/
cp -r ../dist/dist-lin/* ../installer/src/packages/com.littledogbiguniverse.app/data/
cp -r ../dist/dist-examples/* ../installer/src/packages/com.littledogbiguniverse.examples/data/

# Build
#fixme#/bin/qt/Tools/QtInstallerFramework/2.0/bin/binarycreator -c ../installer/src/config/config.xml -p ../installer/src/packages ../installer/dist/markdownorganizer-installer

# Run
../installer/dist/markdownorganizer-installer