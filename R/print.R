#' Printing c3d objects
#'
#' Printing method for c3d objects
#'
#' @param x A \code{list} of the class \code{c3d} to be printed.
#' @param ... empty argument, currently not used.
#'
#' @return The function prints basic information for the c3d object and returns
#'   it invisibly.
#'
#' @export
print.c3d <- function(x, ...) {
  h <- x$header
  dur <- h$nframes / h$framerate
  afps <- h$analogperframe * h$framerate
  m <- sprintf(
    "A c3d object with\n- %d data points and %d frames\n- %.2f s measurement duration (%d fps)\n- %d analog channels (%d fps)",
    h$npoints, h$nframes, dur, h$framerate, h$nanalogs, afps
  )
  cat(m)
  invisible(x)
}
