#' Get point data from a c3d file
#'
#' Get the point data in a data.frame
#'
#' @param x A c3d object, as imported by \code{c3d_read()}.
#'
#' @return A data.frame with three columns (x, y, z) per point. It has n rows
#'   and k*3 columns, with n as the number of recorded frames and k as the
#'   number of recorded points.
#' @export

c3d_data <- function(x) {
  # change data format from nested list to data.frame
  out <- as.data.frame(
    matrix(unlist(x$data), nrow = x$header$nframes, byrow = TRUE)
  )
  # get label names
  colnames(out) <- paste0(rep(x$labels, each = 3), c("_x", "_y", "_z"))
  out
}

#' Get analog data from a c3d file
#'
#' Get the analog data in a data.frame
#'
#' @param x A c3d object, as imported by \code{c3d_read()}.
#'
#' @return A data.frame with with n rows and m columns, where n is the number of
#'   frames recorded times the number of analog subframes per frame, and m as
#'   the number of recorded analog channels.
#' @export
c3d_analog <- function(x) {
  # change data format from list of matrices to data.frame
  out <- as.data.frame(do.call(rbind, x$analog))
  colnames(out) <- x$alabels
  out
}
