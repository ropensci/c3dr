# get data
d <- c3d_read(c3d_example())

test_that("import returns c3d class list", {
  expect_type(d, "list")
  expect_s3_class(d, c("c3d", "list"))
})

test_that("header import works", {
  expect_type(d$header, "list")
})

test_that("data import works", {
  # correct number of data frames
  expect_identical(length(d$data), d$header$nframes)
  # correct number of data points
  expect_identical(length(d$data[[1]]), d$header$npoints)
  # correct number of dimensions
  expect_identical(length(d$data[[1]][[1]]), 3L)

  # correct first data record
  expect_equal(
    d$data[[1]][[1]], c(514.7515, 426.1067, 1111.9399),
    tolerance = 0.001
  )
})

test_that("label import works", {
  expect_identical(length(d$labels), d$header$npoints)
})

test_that("parameter import works", {
  expect_snapshot(d$parameters)
})
