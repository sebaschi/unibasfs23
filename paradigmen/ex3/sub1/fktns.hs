factors :: Int -> [Int]
factors n = [x | x <- [1..n], n `mod` x == 0]

swapHeadTail :: [a] -> [a]
swapHeadTail [] = []
swapHeadTail [x] = [x]
swapHeadTail (x:xs) = last xs : init xs ++ [x]

consecutive :: Eq a => [a] -> Bool
consecutive [] = False
consecutive [x] = False
consecutive (x:y:xs) = x == y || consecutive (y:xs)

mean [] = 0
mean xs = if l > 0 then fromIntegral (sum y) / fromIntegral l else 0
    where 
        y = [x | x <- xs, even x]
        l = length y

noOdds :: [Int] -> [Int]
noOdds [] = []
noOdds xs = [x | x <- xs, even x]

tlist :: [(Int,Int)]
tlist = [(x,x^2) | x <- [0..30]]

sharedPrimes :: Int -> Int -> [Int]
sharedPrimes a b = filter prime [x | x<-[2..min a b], x `elem` fctrs a, x `elem` fctrs b]
  where
    prime x = fctrs x ==[1,x]
    fctrs x = [y | y <- [1..x], x `mod` y == 0]

main = do 
  let mix = mean (map (*2) (sharedPrimes (2*11*21) 463))
  let mtest = mean [1,2,3,4,5,6,7,8,9,10]
  let ptest = sharedPrimes (2*11*21) 463
  let ttest = tlist
  let ntest = noOdds [1,2,3,4,5,6,7,8,9,10]
  let ntest2 = noOdds [1,3,5,7,9]
  let ctest = consecutive [1,2,3,4,5,6,7,8,9,10]
  let ctest2 = consecutive [1,2,3,4,5,6,7,8,9,10,10]
  let stest = swapHeadTail [1,2,3,4,5,6,7,8,9,10]
  let ftest = factors 100
  let ftest2 = factors 101
  let ftest3 = factors 11
  print("mean test: " ++ show mtest) 
  print("mix test: " ++ show mix)
  print("prime test: " ++ show ptest)
  print("tlist test: " ++ show ttest)
  print("noOdds test: " ++ show ntest)
  print("noOdds test2: " ++ show ntest2)
  print("consecutive test: " ++ show ctest)
  print("consecutive test2: " ++ show ctest2)
  print("swapHeadTail test: " ++ show stest)
  print("factors test: " ++ show ftest)
  print("factors test2: " ++ show ftest2)
  print("factors test3: " ++ show ftest3)


