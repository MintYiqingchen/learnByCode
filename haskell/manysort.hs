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
data BinTree a = Nil|Node{ value::a, left::BinTree a, right::BinTree a}
        deriving(Show)

-- accept type constructor rather than value constructor
instance Functor BinTree where
    fmap func Nil = Nil
    fmap func treeA = Node (func $ value treeA) (fmap func $ left treeA) (fmap func $ right treeA)

listToTree::(Ord a)=>[a]->BinTree a
listToTree [] = Nil
listToTree (x:xs) = let 
    ltx = [t|t<-xs, t<=x]
    gtx = [t|t<-xs, t>x]
    in Node x (listToTree ltx) (listToTree gtx)

insertToTree::(Ord a)=>a->BinTree a->BinTree a
insertToTree val Nil = Node val Nil Nil
insertToTree val tree = if val<=value tree
    then Node (value tree) (insertToTree val $ left tree) (right tree)
    else Node (value tree) (left tree) (insertToTree val $ right tree)

searchInTree::(Ord a)=>a->BinTree a->Bool
searchInTree val Nil = False
searchInTree val tree -- the way of if else if else
    |val==value tree = True
    |val < value tree = (searchInTree val $ left tree) 
    |val > value tree = (searchInTree val $ right tree)

deleteFromTree::(Ord a)=>a->BinTree a->(BinTree a, Bool)
deleteFromTree val Nil = (Nil, False)
deleteFromTree val tree 
    |val==value tree= _handle tree
    |val < value tree= let (new_tree, b)=deleteFromTree val $ left tree in 
        (Node (value tree) new_tree (right tree), b)
    |val > value tree= let (new_tree, b)=deleteFromTree val $ right tree in 
        (Node (value tree) (left tree) new_tree, b)
    where
        _handle (Node v Nil Nil) = (Nil, True)
        _handle (Node v Nil right) = (right, True)
        _handle (Node v left Nil) = (left, True)
        _handle subroot = let (succ_val, new_tree) = _succ (right subroot)-- 使用直接后继
            in (Node succ_val (left subroot) new_tree, True)
        
        _succ (Node v Nil right) = (v, right)
        _succ (Node v ll rr) = let (res_v, new_tree)=_succ ll in (res_v, Node v new_tree rr)