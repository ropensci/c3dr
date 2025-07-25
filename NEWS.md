c3dr (development version)
===========================

### NEW FEATURES

  * Support export of force platform data in c3d_write(). Thanks to Michael Schwartz for suggesting and testing this feature.
  
### MINOR IMPROVEMENTS

  * Preserve matrix data structure of imported parameters

c3dr 0.1.5 (2025-05-21)
===========================

### BUG FIXES

  * Fix compilation error for gcc15


c3dr 0.1.4 (2025-05-15)
===========================

First CRAN release.

### MINOR IMPROVEMENTS

  * Minor fixes for the CRAN submission

c3dr 0.1.1 (2025-04-24)
========================

Changes in response to the rOpenSci [peer review process](https://github.com/ropensci/software-review/issues/686).
The repository has been transferred to the rOpenSci organization.

### MINOR IMPROVEMENTS

  * Improved input validation for all functions
  * Improved error messages
  * New method format.c3d() and internal restructuring of printing for c3d objects
  * Internal changes: Improved build process, automated cleaning of build artifacts, restructured source code

### DOCUMENTATION FIXES

  * Updated vignette: Added visualization examples,link to a video of the recording of the example data, minor fixes
  * Added more context for the example data in vignette and function documentation
  * Converted function documentation to markdown
  * Improved function documentation in regard to the different point data formats
  * Fix typos

### BUG FIXES
  
  * Fix bug in c3d_write(): Silently failed when writing directory was nonexistent
  * Fix compiler and ubsan warnings in C++ source code

c3dr 0.1.0 (2025-02-14)
========================

### NEW FEATURES

  * First GitHub release

