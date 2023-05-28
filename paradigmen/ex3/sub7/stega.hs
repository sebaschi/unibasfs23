import Data.Char ( chr )
import Data.Bits 

--function to convert an Integerlist to a list of chars
getAsciiChars :: [Int] -> [Char]
getAsciiChars = foldr (\ x -> (++) [chr x]) []

-- Did this below first, but VS Code told me that the code above is a better solution
--getAsciiChars :: [Int] -> [Char]
--getAsciiChars [] = []
--getAsciiChars (x:rest) = [chr x] ++ getAsciiChars rest

--bitmask to store only the first 4 bits
bitmask :: [Int] -> [Int]
bitmask rest = foldr (\ x -> (++) [(x .&. 0b1111)]) [] rest

-- bitmask [] = []
-- bitmask (x:rest) = [(x .&. 0b1111)] ++ bitmask rest

--calculates new integer value from the three list
calcInt :: [Int] -> [Int] -> [Int] -> [Int]
calcInt x y z = 
            let
                triples = zip3 x y z
                list = map (\(a,b,c) -> a* (5^2) + b*5 + c) triples
            in
                list

--final function for exercise b
uncover :: [Int] -> [Int] -> [Int] -> [Char]
uncover x y z = 
        let 
            xbit = bitmask x
            ybit = bitmask y
            zbit = bitmask z
            list = calcInt xbit ybit zbit
        in
            getAsciiChars list

main :: IO ()
main = do 
    -- "Hallo"  as Integerlist to test getAsciiChars
    print (getAsciiChars [72, 65, 76, 76, 79])
    -- test bitmask with example from ex. sheet
    print (bitmask  [67])
    -- test uncover method with example from ex sheet
    print (uncover [66] [7] [17])

    let x = [18, 68, 36, 36, 20, 67, 36, 20, 36, 35, 68, 20, 20, 36, 68, 33, 65, 20, 20, 35, 36, 17, 36,
            65, 36, 17, 68, 20, 68, 33, 33, 19, 20, 35, 67, 33, 35, 18, 68, 20, 36, 68, 19, 36, 65, 68, 36,
            20, 68, 35, 20, 20, 35, 17, 36, 68, 17, 68, 36, 33, 33]
    let y = [19, 34, 66, 32, 34, 20, 67, 19, 65, 36, 35, 33, 34, 66, 19, 19, 17, 18, 34, 22, 35, 65, 34,
            36, 19, 65, 18, 34, 64, 65, 17, 68, 19, 33, 68, 33, 64, 64, 18, 36, 33, 18, 71, 16, 65, 32, 36,
            16, 66, 36, 17, 35, 37, 65, 19, 66, 17, 64, 34, 33, 33]
    let z = [34, 65, 32, 67, 20, 66, 33, 66, 35, 18, 65, 16, 17, 32, 64, 36, 66, 33, 16, 35, 70, 18, 32,
            35, 17, 66, 65, 16, 33, 34, 18, 67, 18, 36, 64, 34, 66, 66, 16, 33, 20, 65, 20, 33, 34, 65, 64,
            65, 20, 20, 32, 16, 65, 18, 33, 33, 66, 35, 17, 19, 19]
    print "Hidden Message: "
    print (uncover x y z)
