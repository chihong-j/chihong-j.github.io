主題簡介：

我做的是todo list，之前看到老師demo過去學生做的作品得到靈感，自己平常是iphone的用戶，我覺得iphone的todo list很方便，因此我這次模仿iphone的todo list。

使用者如何使用我的網站：

新增：當你有待辦事項的時候，點一下最下面那行，直接輸入，然後滑鼠點一下旁邊(不是按enter)，就可以新增一項了。

更新：點擊兩下上面已新增過的就可以直接更改。

顯示已完成：當你做完這件事之後，可以點一下左邊的圓圈，他就會變顏色，並且出現一點橫線代表刪除的意思。(跟iphone的功能很像，點一下圓圈只是顯示已完成並沒有刪除)

刪除：按一下右邊的小叉叉，就會跳出一個視窗問你是不是要刪除，點確定或取消。

排序：點著某一個，然後上下移動，就可以跟其他行交換順序。

你在這次專題中做了什麼，使用了什麼技術:

整個todo list是一個ul，每一行都是一個li
使用handlebars的技術來製作模板(需要下載handlebars的js檔，網址：https://handlebarsjs.com/ )，我的模板是todo list之中的一個li

新增的時候，點一下最下面那行，就會focus，並且變成可編輯

新增的時候，打完文字，點一下旁邊就可以新增了，不是按enter，這是blur的功能

新增文字的時候，我用了trim的功能，因此不可以只輸入空白(只輸入空白的話再點一下旁邊不會多新增一行，同時會取消focus)，另外也會去除文字最前面的所有空白

新增之後，你輸入的文字會丟進去我用handlebars做的模板，然後就會多一行可以新增的空白行

更新的時候，要點兩下(點一下會沒反應，跟新增的點一下不同)，改完文字之後，一樣是blur的功能就會更改內容了

刪除的時候，用jquery搭配javascript的語法，會跳出一個視窗顯示"Do you want to delete?"，然後可以按確定或取消

顯示已完成，當你點一下左邊的圓圈就會改變他的css，所以會呈現出不同的樣子，再點一次就會變回來

排序，我到jqueryui網站上下載延伸的功能(需要下載兩個js檔，網址：https://jqueryui.com/sortable/ )，然後就可以直接使用他的sortable功能

