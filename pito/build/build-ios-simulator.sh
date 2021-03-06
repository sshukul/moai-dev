#!/bin/bash

set -e # exit on error

pushd $(dirname "${0}")/../../xcode > /dev/null

xcodebuild -derivedDataPath build -configuration Release -workspace moai.xcworkspace -scheme libmoai-ios-all -sdk iphonesimulator PLATFORM_NAME=iphonesimulator || exit 1

if [ ! "$1"=="justlibs" ]; then
xcodebuild -derivedDataPath build -configuration Release -workspace moai.xcworkspace -scheme moai-ios -sdk iphonesimulator PLATFORM_NAME=iphonesimulator || exit 1
fi

popd > /dev/null