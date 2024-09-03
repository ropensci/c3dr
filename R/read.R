#' Read a c3d file in R
#'
#' \code{c3d_read()} imports a c3d file using the C++ ezc3d library.
#'
#' @param file A string with the path of a c3d file.
#'
#' @return A list of class c3d.
#' @export

c3d_read <- function(file) {
  out <- read(file)
  class(out) <- c("c3d", "list")
  out
}
