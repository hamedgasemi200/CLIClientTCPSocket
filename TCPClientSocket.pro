# Include Qt Libraries
QT += core network widgets

# This determines whether the output of the build process will be an application, a library, or a plugin.
TEMPLATE = app

# Show deprication warnings
DEFINES += QT_DEPRECATED_WARNINGS

# Set source files
SOURCES += src/main.cpp

# Set The Target
TARGET = dest/TCPClientSocket
