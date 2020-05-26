import Control.Monad
import Data.Char

-- not need bracket behind do
main = forever $ do
    putStrLn "Please input your text:"
    x<-getLine
    putStrLn (map toUpper x)
        