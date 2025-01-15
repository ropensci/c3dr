d <- c3d_read(c3d_example())

# create temporary file
tmp <- tempfile()
on.exit(unlink(tmp))

# write c3d file
c3d_write(tmp, d)
# reread file
n <- c3d_read(tmp)

test_that("reimport works", {
  expect_equal(n$header, d$header) # same header
  expect_equal(n$labels, d$labels) # same labels
  expect_equal(n$alabels, d$alabels) # same analog labels
  # parameters are different
  expect_equal(n$data, d$data) # same data
  expect_equal(n$analog, d$analog) # same analogs
  # force platform data is not exported at the moment
})
