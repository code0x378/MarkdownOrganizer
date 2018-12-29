#!/bin/bash

# # Clean up
# rm -r ../installer/src/packages/com.littledogbiguniverse.app/data/*
# rm -r ../installer/src/packages/com.littledogbiguniverse.examples/data/*

# # Copy
# cp -r ../dist/dist-apps/* ../installer/src/packages/com.littledogbiguniverse.app/data/
# cp -r ../dist/dist-lin/* ../installer/src/packages/com.littledogbiguniverse.app/data/
# cp -r ../dist/dist-examples/* ../installer/src/packages/com.littledogbiguniverse.examples/data/

# Build
# ~/bin/QtInstallerFramework/2.0/bin/binarycreator -c ../installer/src/config/config.xml -p ../installer/src/packages ../installer/dist/markdownorganizer-installer

cd ../installer/src/
~/bin/QtInstallerFramework/2.0/bin/repogen -r -p ../installer/src/packages/ repository