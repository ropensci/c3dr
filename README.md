# c3dr

<!-- README.md is generated from README.qmd. Please edit that file -->
<!-- badges: start -->

[![Project Status: WIP – Initial development is in progress, but there
has not yet been a stable, usable release suitable for the
public.](https://www.repostatus.org/badges/latest/wip.svg)](https://www.repostatus.org/#wip)
[![R-CMD-check](https://github.com/smnnlt/c3dr/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/smnnlt/c3dr/actions/workflows/R-CMD-check.yaml)
[![codecov](https://codecov.io/gh/smnnlt/c3dr/graph/badge.svg?token=BTRQJ0A831)](https://codecov.io/gh/smnnlt/c3dr)

<!-- badges: end -->

## Overview

An R package for working with motion capture data based on the C++
library [EZC3D](https://github.com/pyomeca/ezc3d).

## Background

C3D (<https://www.c3d.org/>) is a file format for biomechanical data,
namely motion capture recording with additional analog data (e.g., from
force plates or electromyography).

The `c3dr` package allow to read and analyze C3D files in R
(<https://www.r-project.org/about.html>), a programming language popular
for statistical analyses and data visualization. It is build on the
open-source C++ library EZC3D (<https://github.com/pyomeca/ezc3d>).

## Installation

Install `c3dr` from GitHub:

``` r
if (!require(pak)) install.packages("pak")
pak::pak("smnnlt/c3dr")
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
#> - 54 data points and 1885 frames
#> - 7.85 s measurement duration (240 fps)
#> - 1 analog channels (960 fps)

# structure of the imported object
str(d, max.level = 1)
#> List of 6
#>  $ header   :List of 6
#>  $ labels   : chr [1:54] "LASI" "RASI" "LPSI" "RPSI" ...
#>  $ alabels  : chr "Electric Potential.Trigger"
#>  $ data     :List of 1885
#>  $ residuals: num [1:1885, 1:54] 172 171 172 172 172 ...
#>  $ analog   :List of 1885
#>  - attr(*, "class")= chr [1:2] "c3d" "list"

# read point data
p <- c3d_data(d)
p[1:5, 1:5]
#>     LASI_x   LASI_y   LASI_z   RASI_x   RASI_y
#> 1 514.7515 426.1067 1111.939 517.2385 140.1397
#> 2 514.1281 425.5054 1112.686 517.2141 140.0569
#> 3 514.5764 425.8453 1112.585 517.1833 139.9610
#> 4 514.4996 425.7862 1112.925 517.1443 139.9025
#> 5 514.3743 425.7397 1113.257 517.0745 139.8348

# alternative long data format
p_long <- c3d_data(d, format = "long")
p_long[1:5, 1:5]
#>     frame type      LASI      RASI      LPSI
#> 1.x     1    x  514.7515  517.2385  365.6084
#> 1.y     1    y  426.1067  140.1397  348.0317
#> 1.z     1    z 1111.9390 1085.5681 1196.8900
#> 2.x     2    x  514.1281  517.2141  365.5312
#> 2.y     2    y  425.5054  140.0569  347.8595

# read analog data
a <- c3d_analog(d)
head(a)
#>   Electric Potential.Trigger
#> 1              -0.0001525879
#> 2              -0.0001525879
#> 3               0.0000000000
#> 4               0.0000000000
#> 5               0.0000000000
#> 6               0.0003051758
```

## Citation

``` r
citation("c3dr")
```

    To cite spiro in publications use:

      Simon Nolte (2024). c3dr: Work with motion capture data in R. R
      package Version 0.0.0.9000, https://github.com/smnnlt/c3dr

    A BibTeX entry for LaTeX users is

      @Manual{,
        title = {c3dr: Work with motion capture data in R},
        author = {Simon Nolte},
        year = {2024},
        url = {https://github.com/smnnlt/c3dr},
        note = {R package version 0.0.0.9000},
      }

## Contributing

If you consider contributing to this package, read the
[CONTRIBUTING.md](https://github.com/smnnlt/c3dr/blob/main/.github/CONTRIBUTING.md).
Please note that the c3dr project is released with a [Contributor Code
of
Conduct](https://github.com/smnnlt/c3dr/blob/main/CODE_OF_CONDUCT.md).
By contributing to this project, you agree to abide by its terms.

## Funding

This project was funded by the Internal Research Funds of the [German
Sport University Cologne](https://www.dshs-koeln.de/english/), grant
agreement number L-11-10011-289-154000.
