d <- c3d_read(c3d_example())
d_wide <- c3d_data(d, "wide")
d_longest <- c3d_data(d, "longest")
d_cut <- d_wide[-340,-c(163:165)]
cut <- c3d_setdata(d, d_cut)


test_that("data setting recreates data structure", {
  expect_identical(c3d_setdata(d, d_wide), d)
  expect_identical(c3d_setdata(d, d_longest), d)
})

test_that("data modification works", {
  # removed point
  expect_equal(cut$parameters$POINT$USED, d$parameters$POINT$USED - 1)
  expect_equal(cut$header$npoints, d$header$npoints - 1)
  expect_equal(length(cut$data[[1]]), length(d$data[[1]]) - 1)
  # removed frame
  expect_equal(cut$parameters$POINT$FRAMES, d$parameters$POINT$FRAMES - 1)
  expect_equal(cut$header$nframes, d$header$nframes - 1)
  expect_equal(length(cut$data), length(d$data) - 1)
})

test_that("input validation works", {
  expect_error(c3d_setdata(data.frame(), d_long))
  expect_error(c3d_setdata(d, data.frame()))
})


