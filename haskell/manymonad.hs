import Control.Monad

solveRPN::String->Maybe Double
solveRPN strExp = (foldM foldFunc [] (words strExp)) >>= getResult
    where
        foldFunc (x:y:xs) "+"=Just $ (x+y):xs
        foldFunc (x:y:xs) "-"=Just $ (y-x):xs
        foldFunc (x:y:xs) "*"=Just $ (x*y):xs
        foldFunc xs str = case reads str::[(Double,String)] of
            [(x,"")] -> Just $ x:xs
            _ -> Nothing

        getResult [x] = Just x
        getResult _ = Nothing
