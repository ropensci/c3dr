#' Get point data from a c3d file
#'
#' Get the point data in a data.frame
#'
#' @param x A c3d object, as imported by \code{c3d_read()}.
#'
#' @return A data.frame with three columns (x, y, z) per point.
#' @export

c3d_data <- function(x) {
  # change data format from nested list to matrix
  out <- as.data.frame(
    matrix(unlist(x$data), nrow = x$header$nframes, byrow = TRUE)
  )
  # get label names
  colnames(out) <- paste0(rep(x$labels, each = 3), c("_x", "_y", "_z"))
  out
}
