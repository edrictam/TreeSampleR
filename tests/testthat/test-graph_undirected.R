test_that("graph undirected fast cover", {
  expect_error(fast_cover(matrix(c(0,2,1,1,0,1,1,1,0),3,3),1, 1), "symmetric")
})

test_that("graph undirected wilson", {
  expect_error(wilson(matrix(c(0,2,1,1,0,1,1,1,0),3,3),1), "symmetric")
})

test_that("graph undirected aldous_broder", {
  expect_error(aldous_broder(matrix(c(0,2,1,1,0,1,1,1,0),3,3),1), "symmetric")
})