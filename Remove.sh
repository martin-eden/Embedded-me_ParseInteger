#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_ParseInteger

# Uninstall dependencies
arduino-cli lib uninstall \
  me_SerialTokenizer \
  me_InstallStandardStreams \
  me_UartSpeeds \
  me_Types
