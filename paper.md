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
date: 06 January 2025
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

The *R* language is widely used for scientific visualization, data wrangling, and statistical analysis [@rcoreteam2025].
Yet, no software for reading and analyzing *C3D* files has existed in the R environment.
We here present `c3dr`, an R package built on the open-source C++ library `ezc3d` [@michaud2021].
The package allows users to import, modify, and export *C3D* files directly within R.
This makes it possible to create fully reproducible data analysis pipelines for biomechanical research projects using R.

# State of the field

The primary software for handling *C3D* files is the Biomechanical-ToolKit (`BTK`) [@barre2014].
Released as open-source software and popular for its graphical user interface Mokka, `BTK` has long served as the standard tool for biomechanical data analysis; however, the software has not been updated since 2015.
More recent approaches, such as the `ezc3d` library [@michaud2021], are available, but like `BTK`, they are limited to C++, MATLAB, or Python [@johnsson2022].

To work with *C3D* data in R without a dedicated package, several cumbersome options exist.
First, the data could be exported via graphical user interfaces as a *CSV* file and then imported in R.
However, this workflow is not reproducible, inefficient, and does not preserve the metadata of the recording.
Second, one could use the Python interface for `ezc3d` in R via the `reticulate` package [@reticulate], but this requires expertise in both Python and R and conversion of objects between the two is suboptimal for *C3D* data.
Third, one could use the SWIG port available for R, but a dedicated software provided as an R package is easier to install and to use.

The `c3dr` package is available from CRAN and can be installed via `install.packages("c3dr")`.
Apart from R and the `Rcpp` package for integrating the C++ source code [@eddelbuettel2011], no additional dependencies are required.
The software is compatible with all major operating systems and contemporary C++ compilers.
The package is released as open-source software under an MIT license.

# Software Design

The core of `c3dr` is the reading and writing functions for *C3D* data that wrap the existing C++ functionality of `ezc3d`.
A key challenge was to translate the structure of *C3D* data into an appropriate structure for R objects.
Internally, `c3dr` treats *C3D* data as nested lists with different categories.
This guarantees that all data and metadata are imported and available for re-export.
Because nested lists are difficult to handle in R, several accessor functions are provided to convert the list data into more accessible data (and back), such as data.frame, which can be directly used for statistical analysis or visualization.
When writing an *C3D* file, `c3dr` recreates the file from scratch, even if no modifications were made.
This means that importing and re-exporting a file with the package may lead to minor modifications in the structure of the file.
But rebuilding the file based on the available data is the only way to create valid files in response to changes to the data undertaken in R.
It also ensures uniform output formats regardless of the input *C3D* format.

# Research Impact Statement

In its first 9 months on CRAN, `c3dr` has been downloaded more than 2500 times from the RStudio mirror.
It is actively used at different universities for research and teaching, though no publications have yet resulted from these activities.
The package has had several non-coding contributors from different countries.
Since `c3dr` is the only package in R to support C3D data, future use in biomechanical research projects is to be expected.

# AI usage disclosure

In writing the software documentation and the research paper, ChatGPT (GPT-4) was used for language improvements in the form of minor grammar and style edits.
Additionally, the same tool was used for reviewing and refactoring code in the C++ wrapper functions.
All edits coauthored by AI were verified by human review and the software passes an extensive test suite.

# Acknowledgements

The following people have contributed to this package by providing raw data files, testing code, suggesting features and/or reviewing the package: Björn Braunstein, July Pilowsky, Michael Schwartz, Theresa Siepe, Aymeric Stamm.

# Funding

This project was funded by the Internal Research Funds of the German Sport University Cologne, grant agreement number L-11-10011-289-154000.

# References

