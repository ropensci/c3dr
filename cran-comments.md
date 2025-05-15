## Resubmission
This is a resubmission. In this version I have:

* Fixed the test failure

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.

## Test environments


R CMD via https://github.com/ropensci/c3dr/actions:
- macOS-latest (R release)
- windows-latest (R release)
- ubuntu-latest (R devel)
- ubuntu-latest (R release)
- ubuntu-latest (R oldrel-1): 1 NOTE

* checking installed package size ... NOTE
  installed size is 11.2Mb
  sub-directories of 1Mb or more:
    extdata   1.2Mb
    libs      9.5Mb

On newer version of R with ubuntu this is an INFO instead of a NOTE.

- rhub clang-asan (https://github.com/ropensci/c3dr/actions/runs/14622677951)
- rhub clang-ubsan (https://github.com/ropensci/c3dr/actions/runs/14622677951)
- win-builder: 2 NOTES

* checking CRAN incoming feasibility ... [10s] NOTE
  Maintainer: 'Simon Nolte <s.nolte@dshs-koeln.de>'

  New submission

  Version contains large components (0.1.2)

  Possibly misspelled words in DESCRIPTION:
    EZC (16:35)

'EZC3d' is the name of the C++ library.

* checking DESCRIPTION meta-information ... NOTE
Author field differs from that derived from Authors@R
  Author:    'Simon Nolte [aut, cre] (<https://orcid.org/0000-0003-1643-1860>), Benjamin Michaud [cph] (Author of included EZC3D library), German Sport University Cologne [fnd] (0189raq88), Aymeric Stamm [rev] (reviewed the package (v. 0.1.0) for rOpenSci, see <https://github.com/ropensci/software-review/issues/686>), July Pilowsky [rev] (reviewed the package (v. 0.1.0) for rOpenSci, see <https://github.com/ropensci/software-review/issues/686>)'
  Authors@R: 'Simon Nolte [aut, cre] (ORCID: <https://orcid.org/0000-0003-1643-1860>), Benjamin Michaud [cph] (Author of included EZC3D library), German Sport University Cologne [fnd] (ROR: <https://ror.org/0189raq88>), Aymeric Stamm [rev] (reviewed the package (v. 0.1.0) for rOpenSci, see <https://github.com/ropensci/software-review/issues/686>), July Pilowsky [rev] (reviewed the package (v. 0.1.0) for rOpenSci, see <https://github.com/ropensci/software-review/issues/686>)'

I do not use a Author field, but only the Authors@R field following best practices.
