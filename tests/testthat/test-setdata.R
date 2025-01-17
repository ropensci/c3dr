# example import
d <- c3d_read(c3d_example())

# different data formats
d_wide <- c3d_data(d, "wide")
d_longest <- c3d_data(d, "longest")
# modified data
d_cutdata <- d_wide[-340,-c(163:165)] # remove last points and last frame
d_cut <- c3d_setdata(d, newdata = d_cutdata)
# analog data
a <- c3d_analog(d)
# modified analog data
a_cutdata <- a[-c(3300:3400), -69] # remove last 10 frames and last analog channel
a_cut <- c3d_setdata(d, newanalog = a_cutdata)

test_that("data setting recreates data structure", {
  expect_identical(c3d_setdata(d, newdata = d_wide), d)
  expect_identical(c3d_setdata(d, newdata = d_longest), d)
})

test_that("analog setting recreates data structure", {
  expect_identical(c3d_setdata(d, newanalog = a), d)
})

test_that("point data modification works", {
  # removed point
  expect_equal(d_cut$parameters$POINT$USED, d$parameters$POINT$USED - 1)
  expect_equal(d_cut$header$npoints, d$header$npoints - 1)
  expect_equal(length(d_cut$data[[1]]), length(d$data[[1]]) - 1)
  # removed frame
  expect_equal(d_cut$parameters$POINT$FRAMES, d$parameters$POINT$FRAMES - 1)
  expect_equal(d_cut$header$nframes, d$header$nframes - 1)
  expect_equal(length(d_cut$data), length(d$data) - 1)
})

test_that("analog data modification works", {
  # removed analog channel
  expect_equal(a_cut$parameters$ANALOG$USED, d$parameters$ANALOG$USED - 1)
  expect_equal(a_cut$header$nanalogs, d$header$nanalogs - 1)
  expect_equal(ncol(a_cut$analog[[1]]), ncol(d$analog[[1]]) - 1)
  # removed frames
  expect_equal(length(a_cut$analog), length(d$analog) - 10)
})

test_that("input validation works", {
  expect_error(c3d_setdata(data.frame(), d_long))
  expect_error(c3d_setdata(d, data.frame()))
})

test_that("function without data arguments returns same object", {
  expect_identical(c3d_setdata(d), d)
})

