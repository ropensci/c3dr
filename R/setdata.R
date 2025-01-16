#' Write data to a c3d object
#'
#' Set new data to an existing c3d object
#'
#' @param object A \code{c3d} object to be modified.
#' @param data The new data that should be written to the \code{c3d} object.
#'
#' @return The modified c3d object
#'
#' @export

c3d_setdata <- function(object, data) {

  # input validation
  if (!any(class(object) == "c3d")) stop("'object' needs to be a list of class 'c3d'.")
  if (!any(class(data) != "c3d_data")) stop("'data' needs to be a data.frame of class 'c3d_data'.")

  # convert to long data format if necessary
  frmt <- class(data)[1]
  if (frmt == "c3d_data_longest") {
    d = data # no conversion required
  } else if (frmt == "c3d_data_longer") {
    d = c3d_longest(data, is_wide = FALSE)
  } else if (frmt == "c3d_data_wide") {
    d = c3d_longest(data, is_wide = TRUE)
  } else if (is.null(frmt)) {
    d = c3d_longest(data, is_wide = TRUE)
    message("assumed wide format")
  } else {
    stop("Unknown c3d_data format")
  }

  # write data to list format
  frames <- unique(d$frame)
  points <- unique(d$point)

  out <- vector("list", length(frames))

  # Split data by frames and points for faster access
  data_split <- split(d, list(d$frame, d$point), drop = TRUE)

  for (i in seq_along(frames)) {
    frame <- frames[i]
    frame_data <- data_split[grep(paste0("^", frame, "\\."), names(data_split))]

    out[[i]] <- lapply(points, function(point) {
      point_data <- frame_data[[paste0(frame, ".", point)]]
      if (!is.null(point_data)) {
        c(
          point_data$value[point_data$type == "x"],
          point_data$value[point_data$type == "y"],
          point_data$value[point_data$type == "z"]
        )
      } else {
        c(NA, NA, NA)
      }
    })
  }

  # rewrite point data
  object$data <- out
  # rewrite point labels
  object$parameters$POINT$LABELS <- points
  object$parameters$POINT$USED <- length(points)
  object$labels <- points
  object$header$npoints <- length(points)
  # rewrite frame number
  object$parameters$POINT$FRAMES <- length(frames)
  object$header$nframes <- length(frames)
  object
}


