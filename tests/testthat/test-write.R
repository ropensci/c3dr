d <- c3d_read(c3d_example())

# create temporary file
tmp <- tempfile()
on.exit(unlink(tmp))

# write c3d file
c3d_write(d, tmp)
# reread file
n <- c3d_read(tmp)

test_that("reimport works", {
  expect_identical(n$header, d$header) # same header
  expect_identical(n$labels, d$labels) # same labels
  expect_identical(n$alabels, d$alabels) # same analog labels
  # parameters are different
  expect_equal(n$data, d$data, tolerance = 0.0001) # same data
  expect_equal(n$residuals, d$residuals, tolerance = 0.0001)
  expect_equal(n$analog, d$analog, tolerance = 0.0001) # same analogs
  # force platform data is not exported at the moment
})

test_that("c3dr parameter export works", {
  expect_identical(n$parameter$EZC3D$BINDING, "c3dr")
  expect_identical(n$parameter$EZC3D$C3DR_VERSION, as.character(packageVersion("c3dr")))
})
