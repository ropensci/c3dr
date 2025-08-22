---
title: 'c3dr: An R Package to Read and Write C3D Motion Capture Files'
tags:
  - R
  - C3D
  - biomechanics
  - kinematics
  - motion capture
authors:
  - name: Simon Nolte
    orcid: 0000-0003-1643-1860
    affiliation: 1
affiliations:
 - name: Institute of Movement and Neurosciences, German Sport University Cologne, Cologne, Germany
   index: 1
   ror: 0189raq88
date: 22 August 2025
bibliography: paper.bib
---

# Summary

Human motion can be recorded in several ways, including three-dimensional motion capture systems, force platforms, electromyographic measurement devices, and inertial measurement units.
These biomechanical measurements are stored and combined in data containers.
The standard format for these data containers is the *C3D* file format.
Software for working with *C3D* files has primarily been limited to programming languages such as C++, Python, or MATLAB.
We here present `c3dr`, an R package for reading and writing *C3D* files.
R is a programming language widely used for statistical modeling and data visualization, and `c3dr` extends its capabilities to biomechanical data analysis.
The package is built on the open C++ library `ezc3d` [@michaud2021].
With `c3dr`, researchers can use R to modify, visualize, and model biomechanical data stored in *C3D* files.

# Statement of need

*C3D* is a binary format commonly used in biomechanics to store data from multiple sources, such as motion capture systems and force plates [@motionlabsystems2021].
The format is widely regarded as the standard data container in the field of human motion analysis.
However, despite its widespread adoption, the available technical tools for working with *C3D* files are limited.

The primary software for handling *C3D* files is the Biomechanical-ToolKit (`BTK`) [@barre2014].
Released as open-source software and popular for its graphical user interface Mokka, `BTK` has long served as the standard tool for biomechanical data analysis; however, the software has not been updated since 2015.
More recent approaches, such as the `ezc3d` library [@michaud2021], are available, but like `BTK`, they are limited to C++, MATLAB, or Python [@johnsson2022].

The *R* language is widely used for scientific visualization, data wrangling, and statistical analysis [@rcoreteam2025].
Yet, no software for reading and analyzing *C3D* files has existed in the R environment.
We here present `c3dr`, an R package built on the open-source C++ library `ezc3d` [@michaud2021].
The package allows users to import, modify, and export *C3D* files directly within R.
This makes it possible to create fully reproducible data analysis pipelines for biomechanical research projects using R.

The `c3dr` package is available from CRAN and can be installed via `install.packages("c3dr")`.
Apart from R and the `Rcpp` package for integrating the C++ source code [@eddelbuettel2011], no additional dependencies are required.
The software is compatible with all major operating systems and contemporary C++ compilers.
The package is released as open-source software under an MIT license.

# Acknowledgements

The following people have contributed to this package by providing raw data files, testing code, suggesting features and/or reviewing the package: Björn Braunstein, July Pilowsky, Michael Schwartz, Theresa Siepe, Aymeric Stamm.

# Funding

This project was funded by the Internal Research Funds of the German Sport University Cologne, grant agreement number L-11-10011-289-154000.

# References
