module Filmap where
{-
 - Steps to go thorugh when defining a recursive funtion taken from Programming in Haskel, Graham Hutton, Second Edition, Cambridge University Press, 2016
 - Step 1: Define the type
 - Step 2: Enumerate the cases
 - Step 3: Define the simple cases
 - Step 4: Define the other cases
 - Step 5: Generalise and simplify
 -}
my_filter :: (a -> Bool) -> [a] -> [a] --taken from :t my_filter Step 1 but already generalized
my_filter p [] = [] -- predicate applied to empty list is empty list Step 3
my_filter p (x:xs) | p x == True = x : my_filter p xs -- if p x is true keep in list, process rest of list recursively
                | otherwise = my_filter p xs -- if p x is false, ignore and recirsively process rest of list
my_map :: (a -> b) -> [a] -> [b] -- taken from :t my_map Step 1 but already generalized
my_map f [] = [] -- function applied to empty list is empty list
my_map f (x:xs) = f x : my_map f xs -- apply function to x and recursivley build new list 

