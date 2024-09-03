#' Get point data from a c3d file
#'
#' Get the point data in a data.frame
#'
#' @param x A c3d object, as imported by \code{c3d_read()}.
#' @param format Either "wide" (default) or "long" to determine the format of the
#'   resulting data frame. Long format has three columns per point (x,y,z),
#'   short format has three rows per frame per point (x,y,z).
#'
#' @return A data.frame with the c3d point data. The structure of the data frame
#'   depends on the 'format' argument.
#' @export

c3d_data <- function(x, format = "wide") {
  # change data format from nested list to data.frame
  out <- as.data.frame(
    matrix(unlist(x$data), nrow = x$header$nframes, byrow = TRUE)
  )
  # get label names
  colnames(out) <- paste0(rep(x$labels, each = 3), c("_x", "_y", "_z"))
  if (format == "wide") {
    out
  } else if (format == "long") {
    c3d_longer(out)
  } else {
    stop("'format' argument in c3d_data() must be either 'wide' or 'long'")
  }
}

#' Convert wide to long data for c3d points
#'
#' Convert from wide representation of data (3 columns per point) to long data
#' (1 column per point) in c3d point data
#'
#' @param x A data.frame with c3d point data with three columns (x, y, z) per
#'   point.
#'
#' @return A data.frame with one column per point. It has n*3 rows
#'   and k columns, with n as the number of recorded frames and k as the
#'   number of recorded points.
#' @export
c3d_longer <- function(x) {
  # get new column names
  old_names <- colnames(x)[0:(ncol(x) / 3 - 1) * 3 + 1]
  new_names <- sub("_([xyz])$", "", old_names)

  # get split factors for reshape
  splt <- split(seq_len(ncol(x)), rep(1:(ncol(x) / 3), each = 3))
  r <- stats::reshape(
    data = x,
    varying = splt,
    v.names = new_names,
    direction = "long",
    timevar = "type",
    times = c("x","y","z"),
    idvar = "frame"
  )
  # reorder columns
  r <- r[,c(ncol(r), seq_along(r)[-ncol(r)])]
  # reorder rows
  r[order(r$frame, r$type),]
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
