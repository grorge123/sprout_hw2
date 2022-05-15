# sprout_hw2

## source.cpp：
原始檔。資料來源：https://kickingbrains.wordpress.com/2016/08/03/space-shooter-a-simple-c-game-for-windows/

玩法：玩家是畫面下方的飛行船，可以用鍵盤操控上下左右＆發射子彈。子彈每射中一顆隕石會拿10分，玩家拿到100分就贏了。玩家共有3條命，一條命包含5個energy（換句話說，玩家總共有15個energy），飛行船每被隕石打到一次會扣一個energy，所有energy都用完（也就是被隕石打到15次）就輸了。

缺點：只能在Windows上面跑，其他地方都不行。（因為<conio.h>和<windows.h>只有在Windows才能用。）

## hw.cpp：
從source.cpp去修改出來的檔案內容（主要就是把和<conio.h>和<windows.h>有關的東西都拔掉）。在mac上能跑起來，但不確定在其他地方能不能跑。

玩法：代定。

目前：和source.cpp的規則一樣，只是玩家的行為（上下左右、發射子彈）是用我隨便寫的random function做的（詳見HowToMove和isshoot）。到時候也許可以讓學員去用更好的方式去實作這些 function。因為不能用鍵盤操控，所以執行起來會是全自動的。

努力方向：
  盡快想出規則
  找到可以用鍵盤操作，且適用於Windows以外的地方的方法。
  
