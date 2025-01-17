#' Write a c3d file in R
#'
#' \code{c3d_write()} writes a c3d file using the C++ ezc3d library.
#'
#' @param object A c3d object
#' @param file A string with the file path to write to.
#'
#' @examples
#' # read an example file
#' d <- c3d_read(c3d_example())
#'
#' # create a temporary file
#' tmp <- tempfile()
#' on.exit(unlink(tmp))
#'
#' # write c3d file
#' c3d_write(d, tmp)
#'
#' @export

c3d_write <- function(object, file) {
  out <- write(object, file)
  invisible(out)
}
