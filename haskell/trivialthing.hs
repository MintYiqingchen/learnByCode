import System.IO
import System.Environment(getArgs)
import System.Directory
import Control.Exception(bracketOnError)

dispatch::String->([String]->IO ())
dispatch "add" = addItems
dispatch "list" = listItems
dispatch "delete" = deleteItems
dispatch _ = noCommand

noCommand::[String]->IO()
noCommand _ = putStrLn "Sorry, there is no corresponding function yet."

addItems::[String]->IO()
addItems [filePath, item] = do
    putStrLn $ "Add Item - "++item
    appendFile filePath $ item++"\n"
addItems others = putStrLn $ "The argument amount is not consistent" ++ (show others)

listItems::[String]->IO()
listItems [filePath] = do
    contents <- readFile filePath
    mapM_ putStrLn (zipWith (\n item->(show n) ++ "-" ++ item) [1..] $ lines contents)

deleteItems::[String]->IO()
deleteItems [filePath, idx] = do
    contents <- readFile filePath
    let item = (lines contents) !! ((read idx)-1)
    putStrLn ("Item \""++item++"\" is deleted")
    let newContents = [x|x<-(lines contents), x/=item]
    bracketOnError
        (openTempFile "." "todo.tmp") 
        (\a->do
            let (tmpFile, handle) = a
            hClose handle
            removeFile tmpFile
        )
        (\a->do
            let (tmpFile, handle) = a
            hPutStr handle (unlines newContents)
            hClose handle
            renameFile tmpFile filePath
            )

main = do
    args <- getArgs
    if (length args)<2
        then putStrLn "The number of arguments doesn't valid"
        else 
            let (ops: remainArg)=args
                func = dispatch ops in func remainArg