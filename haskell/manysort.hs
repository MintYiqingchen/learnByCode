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