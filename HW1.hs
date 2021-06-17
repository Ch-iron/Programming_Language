factors :: Int -> [Int]
factors n = [x|x <- [1..n], n `mod` x == 0]

prime :: Int -> Bool
prime n = factors n == [1, n]

findingPrimes :: Int -> Int -> [Int]
findingPrimes x y = take y [p|p <- [x..], prime p == True]
