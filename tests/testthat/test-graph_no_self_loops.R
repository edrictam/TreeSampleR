test_that("graph no self loops fast cover", {
  expect_error(fast_cover(matrix(c(1,1,1,1,0,1,1,1,0),3,3),1, 1), "loop")
})

test_that("graph no self loops wilson", {
  expect_error(wilson(matrix(c(1,1,1,1,0,1,1,1,0),3,3),1), "loop")
})

test_that("graph no self loops aldous_broder", {
  expect_error(aldous_broder(matrix(c(1,1,1,1,0,1,1,1,0),3,3),1), "loop")
})