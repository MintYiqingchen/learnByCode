qsort::(Ord a)=>[a]->[a]
qsort []=[]
qsort (x:xs) = let
    ltx = [t|t<-xs, t<=x]
    gtx = [t|t<-xs, t>x]
    in (qsort ltx)++[x]++(qsort gtx)

mergesort::(Ord a)=>[a]->[a]
mergesort [x1]=[x1]
mergesort lst= let 
    merge s1 []=s1
    merge [] s2=s2
    merge (s1_0:s1) (s2_0:s2)= if s1_0<=s2_0
                                then [s1_0,s2_0]++(merge s1 s2)
                                else [s2_0,s1_0]++(merge s1 s2)
    (s1,s2) = splitAt ((length lst) `div` 2) lst
    in merge (mergesort s1) (mergesort s2)

-- binary Tree
class Tree t where -- here, a is a data, but not specific data
    height::t a->Int
    infixWalk::t a->[a]


-- do not use record if there are alternative value constructor
data BinTree a = Nil|Node a (BinTree a) (BinTree a)
        deriving(Show)

-- accept type constructor rather than value constructor
instance Functor BinTree where
    fmap func Nil = Nil
    fmap func (Node value left right) = Node (func value) (fmap func left) (fmap func right)
instance Tree BinTree where
    height Nil = 0
    height (Node value left right) = max (height left) (height right) + 1
    infixWalk Nil = []
    infixWalk (Node value left right) = (infixWalk left) ++ [value] ++ (infixWalk right)

listToTree::(Ord a)=>[a]->BinTree a
listToTree [] = Nil
listToTree (x:xs) = let 
    ltx = [t|t<-xs, t<=x]
    gtx = [t|t<-xs, t>x]
    in Node x (listToTree ltx) (listToTree gtx)

insertToTree::(Ord a)=>a->BinTree a->BinTree a
insertToTree val Nil = Node val Nil Nil
insertToTree val (Node value left right) = if val<=value
    then Node value (insertToTree val left) right
    else Node value left (insertToTree val right)

searchInTree::(Ord a)=>a->BinTree a->Bool
searchInTree val Nil = False
searchInTree val (Node value left right)-- the way of if else if else
    |val==value = True
    |val < value = (searchInTree val left) 
    |val > value = (searchInTree val right)

deleteFromTree::(Ord a)=>a->BinTree a->(BinTree a, Bool)
deleteFromTree val Nil = (Nil, False)
deleteFromTree val tree@(Node value left right)
    |val == value = _handle tree
    |val < value = let (new_tree, b)=deleteFromTree val left in 
        (Node value new_tree right, b)
    |val > value = let (new_tree, b)=deleteFromTree val right in 
        (Node value left new_tree, b)
    where
        _handle (Node v Nil Nil) = (Nil, True)
        _handle (Node v Nil right) = (right, True)
        _handle (Node v left Nil) = (left, True)
        _handle (Node v left right) = let (succ_val, new_tree) = _succ right-- 使用直接后继
            in (Node succ_val left new_tree, True)
        
        _succ (Node v Nil right) = (v, right)
        _succ (Node v ll rr) = let (res_v, new_tree)=_succ ll in (res_v, Node v new_tree rr)