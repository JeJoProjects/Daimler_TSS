# Daimler_TSS

Simple cmd line module for the collecting directory information, when a new file
has been created.

## Required
* C++ Compiler supports C++20 or latter.
* CMake 3.2

## Features

* New file detection in every given time limit (configurable via command-line).
* Detect creation of a file in a specified directory (configurable via command-line).
* Detect of new file under following cases:
	* Starts with `<name-start>` (configurable via command-line); Default `core`.
	* Ends with `<name-end>` (configurable via command-line); Default `lz4`.
	* Contains one or more hexadecimal id separated by dots.
	* Example name: `core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4`
* Collect data as output .txt file (file format can configurable via command-line).
* Collect new file and/ or its (recursively) directories (configurable via command-line).
* Collect disk usage information of the new file.

## TODO

* Improvements in general command-line inputs parsing.
* Logging system for better diagnostics.
* Handling different file output formats, including `.tar`, and general improvements for the output file creation and handling (i.e FileArchiver class).
* Unit Tests and Module Tests.
* Queue system in handling events in EventMgr!
* Testing in other environments. 
* ...
