sorted :: Ord a => [a] -> Bool
sorted [] = True
sorted [_] = True
sorted (x:y:xs) = x <= y && sorted (y:xs) -- list is sorted if first two are in order and rest of list is sorted

-- finnishes as soon as left and right are sorted
mergesort :: Ord a => [a] -> [a]
mergesort [] = []
mergesort xs | sorted xs = xs
             | otherwise = merge (mergesort left) (mergesort right)
             where (left, right) = splitAt (length xs `div` 2) xs -- splitAt returns a tuple of lists 

-- interleave two sorted lists
merge :: Ord a => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys) | x <= y = x : merge xs (y:ys)
                    | otherwise = y : merge (x:xs) ys

-- finnishes as soon as init b is sorted
bubblesort :: Ord a => [a] -> [a]
bubblesort xs | sorted xs = xs
              | otherwise = bubblesort (init b) ++ [last b] -- sort sublist and append largest element
              where b = bubble xs

-- get highest element to end of list
bubble :: Ord a => [a] -> [a]
bubble [] = []
bubble [x] = [x]
bubble (x:y:xs) | x <= y = x : bubble (y:xs)
                | otherwise = y : bubble (x:xs)

main :: IO ()
main = do
  let a = [1, 2, 3, 4, 5]
  let b = [5, 4, 3, 2, 1]
  let c = [1, 3, 2, 5, 4]
  let d = [2,3,2,32,8.2,43,2.01,33,123,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
  print (mergesort a)
  print (mergesort b)
  print (mergesort c)
  print (mergesort d)
  print (bubblesort a)
  print (bubblesort b)
  print (bubblesort c)
  print (bubblesort d)
