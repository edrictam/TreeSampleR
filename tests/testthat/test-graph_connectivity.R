test_that("graph connectivity fast cover", {
  expect_error(fast_cover(matrix(c(0,0,0,0),2,2),1, 1), "connected")
})

test_that("graph connectivity  wilson", {
  expect_error(wilson(matrix(c(0,0,0,0),2,2),1), "connected")
})

test_that("graph connectivity  aldous_broder", {
  expect_error(aldous_broder(matrix(c(0,0,0,0),2,2),1), "connected")
})