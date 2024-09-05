#' Get path to spiro example
#'
#' \code{c3d_example} returns the file path for an example data files within the
#' \code{c3d} package.
#'
#' @return A character vector with the absolute file path of the example
#'   file.
#'
#' @examples
#' c3d_example()
#'
#' @export
c3d_example <- function() {
  system.file("extdata", "example.c3d", package = "c3dr")
}
