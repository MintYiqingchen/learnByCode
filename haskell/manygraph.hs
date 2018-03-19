import Control.Monad
import Data.Array
type Graph = Array (Int,Int) Int

getInput::Int->IO [String]
getInput n = sequence $ take n (repeat getLine)

createGraph::Int->[String]->Graph
createGraph n strAdj =
    let -- lg: initial graph 
        lg = array ((1,1),(n,n)) [((a,b),0)|a<-[1..n], b<-[1..n]]
        tagGraph graph ll= 
            let 
                z::[Int]
                z=map read (words ll) in graph//[((z!!0,z!!1), z!!2)]
    in foldl tagGraph lg strAdj 

main = do
    [n, cities] <- sequence $ [getLine, getLine]
    info <- getInput (read n)
    let graph = createGraph (read cities) info
    print graph