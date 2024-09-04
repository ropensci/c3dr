# get test data file
f <- test_path("test_b1.c3d")
# get data
d <- c3d_read(f)

test_that("printing works", {
  expect_snapshot(d)
})
