## Data Verification with Merkle Tree
### Data Merkle Tree
在分離式系統中傳輸較大的檔案時，檔案通常會被分割為多個較小的區塊傳送，然而在傳輸過程中資料時常會受到損壞，對每個區塊進行 Hash 處理並建構 Merkle Tree，其中每個 leaf node 為各資料區塊的 hash 值，其他 node 的值則是其 child node 的 hash 值，傳輸完成後比較資料傳輸前後的 Merkle Tree，可以得知資料內容是否一致，從而快速判斷資料是否在傳輸過程損壞以及具體的損壞區塊。

### 程式目的
模擬資料傳輸時使用 Merkle Tree 儲存並偵測錯誤，輸入多個字串以及最大字串長度，與原始資料 Merkle Tree 的 hash 值比較而找出產生錯誤的區塊，最後輸出錯誤的區塊總數並列出錯誤區塊內容。

### 實作方法
輸入字串資料總數、多個字串資料與最大字串長度後，`ConstructTree`函式建構出該筆資料的 Merkle Tree，若遇到樹不平衡的情況則複製 sibling node 以進行 hash 處理，之後進入 Query 互動階段，先檢查 root，使用`printf`與`scanf`向資料傳送端提問並取得原始資料的正確 hash 值，若 hash 值不同則加入 queue 中，再從 queue 中取出新節點檢查其 child node，重複動作直到清空 queue，此時已檢查完兩者 Merkle Tree 所有相異的 node，即可顯示產生錯誤的區塊數量以及錯誤的字串資料。

### 字串資料輸入

<li>格式</li>

```bash
#Strings    StrMaxLen
    // Strings 為字串資料的區塊總數，StrMaxLen 為所有區塊中最大字元
String1
String2
...
    // 每行輸入各區塊的字串資料
``` 

<li>範例</li>

```bash
3 6
abc
deeffg
xxYyz
```

### 字串資料輸出
<li>格式</li>

```bash
2    #IncorrectStrings
    // "2"表示該輸出為回答輸出，接著輸入錯誤區塊的總數
IncorrectString1
IncorrectString2
...
    // 每行輸入各錯誤區塊的字串資料
```

<li>範例</li>

```bash
2 3
aaa
bbbbbb
ccccc
```

### Query 輸出
<br/>
<div align = "center">
<image src = "sample_graph.png">

Level 與 NodeIndex（LevelNum）編號方式如圖所示
</div>
<br/>
<li>格式</li>

```bash
1    Level    NodeIndex
    // "1"表示該輸出為 Query，接著輸入欲詢問 hash 值節點之 level 值與 NodeIndex（LevelNum）
``` 

<li>範例</li>

```bash
1 0 0
```

### Query 輸入

<li>格式</li>

```bash
MasterHashValue
    // 所詢問的節點原 hash 值
```  
<li>範例</li>

```bash
-620310961
```

### 工具準備
<li>安裝 gcc：</li>

```bash
sudo apt-get install gcc
```
查看是否已安裝 gcc：`gcc --version`

### 編譯
```bash
gcc MerkleTree.c -o MerkleTree
```

### 執行
```bash
./MerkleTree
```
