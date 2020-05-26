import Control.Monad
import Data.Array
import Data.List (find)
type Graph = Array (Int,Int) Int
type Path = [(Int,Int)]

shape::Graph->(Int,Int)
shape g = let (u,l)=bounds g in (abs (fst l - fst u + 1), abs (snd l - snd u + 1))

rows::Graph->Int
rows g = (fst.shape) g

getInput::Int->IO [String]
getInput n = sequence $ take n (repeat getLine)

createGraph::Int->[String]->Graph
createGraph n strAdj =
    let -- lg: initial graph 
        lg = array ((1,1),(n,n)) [((a,b),9999)|a<-[1..n], b<-[1..n]]
        tagGraph graph ll= 
            let 
                z::[Int]
                z=map read (words ll) in graph//[((z!!0,z!!1), z!!2)]
    in foldl tagGraph lg strAdj 

getNextNode::Graph->[Bool]->[Int]->Int->Maybe Int->Path
getNextNode _ _ _ last Nothing = [(last, -1)]
getNextNode g visited cango last (Just start) = 
    let 
        ifReplace i = visited!!(i-1) || cango!!(i-1) < g!(start, i) + cango!!(start-1)
        new_cango = map (\i->if ifReplace i then cango!!(i-1) else g!(start, i) + cango!!(start-1)) [1..rows g]
        new_visited = map (\(a,b)->if a==start then True else b) $ zip [1..] visited
        now = (Just (+1)) <*> find (\i->new_cango!!i==minimum new_cango && new_visited!!i==False) [0..(rows g)-1]
    in (start,last):getNextNode g new_visited new_cango start now
dijkstra::Graph->Int->Path
dijkstra graph start = let
        nodeNum = rows graph
        cango = [graph ! (start, i)| i <- [1..nodeNum]]
        visited = [if i==start then True else False| i <- [1..nodeNum] ]
        now = (Just (+1)) <*> find (\i->cango!!i==minimum cango && visited!!i==False) [0..nodeNum-1]
    in (start,0):getNextNode graph visited cango start now 

main = do
    [n, cities] <- sequence $ [getLine, getLine]
    info <- getInput (read n)
    let graph = createGraph (read cities) info
    let path = dijkstra graph 1
    print path