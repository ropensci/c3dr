#' Write a c3d file in R
#'
#' \code{c3d_write()} writes a c3d file using the C++ ezc3d library.
#'
#' @param file A string with the file path to write to.
#' @param object A c3d object
#'
#' @export

c3d_write <- function(file, object) {
  out <- write(file, object)
  invisible(out)
}
