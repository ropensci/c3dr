#' @keywords internal
#'
#' @section Main functions:
#' \itemize{
#'   \item Use \code{\link{c3d_read}} for the import of c3d data.
#'   \item Use \code{\link{c3d_data}} and \code{\link{c3d_analog}} for assessing
#'   the point and the analog data as a data frame.
#'   \item Use \code{\link{c3d_write}} to write a c3d object to a c3d file.
#' }
"_PACKAGE"


## usethis namespace: start
#' @importFrom Rcpp sourceCpp
#' @useDynLib c3dr, .registration = TRUE
## usethis namespace: end
NULL
