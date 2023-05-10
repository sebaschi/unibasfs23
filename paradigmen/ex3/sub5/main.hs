import Filmap
weight :: [Int] -- define list of weights
weight = [97, 95, 53, 40, 46, 73, 68, 67, 69, 62, 99, 89, 77, 94, 100, 63, 75, 44, 81, 96, 63, 99, 64, 88, 77, 104, 50, 97, 81, 84, 66, 78, 72, 93, 42, 93, 94, 58, 48, 94, 71, 47, 49, 57, 93, 71, 106, 63, 81, 95]

height :: [Int] -- define list of heights
height = [172, 195, 157, 144, 165, 191, 183, 194, 185, 194, 183, 194, 186, 152, 156, 163, 179, 164, 186, 181, 158, 181, 155, 197, 150, 166, 179, 153, 142, 154, 162, 156, 149, 166, 148, 195, 198, 152, 167, 197, 157, 144, 147, 159, 198, 149, 179, 183, 156, 175, 157]

bmi :: (Real a, Real b, Fractional c) => a -> b -> c -- funciton to calculate bmi given weight and height
bmi w h = realToFrac w / (realToFrac (h * h)  / 10000)

pairsList :: [(Int,Int)] -- weight height pairs
pairsList = zip weight height

bmiList :: [Double] -- list of bmi's
bmiList = my_map (uncurry bmi) pairsList -- uncurry bmi to take a tuple as an argument since zip returns a list of tuples

withIndex :: [Double] -> [(Int,Double)] -- function to add index to list
withIndex xs = zip [1..] xs

bmiListWithIndex :: [(Int,Double)] -- list of bmi's with index
bmiListWithIndex = withIndex bmiList

overUnderList :: [(Int,Double)] -- list of bmi's with index and over/underweight 
overUnderList = my_filter (\(i,b) -> b > 25 || b < 18.5) bmiListWithIndex

mean :: (Real a, Fractional b) => [a] -> b -- function to calculate mean of list
mean [] = 0
mean xs = realToFrac (sum xs) / fromIntegral (length xs)

main = do
 print overUnderList
 let meanH = mean height
 let meanW = mean weight
 let meanB = mean bmiList
 print ("Mean height: " ++ show meanH)
 print ("Mean weight: " ++ show meanW)
 print ("Mean bmi: " ++ show meanB)
