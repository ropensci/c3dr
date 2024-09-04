# get test data file
f <- test_path("test_b1.c3d")
# get data
d <- c3d_read(f)
d_wide <- c3d_data(d)
d_long <- c3d_data(d, format = "long")
d_longest <- c3d_data(d, format = "longest")

test_that("wide data retrieval works", {
  # dimensions
  expect_equal(dim(d_wide), c(d$header$nframes, d$header$npoints * 3))
  # data
  expect_equal(d_wide[2,3], d$data[[2]][[1]][[3]])
  # header labels
  expect_equal(colnames(d_wide)[[1]], paste0(d$labels[[1]],"_x"))
})

test_that("long data retrieval works", {
  # dimensions
  expect_equal(dim(d_long), c(d$header$nframes * 3, d$header$npoints + 2))
  # data
  expect_equal(d_long[3,3], d$data[[1]][[1]][[3]])
  # header
  expect_equal(colnames(d_long)[-c(1,2)], d$labels)
})

test_that("longest data retrieval works", {
  # dimensions
  expect_equal(nrow(d_longest), d$header$nframes * d$header$npoints * 3)
  # data
  expect_equal(d_longest$value[4], d$data[[1]][[2]][[1]])
})
