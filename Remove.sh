#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_InstallStandardStreams

# Uninstall dependencies
arduino-cli lib uninstall \
  me_Uart \
  me_BaseTypes
