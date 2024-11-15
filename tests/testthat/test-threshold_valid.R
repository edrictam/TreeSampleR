test_that("threshold valid", {
  expect_error(fast_cover(matrix(c(0,1,1,0),2,2),1, -1), "non-negative")
})
