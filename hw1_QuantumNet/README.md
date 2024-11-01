## Entanglement Routing in Quantum Networks

### Entanglement Swapping
首先在粒子 A, B 與 C 之間有兩個獨立的糾纏，其中 A 與 B 糾纏，B 與 C 糾纏，之後進行糾纏交換，使 A 和 C 這兩個之前沒有直接糾纏的粒子，通過 B 間接地變成糾纏態。  
因此共需要 （A,B）、（B,C）兩條 quantum channel 與 A、C 各一個 quantum memory 與 B 兩個 quantum memory。

### 程式目的
模擬量子糾纏網路，根據所給予的一串需求輸入，計算網路圖 G(V,E) 的資源最多可以允許多少需求，統計可行的需求數量並顯示每條需求的路徑。

### 實作方法
對於每個需求，使用`BFS`（Breadth-first search）找出`reqSrc`（request source）到所有點的最短距離，並在過程中將每個點的前一位紀錄在`front`數列，上述動作執行完畢後，由`GetPath`經由`front`取得該需求的最短路徑，若圖中資源足夠支持該路徑，則扣除掉路徑所需的資源並繼續搜尋下一個需求。

### 輸入
<li>格式</li>

```bash
#Nodes    #Links&emsp    #Req
    // 圖 G(V,E)的節點數、邊數與接下來要輸入的需求數量

NodeID    #QuantumMemories
    // NodeID 為節點的編號，隨後輸入的是該點的權重

LinkID    LinkEnd1    LinkEnd2    #Channels
    // LinkID 為邊的編號，LinkEnd1 與 LinkEnd2 為邊的兩個端點，需要輸入剛才所設定的節點編號，Channels 是邊的權重

ReqID    ReqSrc    ReqDst
    // ReqID 為需求的編號，對於每個需求，需要尋找從 ReqSrc 到 ReqDst 的 path
``` 

<li>範例</li>
<br/>
<div align = "center">
<image src = "input_graph.jpg" width = 50%>

範例輸出
</div>
<br/>

```bash
3 3 2
0 6
1 4
2 5
0 0 1 2
1 0 2 3
2 1 2 5
0 0 2
1 1 2
```

### 輸出
<li>格式</li>

```bash
#AccReq
    // 可滿足的需求總數量
ReqID   ReqSrc    Rep1    Rep2 ... ReqDst
    // ReqID 為滿足的需求編號，之後由 source 開始，destination 為終點，展示滿足條件的 path
```  
<li>範例</li>

```bash
2
0 0 2
1 1 2
```

### 工具準備
<li>安裝 gcc：</li>

```bash
sudo apt-get install gcc
```
查看是否已安裝 gcc：`gcc --version`

### 編譯
```bash
gcc QuantumNet.c -o QuantumNet
```

### 執行
```bash
./QuantumNet
```
