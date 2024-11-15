test_that("starting point in range fast cover", {
  expect_error(fast_cover(matrix(c(0,1,1,0),2,2),2, 1), "range")
})

test_that("starting point positive fast cover", {
  expect_error(fast_cover(matrix(c(0,1,1,0),2,2),-1, 1), "non-negative")
})

test_that("starting point in range wilson", {
  expect_error(wilson(matrix(c(0,1,1,0),2,2),2), "range")
})

test_that("starting point positive wilson", {
  expect_error(wilson(matrix(c(0,1,1,0),2,2),-1), "non-negative")
})

test_that("starting point in range aldous_broder", {
  expect_error(aldous_broder(matrix(c(0,1,1,0),2,2),2), "range")
})

test_that("starting point positive aldous_broder", {
  expect_error(aldous_broder(matrix(c(0,1,1,0),2,2),-1), "non-negative")
})

