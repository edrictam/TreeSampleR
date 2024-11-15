test_that("graph non-negative weights fast cover", {
  expect_error(fast_cover(matrix(c(0,1,1,1,0,-1,1,-1,0),3,3),1, 1), "negative")
})

test_that("graph non-negative weights  wilson", {
  expect_error(wilson(matrix(c(0,1,1,1,0,-1,1,-1,0),3,3),1), "negative")
})

test_that("graph non-negative weights  aldous_broder", {
  expect_error(aldous_broder(matrix(c(0,1,1,1,0,-1,1,-1,0),3,3),1), "negative")
})