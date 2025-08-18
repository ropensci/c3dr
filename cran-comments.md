## R CMD check results

0 errors | 0 warnings | 1 note

* Days since last update: 2

* This is a fix for the compilation error on r-devel-linux-x86_64-fedora-gcc

## Test environments

R CMD via https://github.com/ropensci/c3dr/actions:

- macOS-latest (R release)
- windows-latest (R release)
- ubuntu-latest (R devel)
- ubuntu-latest (R release)
- ubuntu-latest (R oldrel-1): 1 NOTE

* checking installed package size ... NOTE
  installed size is 11.3Mb
  sub-directories of 1Mb or more:
    extdata   1.2Mb
    libs      9.5Mb

On newer version of R with ubuntu this is an INFO instead of a NOTE.

- rhub clang-asan (https://github.com/ropensci/c3dr/actions/runs/14622677951)
- rhub clang-ubsan (https://github.com/ropensci/c3dr/actions/runs/14622677951)
- win-builder
- rhub gcc15 (local Docker image)
