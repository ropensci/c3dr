#' @keywords internal
#'
#' @details
#' # Main functions:
#' * Use [c3d_read()] for the import of c3d data.
#' * Use [c3d_data()] and [c3d_analog()] for retrieving the point and the analog
#'   data as a data frame.
#' * Use [c3d_write()] to write a c3d object to a c3d file.
"_PACKAGE"


## usethis namespace: start
#' @importFrom Rcpp sourceCpp
#' @useDynLib c3dr, .registration = TRUE
## usethis namespace: end
NULL
