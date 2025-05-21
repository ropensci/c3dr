# c3dr


<!-- README.md is generated from README.qmd. Please edit that file -->

<!-- badges: start -->

[![Project Status: Active – The project has reached a stable, usable
state and is being actively
developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Status at rOpenSci Software Peer
Review](https://badges.ropensci.org/686_status.svg)](https://github.com/ropensci/software-review/issues/686)
[![CRAN
status](https://www.r-pkg.org/badges/version/c3dr)](https://CRAN.R-project.org/package=c3dr)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14870399.svg)](https://doi.org/10.5281/zenodo.14870399)
[![R-CMD-check](https://github.com/ropensci/c3dr/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/ropensci/c3dr/actions/workflows/R-CMD-check.yaml)
[![codecov](https://codecov.io/gh/ropensci/c3dr/graph/badge.svg?token=7lAu5XzivG)](https://app.codecov.io/gh/ropensci/c3dr)
<!-- badges: end -->

## Overview

An R package for working with motion capture data based on the C++
library [EZC3D](https://github.com/pyomeca/ezc3d).

## Background

C3D (<https://www.c3d.org/>) is a file format for biomechanical data,
namely motion capture recordings with additional analog data (e.g., from
force plates or electromyography).

The `c3dr` package allows to read, analyze and write C3D files in R
(<https://www.r-project.org/about.html>), a programming language popular
for statistical analyses and data visualization. `c3dr` is build on the
open-source C++ library EZC3D (<https://github.com/pyomeca/ezc3d>).

For more information, read the [Get
Started](https://docs.ropensci.org/c3dr/articles/c3dr.html) vignette.

## Installation

Install the latest development version of `c3dr` from R-Universe:

``` r
install.packages("c3dr", repos = "https://ropensci.r-universe.dev")
```

## Usage

### Read Data

``` r
library(c3dr)

# get example data. Insert your file path instead, e.g.
# path <- "folder/myfilename.c3d"
path <- c3d_example()

# import data
d <- c3d_read(path)
d
#> A c3d object with
#> - 55 data points and 340 frames
#> - 1.70 s measurement duration (200 fps)
#> - 69 analog channels (2000 fps)
#> - 2 force platforms with 3400 frames

# structure of the imported object
str(d, max.level = 1)
#> List of 6
#>  $ header       :List of 6
#>  $ parameters   :List of 7
#>  $ data         :List of 340
#>  $ residuals    : num [1:340, 1:55] 1280 1280 1280 1280 1280 ...
#>  $ analog       :List of 340
#>  $ forceplatform:List of 2
#>  - attr(*, "class")= chr [1:2] "c3d" "list"

# read point data
p <- c3d_data(d)
p[1:5, 1:5]
#>     L_IAS_x  L_IAS_y  L_IAS_z   L_IPS_x  L_IPS_y
#> 1 -220.1226 306.4248 846.3361 -398.1731 237.0688
#> 2 -212.4696 306.5356 844.6985 -390.7831 237.8691
#> 3 -204.8696 306.6555 843.2342 -383.1857 238.6758
#> 4 -197.1952 306.8035 841.6127 -375.7068 239.5434
#> 5 -189.6655 307.0628 840.1692 -368.1680 240.4141

# alternative long data format
p_long <- c3d_data(d, format = "long")
p_long[1:5, 1:5]
#>   frame type     L_IAS     L_IPS     R_IPS
#> 1     1    x -220.1226 -398.1731 -392.8751
#> 2     1    y  306.4248  237.0688  146.2103
#> 3     1    z  846.3361  872.8574  880.3161
#> 4     2    x -212.4696 -390.7831 -385.6659
#> 5     2    y  306.5356  237.8691  147.1048

# read analog data
a <- c3d_analog(d)
a[1:5, 41:43]
#>           EMG 1        EMG 2        EMG 3
#> 1 -3.601184e-05 7.324442e-06 1.647999e-05
#> 2  4.638813e-05 8.697775e-06 1.533555e-05
#> 3  1.280251e-04 1.007111e-05 1.449629e-05
#> 4  1.841029e-04 1.190222e-05 1.350444e-05
#> 5  1.898251e-04 1.464888e-05 1.190222e-05

# read data from first force platform
d$forceplatform[[1]]$forces[1:5, ]
#>            [,1]       [,2]       [,3]
#> [1,] 0.13992119  0.0461483 -0.1835251
#> [2,] 0.13992119 -0.0461483  0.0000000
#> [3,] 0.09328079  0.1845932 -0.1835251
#> [4,] 0.04664040 -0.1384449  0.0000000
#> [5,] 0.04664040 -0.2768898  0.5505753

# write data to a new c3d file
# c3d_write(d, "newfile.c3d")
```

## Citation

``` r
citation("c3dr")
```

    To cite c3dr in publications use:

      Simon Nolte (2025). c3dr: Work with motion capture data in R. R
      package Version 0.1.5. DOI: 10.5281/zenodo.14870399.
      https://docs.ropensci.org/c3dr/

    A BibTeX entry for LaTeX users is

      @Manual{,
        title = {c3dr: Work with motion capture data in R},
        author = {Simon Nolte},
        year = {2025},
        url = {https://docs.ropensci.org/c3dr/},
        doi = {10.5281/zenodo.14870399},
        note = {R package version 0.1.5},
      }

## Acknowledgements

The following people have contributed to this package by providing raw
data files, testing code, suggesting features and/or reviewing the
package: Björn Braunstein, July Pilowsky, Theresa Siepe, Aymeric Stamm.

## Contributing

If you consider contributing to this package, read the
[CONTRIBUTING.md](https://github.com/ropensci/c3dr/blob/main/.github/CONTRIBUTING.md).
Please note that this package is released with a [Contributor Code of
Conduct](https://ropensci.org/code-of-conduct/). By contributing to this
project, you agree to abide by its terms.

## Funding

This project was funded by the Internal Research Funds of the [German
Sport University Cologne](https://www.dshs-koeln.de/english/), grant
agreement number L-11-10011-289-154000.
