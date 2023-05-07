prdct [] = 1
prdct (x:xs) = x * prdct xs

n = a `div` length xs
    where
        a = 10
        xs = [1,2,3,4,5]
    
infixl 6 +++

(+++) :: Int -> Int -> Int
a +++ b = a + 2*b

infixr 7 ***
(***) :: Int -> Int -> Int
a *** b = a - 4*b

odds n = map (\x -> x*2 + 1) [0..n-1]

primes :: Int -> [Int]
primes n | n < 2 = []
         | otherwise = [x | x <- [2..n], y <- [2..x-1], x `mod` y /= 0]
