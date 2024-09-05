# get data
d <- c3d_read(c3d_example())

test_that("printing works", {
  expect_snapshot(d)
})
