foo :: (Bool,Int,Int) -> Int
foo (x,y,z)
  | x = y + z
  | otherwise = y - z

foo_curried :: Bool -> Int -> Int -> Int
foo_curried = \x -> (if x then \y -> \z -> y + z else \y -> \z -> y - z)

main = do
  print $ foo (True, 1, 2)
  print $ foo_curried True 1 2
  print $ foo_curried False 1 2
  print $ foo (False, 5, 6)
  print $ foo_curried False 5 6
  print $ foo (True, 5, 6)
  print $ foo_curried True 5 6
 

