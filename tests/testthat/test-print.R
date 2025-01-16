# get data
d <- c3d_read(c3d_example())
# copy without force platform data
d_nof <- d
d_nof$parameters$FORCE_PLATFORM$USED <- 0
# copy with different frames per force platform
d_drate <- d
d_drate$forceplatform[[1]]$meta$frames <- 6800


test_that("printing works", {
  expect_snapshot(d)
})

test_that("prints no force platform data if no data is available", {
  expect_snapshot(d_nof)
})

test_that("prints that force platforms have different number of frames", {
  expect_snapshot(d_drate)
})
