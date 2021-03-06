-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List 

solveProblem :: String -> String -> [Int]
solveProblem ips nsstr = 
  let [n, k] = map read . words $ ips
      ns     = map read . words $ nsstr
      nssorts= sort ns
      ls     = foldl' (\((times, num):as) nl -> if (nl == num) then ((times+1, num):as) else ((1, nl): (times, num) : as))   
                      [(1, head nssorts)] $ tail nssorts
      fls    = map snd . filter ((>= k) . fst) $ ls
      ons    = filter (`elem` fls) . nub $ ns
  in  if null ons then [-1] else ons

runTestCase :: Int -> IO ()
runTestCase 0 = return ()
runTestCase n = do
  ips <- getLine
  ns  <- getLine
  let ans = solveProblem ips ns
  putStrLn $ unwords . map show $ ans
  runTestCase (n-1)

main :: IO ()
main = do
  ntc <- getLine
  runTestCase (read ntc)
