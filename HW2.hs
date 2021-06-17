flipcoin :: String -> Int -> [Int]
flipcoin [] c = [0]
flipcoin [x] c
	| x == 'H' = [0]
	| otherwise = [c + 1, 0]
flipcoin (x:xs) c
	|x == y = flipcoin xs (c + 1)
	|otherwise = [c + 1] ++ flipcoin xs (c + 1)
	where y = head xs

flipCoin :: String -> [Int]
flipCoin xs = flipcoin xs 0
