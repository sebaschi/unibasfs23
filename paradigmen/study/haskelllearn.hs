--Purpose: to learn haskell

swap :: [a] -> [a]
swap [] = []
swap [x] = [x]
swap (x:xs) = last xs : init xs ++ [x]

consec :: Eq a => [a] -> Bool
consec [] = True
consec [x] = True
consec (x:y:xs) = x == y || consec (y:xs)

divisors :: Int -> [Int]
divisors n = [x | x <- [1..n], n `mod` x == 0]

isEven :: Int -> Bool
isEven n = n `mod` 2 == 0

isPrime :: Int -> Bool
isPrime n = divisors n == [1,n]


noOdds :: [Int] -> [Int]
noOdds [] = []
noOdds xs = filter isEven xs

meanOfEvens :: Fractional b => [Int] -> b
meanOfEvens xs = fromIntegral (sum (noOdds xs)) / fromIntegral (length (noOdds xs))

weirdtupleslist :: [(Int, Int)]
weirdtupleslist = [(x,x^2)| x <-[0..30]]

getPrimeFactors :: Int -> [Int]
getPrimeFactors n = [x | x <- divisors n, isPrime x]

