#!/bin/bash

set -e # exit on error

pushd $(dirname "${0}") > /dev/null

xcodebuild -derivedDataPath build -configuration Release -project MoaiSample.xcodeproj -scheme moai

OSX_BIN=../../bin/osx

rm -rf $OSX_BIN
mkdir -p $OSX_BIN
cp -a ./build/Build/Products/Release/moai $OSX_BIN

popd > /dev/null